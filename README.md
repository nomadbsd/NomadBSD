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

### Resize filesystem to use the entire USB memory
Boot NomadBSD into single user mode, and execute:
~~~
# gpart delete -i 2 da0s1
# gpart resize -i 1 da0
# gpart commit da0s1
~~~
Determine the partition size in megabytes using ````fdisk da0````, and calculate
the remaining size of da0s1a:
````<REMAIN> = <SIZE OF PARTITION IN MB> - <DESIRED SWAP SIZE IN MB>````.

~~~
# gpart resize -i 1 -s <REMAIN>M da0s1
# gpart add -t freebsd-swap -i 2 da0s1
# glabel label NomadBSDsw da0s1b
# service growfs onestart
# reboot
~~~
