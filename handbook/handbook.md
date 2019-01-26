# NomadBSD Handbooklet

## Content
1. [Intro](#intro)
2. [Installation](#installation)
	1. [Choosing a USB flash drive](#choosemedia)
	2. [Downloading an writing the image](#download)
3. [Overview](#overview)
4. [Enable/Disable desktop components, and auto-start programs](#autostart)
5. [Filesystem](#filesystems)
	1. [Automount](#automount)
	2. [Extending filesystem support](#fssupport)
		1. [exFat](#exfat)
		2. [BTRFS, ReiserFS, XFS](#linuxfs)
6. [Networking](#networking)
	1. [Wireless Networking](#wifi)

<a name="intro"></a>
## 1. Intro

NomadBSD is a 64bit live system for USB flash drives, based on
FreeBSD<sup>®</sup>. Together with automatic hardware detection and setup, it
is configured to be used as a desktop system that works out of the box, but
can also be used for data recovery, or to test FreeBSD<sup>®</sup> hardware
compatibility.

<a name="installation"></a>
## 2. Installation

### Choosing a USB flash drive
NomadBSD performs well on USB 2.0 flash drives, but writing many small files
can be very slow. To improve performace, you should consider using a USB 3.X
flash drive even on a USB 2.X port, as they tend to be faster. See
[USB 3.0 Flash Drive Roundup](https://www.anandtech.com/show/4523/usb-30-flash-drive-roundup/6)

### Downloading and writing the image
Instructions for writing the image to a flash drive from different operating
systems can be found [here](https://nomadbsd.org/download.html).

<a name="overview"></a>
## 3. Overview
![](images/nomadbsd-overview.png)

1. [Openbox](http://freshports/x11-wm/openbox) menu. You can reach it by
	pressing the Windows<sup>®</sup> key (or Super key)/Cmd key
	(Mac<sup>®</sup>), or by right-clicking on the background image
	(root window).
2. [DSBBatmon](http://freshports.org/sysutils/dsbbatmon). By hovering over
	the icon you can see the battery's current status and charge. Clicking
	on it brings up the configuration menu.
3. [DSBMixer](http://freshports.org/audio/dsbmixer). By hovering over the
	icon you can see the current volume of the master
	channel. Using the mouse wheel on it lets you change the
	master volume. Clicking on it brings up the main window of
	[DSBMixer](http://freshports.org/audio/dsbmixer).
4. [DSBMC](http://freshports.org/sysutils/dsbmc). Clicking on the icon brings
	up the main window in which you	can see all the mountable storage devices
	attached to the system. Use	the context menu of the device icons to select
	an action (un/mounting,	opening, playing, ejecting) or double click to
	mount and open the device in your default filemanager. You can use the
	preferences menu to change the filemanager, autoplay setting, and
	multimedia programs.
5. Date and time. Clicking in that area brings up a calendar.

<a name="autostart"></a>
## 4. Enable/Disable desktop components, and auto-start programs
The program [DSBAutostart](http://freshports.org/sysutils/dsbautostart)
([Openbox menu](#overview) -> *Settings* -> *DSBAutostart*) allows you to control which
programs are automatically executed when the graphical interface starts.
Further, it allows you to enable/disable some components of the NomadBSD
desktop. The changes take place after logging out and in again.

![](images/dsbautostart-screenshot.png)

<a name="filesystems"></a>
## 5. Filesystems
NomadBSD comes with a bunch of pre-installed filesystems (CD9660, FAT, HFS+,
NTFS, Ext2/3/4). You can mount storage devices via
[DSBMC](http://freshports.org/sysutils/dsbmc) (see [Overview](#overview)),
which is a graphical client for [DSBMD](http://freshports.org/sysutils/dsbmd).
<a name="automount"></a>
### Automount
Execute the command `dsbmc-cli -a` to automount all currently connected
storage devices, and to enable automounting on devices attached later to the
system. To start this command automatically on session start, open
[DSBAutostart](#autostart), and add a new entry for the above command.

<a name="fssupport"></a>
### Extending filesystem support
The following subsections describe how to extend the filesystems support.
Rebooting the system, or restarting
[DSBMD](http://freshports.org/sysutils/dsbmd) is not necessary.

<a name="exfat"></a>
#### ExFat
Unfortunately,
[sysutils/fusefs-exfat](https://freshports.org/sysutils/fusefs-exfat)
requires a license from Microsoft<sup>®</sup>, and so it can't be
pre-installed. You have to build it yourself by using the ports or the
[Git repo](https://github.com/relan/exfat.git):

	# pkg install autoconf
	# pkg install automake
	# git clone https://github.com/relan/exfat.git
	# cd exfat
	# autoreconf --install
	# ./configure
	# make && make install

<a name="linuxfs"></a>
#### BTRFS, ReiserFS, XFS
Install the package
[fusefs-lkl](https://www.freshports.org/sysutils/fusefs-lkl) for BTRFS,
ReiserFS, and XFS support.

	# pkg install fusefs-lkl

<a name="networking"></a>
## 6. Networking
<a name="wifi"></a>
### Wireless Networking
The program [wifimgr](http://freshports.org/net-mgmt/wifimgr)
([Openbox menu](#overview) -> *Network* -> *WiFi Networks Manager*) allows
you to connect to a wireless network.

