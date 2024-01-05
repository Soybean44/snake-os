# Uefi-os

## Setup

To create the virtual hard disk run the following commands
```sh
touch test.hdd
dd if=/dev/zero of=test.hdd bs=1M count=100
sudo mkfs.fat -F32 test.hdd 
```

To install the OS to said file do the following
```sh
sudo mkdir -p /mnt/p1
sudo mount test.hdd /mnt/p1
sudo mkdir -p /mnt/p1/EFI/BOOT
sudo cp BOOTX64.EFI /mnt/p1/EFI/BOOT/ # Note this will return a warning ignore it
sudo umount /mnt/p1
```

in theory if you format a USB in the same way you should be able to run this on bare metal, but for ease of use it is best to partition it, so you have a system partition and a Microsoft basic data partition

Note that all of this has been moved to a shell script

