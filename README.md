### About

NomadBSD is a live system for flash drives, based on FreeBSD.

### Screenshots
![](http://nomadbsd.org/screenshots/nomadbsd-1.2-ss1.png)
![](http://nomadbsd.org/screenshots/nomadbsd-1.2-ss2.png)

### Requirements for building the image
A recent FreeBSD system

### Requirements for running NomadBSD
* A 4GB (or more) flash drive
* A System capable running FreeBSD 11.2 (amd64)

### Building the image
~~~ csh
# ./build all
~~~
### Writing the image to an USB memory stick
~~~ csh
# dd if=nomadbsd.img of=/dev/da0 bs=1M conv=sync
~~~

### Ready to use image
Visit http://nomadbsd.org to download the recent image.
