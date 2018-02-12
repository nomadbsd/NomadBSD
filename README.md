### About

NomadBSD is a live system for flash drives, based on FreeBSD.

### Screenshots
![](http://freeshell.de/~mk/download/nomadbsd-ss1.png)
![](http://freeshell.de/~mk/download/nomadbsd-ss2.png)

### Requirements for building the image
A recent FreeBSD system

### Requirements for running NomadBSD
* A 4GB (or more) flash drive
* A System capable running FreeBSD 11.1 (amd64)

### Building the image
~~~ csh
# make image
~~~
### Writing the image to an USB memory stick
~~~ csh
# dd if=nomadbsd.img of=/dev/da0 bs=10240 conv=sync
~~~

### Ready to use image
Visit https://freeshell.de/~mk/projects/nomadbsd.html to download the recent image.
