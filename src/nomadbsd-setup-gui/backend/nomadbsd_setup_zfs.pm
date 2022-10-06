#!/usr/local/bin/perl
#
# Copyright (c) 2022 The NomadBSD Project. All rights reserved.
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

#
# 1. Get the device associated with our ZFS pool
# 2. Get the device name from glabel if a device label was used.
# 3. Return (device name, slice number). E.g. (da0, 2)
#
sub get_rootdev {
	my ($device, $partition, $found_pool);

	foreach (`zpool list -H -v`) {
		if ($found_pool) {
			$device = (split(/\s+/, $_))[1];
			last;
		} elsif (/^${main::pool}\s+/) {
			$found_pool = 1;
		}
	}
	return if (!$device);

	$device =~ s#/dev/##;

	if ($device =~ /^(gpt|label|gptid)\//) {
		foreach (`glabel status`) {
			$_ =~ s/\s+//;
			my ($l, $s, $d) = split(/\s+/, $_);
			if ($l eq $device) {
				$device = $d;
				last;
			}
		}
	}
	if ($device =~ /([a-zA-Z0-9]+)[sp]([0-9]{1,})[a-f]?$/) {
		$device = $1; $partition = $2;
		# Get partition type: GPT or MBR
		my @out = `gpart show $device`;
		my @fields = split(/\s+/, $out[0]); 
		return ($device, $partition, $fields[4]);
	}
}

sub mk_enc_zfs_dataset {
	my $dataset     = "${main::pool}/private";
	my $create_cmd  = "zfs create -o encryption=on -o keylocation=prompt " .
					  "-o keyformat=passphrase $dataset";
	status("Creating encrypted ZFS dataset on $dataset");
	open(my $fh, "|$create_cmd") or bail("Couldn't create $dataset");
	print $fh "${main::cfg_enc_password}\n";
	bail("Failed to create $dataset.")	if (!close($fh));
	system("zfs set mountpoint=/private $dataset") == 0
		or bail("Couldn't mount $dataset");
	status("Creating /private/etc");
	system("mkdir /private/etc") == 0
		or bail("Failed to create /private/etc");
	status("Creating /private/home/nomad");
	system("mkdir -p /private/home/nomad") == 0
		or bail("Failed to create /private/home/nomad");
	system("unlink /home >/dev/null 2>&1");
	system("rmdir -rf /home 2>&1");
	status("Symlinking /home to /private/home");
	system("ln -s /private/home /home") == 0
		or bail("Failed to create symlink /home -> /private/home");
	system("chown nomad:nomad /home/nomad");

	# Protect plain text passwords from ppp.conf and wpa_supplicant.conf
	system("mv /etc/ppp /private/etc/");
	system("mv /etc/wpa_supplicant.conf /private/etc");
	system("touch /private/etc/wpa_supplicant.conf");
	system("cd /etc && ln -sf /private/etc/ppp; " .
		   "ln -sf /private/etc/wpa_supplicant.conf");
	system("sysrc -f /etc/rc.conf.in mount_enc_zfs_enable=YES");
	system("sysrc -f /etc/rc.conf.in mount_enc_zfs_dataset=\"${dataset}\"");
}

1;
