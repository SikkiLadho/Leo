![Generic badge](https://img.shields.io/github/commit-activity/m/sikkiladho/leo)
[![C/C++ CI](https://github.com/SikkiLadho/Leo/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/SikkiLadho/Leo/actions/workflows/c-cpp.yml)

# Leo Hypervisor

`Leo` is a `Type 1 Hypervisor` for the `Raspberry Pi 4`.

# Set Up 

This setup was tested on Debian.

1. Install the required dependencies and toolchain,

  ```shell
  sudo apt install git bc bison flex libssl-dev make libc6-dev libncurses5-dev
  ```

2. Install the 64-bit toolchain for a 64-bit kernel,

  ```shell
  sudo apt install crossbuild-essential-arm64
  ```

3. Compile ARM-trusted-Firmware for Raspiberry Pi,

  ```shell
  git clone https://github.com/ARM-software/arm-trusted-firmware.git
  cd arm-trusted-firmware/
  CROSS_COMPILE=aarch64-linux-gnu- make PLAT=rpi4 DEBUG=1
  ```

4. Copy the `bl31.bin` from [Trusted Firmware-A (TF-A)](https://trustedfirmware-a.readthedocs.io/en/latest/) to the `/boot/` directory on the Raspberry Pi 4B's SD card,

  ```shell
  cp build/rpi4/debug/bl31.bin /media/me/boot/
  ```

5. Rename `kerne8.img` to `el1-kernel.img` in the SD Card's boot directory,

  ```shell
  mv /media/boot/kernel8.img el1-kernel8.img
  ```

6. Compile Leo ARM64 Hypervisor

  ```shell
  git clone https://github.com/sikkiladho/leo.git leo
  cd leo
  make
  ```

You will get the `kernel8.img` binary, which is the hypervisor binary. Copy it to you SD Card.

7. Add following to /boot/config.txt in Raspberry Pi Model 4B

  ```txt
  enable_uart=1
  arm_64bit=1
  enable_gic=1
  armstub=bl31.bin
  initramfs el1-kernel.img 0x400000
  ```
