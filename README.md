# Leo Hypervisor
Leo. Type 1 hypervisor on Raspberry Pi 4 machine.

![Generic badge](https://img.shields.io/github/commit-activity/w/sikkiladho/leo)

# Set Up 
This setup was tested on Debian

### Install Required Dependencies and Toolchain

`sudo apt install git bc bison flex libssl-dev make libc6-dev libncurses5-dev`

### Install the 64-bit Toolchain for a 64-bit Kernel

`sudo apt install crossbuild-essential-arm64`

### Compile Trusted-Firmware-A for Raspiberry Pi. 


`git clone https://github.com/ARM-software/arm-trusted-firmware.git`

`cd arm-trusted-firmware/`

`CROSS_COMPILE=aarch64-linux-gnu- make PLAT=rpi4 DEBUG=1`

Copy [Trusted Firmware-A (TF-A)](https://trustedfirmware-a.readthedocs.io/en/latest/) binary 'bl31.bin' to Raspberry Pi 4B's sd card /boot/

`cp build/rpi4/debug/bl31.bin /media/me/boot/`

### Add following to /boot/config.txt in Raspberry Pi Model 4B

``````
enable_uart=1

arm_64bit=1

enable_gic=1

armstub=bl31.bin

kernel=el2-kernel.img

initramfs el1-kernel.img 0x400000
``````

### Rename kerne8.img to el1-kernel.img
