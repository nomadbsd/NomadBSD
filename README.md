### About

NomadBSD is a persistant live system for flash drives, based on FreeBSD.

### Screenshots
![](http://nomadbsd.org/screenshots/nomadbsd-1.3-RC1-ss1.png)

### Requirements for building the image
A recent FreeBSD system with at least 40GB free disk space. The build machine's
major FreeBSD version must be >= the base system's major version of the image
you want to build. If you're building the image on a system with ZFS, the build
might fail due to a problem with the size calculation for the root file system.
It's best to run a FreeBSD system with UFS in a virtual machine for the build.

### Requirements for running NomadBSD
* A >= 5GB flash drive
* A (amd64/i386) system with a 1.2GHz CPU and 1G of RAM should be able to run
NomadBSD decently.

### Building the image
By default, the build script builds a 64-bit (amd64) image. For a 32-bit (i386)
image, or a Mac image set `ARCH=i386` or `ARCH=mac` accordingly in `build.cfg`.
ARCH can also be defined via the `-a` option.

~~~ csh
# ./build all
~~~

If something went wrong, you can resume the build after locating and fixing
the problem that caused the build to stop.
~~~ csh
# ./build resume
~~~

### Writing the image to an USB memory stick
~~~ csh
# dd if=nomadbsd.img of=/dev/da0 bs=1M conv=sync
~~~

### Ready to use image
Visit http://nomadbsd.org to download the recent image.
