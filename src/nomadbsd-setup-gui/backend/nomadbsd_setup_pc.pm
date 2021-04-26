#!/usr/local/bin/perl
#
# Copyright (c) 2019 The NomadBSD Project. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
use utf8;
use strict;

binmode(STDOUT, ":utf8");
binmode(STDERR, ":utf8");

my $rootlabel = "nomadroot";
my $datalabel = "nomaddata";

#
# 1. Get the device mounted on /, which must be label/$rootlabel
# 2. Get the device name from glabel
# 3. Return the device name without the '/dev' prefix and slice.
#
sub get_rootdev {
	my ($rootdev, @output);
	
	@output = `df /`;
	# Skip header
	$rootdev = (split(/\s+/, $output[1]))[0];
	$rootdev =~ s#/dev/##;
	return if ($rootdev ne "label/$rootlabel");
	foreach (`glabel status`) {
		$_ =~ s/\s+//;
		my ($l, $s, $d) = split(/\s+/, $_);
		next if ($l ne "label/$rootlabel");
		return $1 if (/([a-zA-Z0-9]+)[sp][0-9]{1,}[a-f]?$/);
	}
}

#
# Return the device and slice the /home partition is stored on.
# It must match the label label/$datalabel, and must be on the
# root device.
#
sub get_datadev {
	my ($rootdev, $datadev, @output);
	
	$rootdev = get_rootdev();
	bail("Couldn't find root device") if (!$rootdev);
	@output = `df /`;
	# Skip header
	$datadev = (split(/\s+/, $output[1]))[0];
	$datadev =~ s#/dev/##;
	bail("label/$datalabel not mounted on /data")
		if ($output[1] ne "label/$datalabel");
	@output = `glabel status`;
	# Skip header
	shift @output;
	foreach (@output) {
		chomp;
		# Remove leading spaces
		$_ =~ s/^\s+//;
		my ($l, $s, $d) = split(/\s+/, $_);
		if ($l eq "label/$datalabel") {
			return $d if ($d =~ /$rootdev[ps]{1}[0-9]{1,}[a-f]?$/);
			bail("label/$datalabel not on $rootdev");
		}
	}
	bail("Couldn't find label/$datalabel");
}

sub mkdatapart {
	my $dev = get_rootdev();
	my ($partdev, $datadev);
	bail("Failed to find root device.") if (!$dev);
	#
	# Check if label/${datalabel} already exists.
	#
	foreach (`glabel status`) {
		$_ =~ s/\s+//;
		my ($l, $s, $d) = split(/\s+/, $_);
		if ($l eq "label/$datalabel") {
			bail("Error: label/$datalabel already exists");
		}
	}
	system("gpart recover $dev >/dev/null");
	chomp($partdev = `gpart add -a 1m -t freebsd $dev`);
	bail("'gpart add -t freebsd $dev' failed") if ($?);
	bail("Unexpected gpart output: '$partdev'")
		if (!($partdev =~ s/^([a-z0-9]+)\s(added|created)/$1/));
	system("dd if=/dev/zero of=/dev/${partdev} bs=1M count=100");
	system("gpart create -s bsd ${partdev}") == 0
		or bail("'gpart create -s bsd ${partdev}' failed");
	chomp($datadev = `gpart add -t freebsd-ufs -a 1m -b 16 ${partdev}`);
	bail("'gpart add -t freebsd-ufs -a 1m -b 16 $partdev' failed") if ($?);
	bail("Unexpected gpart output: '$datadev'")
		if (!($datadev =~ s/^([a-z0-9]+)\s(added|created)/$1/));
	system("glabel label ${datalabel} /dev/${datadev}") == 0
		or bail("Couldn't create label on /dev/${datadev}.");
}

sub mkdatafs {
	my $dev = "/dev/label/$datalabel";
	my $cmd = "newfs -t -E -U -O 1 -o time -b ${main::blksize} " .
		  "-f ${main::fragsize} -m 8 $dev";
	mkdatapart();
	status("Creating filesystem on $dev");
	newfswrp($cmd);
	if (! -d "/data") {
		status("Creating /data");
		system("mkdir /data") == 0
			or bail("Failed to create directory /data");
	}
	status("Mounting $dev on /data");
	system("mount $dev /data") == 0
		or bail("Couldn't mount $dev on /data");
	status("Adding fstab entry for /data");
	open(my $fh, ">>/etc/fstab") or bail("Couldn't open /etc/fstab");
	print $fh "$dev\t/data\t\t\tufs\trw,noatime\t1 1\n";
	close($fh);
}

sub mkgelidata {
	my $dev			= "/dev/label/$datalabel";
	my $geli_init	= "geli init -s 4096 -e AES-XTS -l 256 -J - $dev";
	my $geli_attach	= "geli attach -j - $dev";
	my $newfscmd	= "newfs -t -E -U -O 1 -o time -b ${main::blksize} -f " .
					  "${main::fragsize} -m 8 ${dev}.eli";
	status("Creating partition for /data");
	mkdatapart();
	status("Initializing geli volume");
	open(my $fh, "|$geli_init") or bail("Couldn't init geli volume");
	print $fh "${main::cfg_geli_password}\n";
	bail("Failed to init geli volume.")	if (!close($fh));
	status("Attaching geli volume");
	open(my $fh, "|$geli_attach") or bail("Couldn't attach geli volume");
	print $fh "${main::cfg_geli_password}\n";
	bail("Failed to attach geli volume.") if (!close($fh));
	status("Creating filesystem on ${dev}.eli");
	newfswrp($newfscmd);
	if (! -d "/data") {
		system("unlink /data >/dev/null 2>&1");
		status("Creating /data");
		system("mkdir /data") == 0 or bail("Failed to create /data");
	}
	status("Mounting ${dev}.eli on /data");
	system("mount ${dev}.eli /data") == 0
		or bail("Failed to mount filesystem.");
	status("Creating /data/home");
	system("mkdir /data/home") == 0
		or bail("Failed to create /data/home");
	status("Creating /data/etc");
	system("mkdir /data/etc") == 0
		or bail("Failed to create /data/etc");
	status("Creating /data/home/nomad");
	system("mkdir /data/home/nomad") == 0
		or bail("Failed to create /data/home/nomad");
	system("unlink /home >/dev/null 2>&1");
	system("rmdir -rf /home 2>&1");
	status("Symlinking /home to /data/home");
	
	system("ln -s /data/home /home") == 0
		or bail("Failed to create symlink /home -> /data/home");
	system("chown nomad:nomad /home/nomad");

	status("Creating /data/freebsd-update");
	system("mkdir /data/freebsd-update");

	# Protect plain text passwords from ppp.conf and wpa_supplicant.conf
	system("mv /etc/ppp /data/etc/");
	system("mv /etc/wpa_supplicant.conf /data/etc");
	system("touch /data/etc/wpa_supplicant.conf");
	system("cd /etc && ln -sf /data/etc/ppp; " .
		   "ln -sf /data/etc/wpa_supplicant.conf");
	system("sysrc -f /etc/rc.conf.in in geli_devices=\"label/${datalabel}\"");
	status("Adding fstab entry for ${dev}.eli");
	open($fh, ">>/etc/fstab") or bail("Couldn't open /etc/fstab");
	print $fh "${dev}.eli\t/data\t\t\tufs\trw,noatime\t1 1\n";
	close($fh);
}

1;

