# NomadBSD: A Versatile Persistent Live System

NomadBSD is a versatile and reliable **persistent live system**, meticulously crafted for seamless operation on portable flash drives. Based on the robust FreeBSD foundation, it provides a secure and efficient computing environment that can accompany you wherever you go.

![NomadBSD Screenshot](http://nomadbsd.org/screenshots/nomadbsd-131R-20221130.png)

**Table of Contents**
- [About NomadBSD](#about-nomadbsd)
- [Visual Excellence](#visual-excellence)
- [Get Started Now](#get-started-now)
  - [System Requirements](#system-requirements)
- [Building Your Custom Image](#building-your-custom-image)
  - [Image Building Requirements](#image-building-requirements)
  - [Repository Cloning](#repository-cloning)
  - [Building the Image](#building-the-image)
  - [Resuming After Build Errors](#resuming-after-build-errors)
  - [Writing the Image to a USB Memory Stick](#writing-the-image-to-a-usb-memory-stick)

## About NomadBSD

NomadBSD offers a customizable computing experience, making it an ideal choice for individuals who require both their operating system and data on the move. This project is deeply rooted in the FreeBSD operating system, enhanced with additional stability and performance enhancements.

## Visual Excellence

Explore the elegance of NomadBSD with a glance at our visually stunning interface:

![NomadBSD Screenshot](http://nomadbsd.org/screenshots/nomadbsd-131R-20221130.png)

Discover the rich features and capabilities that NomadBSD has to offer!

## Get Started Now

Experience the power and flexibility of FreeBSD on your portable drive today. Visit the [NomadBSD website](http://nomadbsd.org) to download the latest image.

### System Requirements

To fully harness the potential of NomadBSD, ensure your hardware meets these prerequisites:

- A flash drive with a minimum of 5GB of storage.
- A system equipped with an AMD64 or I386 architecture, boasting at least a 1.2GHz CPU and 1GB of RAM (or 2GB when utilizing ZFS). These specifications are designed to provide a seamless NomadBSD experience.

## Building Your Custom Image

If you're interested in creating your personalized NomadBSD image, follow these steps:

### Image Building Requirements

To build a NomadBSD image, you'll need:

- A recent FreeBSD system with approximately 30GB of available disk space.
- The major version of your FreeBSD system should be equal to or greater than the base system's major version of the image you intend to build.
- A recent ports tree.
- Ensure the following packages are installed: `x11-fonts/mkfontscale` and `textproc/markdown`.

### Repository Cloning

Recursively clone the NomadBSD repository with the following command:

```shell
git clone --recursive https://github.com/nomadbsd/NomadBSD.git
```

### Building the Image

Before proceeding, make sure your NomadBSD repository copy is owned by the root user. If not, run the following command as root:

```shell
git config --global --add safe.directory /full/path/to/NomadBSD
```

This step is critical for generating the image name correctly.

To initiate the image building process, run the following command. By default, it builds a 64-bit (amd64) image. To create a 32-bit (i386) image or a Mac image, set `ARCH=i386` or `ARCH=mac` accordingly in `build.cfg`. You can also define ARCH via the `-a` option. NomadBSD can be built with UFS (default) or ZFS as the file system. Define the file system via `FILESYSTEM` in `build.cfg` or the `-f` option.

```shell
./build all
```

### Resuming After Build Errors

In case of build errors, you can resume the process after identifying and rectifying the issue that caused the build to halt:

```shell
./build resume
```

### Writing the Image to a USB Memory Stick

To write the NomadBSD image to a USB memory stick, utilize the following command:

```shell
dd if=nomadbsd.img of=/dev/da0 bs=1M conv=sync
```
