# NomadBSD

<p align="center">
<img src="../../../../nomadbsd/artwork/blob/main/logo/nomadbsd-logo-bright-128x128.png#gh-dark-mode-only"></img>
<img src="../../../../nomadbsd/artwork/blob/main/logo/nomadbsd-logo-dark-128x128.png#gh-light-mode-only"></img>
</p>

## About
NomadBSD is a persistent live system for flash drives, based on FreeBSD.

## Screenshots
![](http://nomadbsd.org/screenshots/nomadbsd-xfce.png)

## Ready to use Image
Visit http://nomadbsd.org to download the recent image.

### Requirements for Running NomadBSD
* A >= 5GB flash drive
* A (amd64/i386) system with a 1.2GHz CPU and 1G of RAM (2G when using ZFS)
should be able to run NomadBSD decently.

## Building the Image
### Requirements for Building the Image
* A recent FreeBSD system with approx. 30GB free disk space.
* The build machine's major FreeBSD version must be >= the base system's
major version of the image you want to build.
* A recent ports tree.
* The packages x11-fonts/mkfontscale, and textproc/markdown must be installed.

### Cloning the Repository
~~~ csh
% git clone --recursive https://github.com/nomadbsd/NomadBSD.git
~~~

### Building the Image
#### Preparation
If your copy of the NomadBSD repository is not owned by the root user, run

~~~ csh
# git config --global --add safe.directory /full/path/to/NomadBSD
~~~

as root before the first build. Otherwise the build script can't correctly
generate the image name.

#### Building
By default, the build script builds a 64-bit (amd64) image. For a 32-bit (i386)
image, or a Mac image set `ARCH=i386` or `ARCH=mac` accordingly in `build.cfg`.
ARCH can also be defined via the `-a` option.

NomadBSD can be build with UFS (default), and ZFS as file system. The file
system can be defined via `FILESYSTEM` in `build.cfg`, or via the `-f`
option.

~~~ csh
# ./build all
~~~

#### Resuming from Build Errors
If something went wrong, you can resume the build after locating and fixing
the problem that caused the build to stop.
~~~ csh
# ./build resume
~~~

### Writing the image to a USB memory stick
~~~ csh
# dd if=nomadbsd.img of=/dev/da0 bs=1M conv=sync
~~~
