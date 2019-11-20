### About

NomadBSD is a live system for flash drives, based on FreeBSD.

### Screenshots
![](http://nomadbsd.org/screenshots/nomadbsd-1.3-RC1-ss1.png)

### Requirements for building the image
A recent FreeBSD system

### Requirements for running NomadBSD
* A 4GB (or more) flash drive
* A (amd64/i386) system with a 1.2GHz CPU and 1G of RAM should be able to run
NomadBSD decently.

### Building the image
By default, the build script builds a 64-bit (amd64) image. For a 32-bit (i386)
image, set ````ARCH=i386```` in ````build.cfg````.

~~~ csh
# ./build all
~~~

If you want to build an image for Mac, define ````-m````
~~~ csh
# ./build -m all
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
