#!/bin/sh
sudo mkdir -p /mnt/p1
# check if BOOTX64.EFI exists
if [ -e BOOTX64.EFI ]
then
  echo "BOOTX64.EFI found, creating image:"
  # check if hard disk image exists
  if [ -e test.hdd ]
  then
    echo "test.hdd found, updating image:"
    # assume its partitioned
    # seet up loopback devices for each virtual partition
    sudo kpartx -av test.hdd 
    # mount on partition 1
    sudo mount /dev/mapper/loop0p1 /mnt/p1/
    # make EFI and BOOT directories if they dont exist
    sudo mkdir -p /mnt/p1/EFI/BOOT
    # copy bootloader file to the BOOT directory 
    sudo cp BOOTX64.EFI /mnt/p1/EFI/BOOT/BOOTX64.EFI
    # unmout and delete loopback devices
    sudo umount /mnt/p1
    sudo kpartx -d test.hdd
  else
    echo "test.hdd not found, creating image:"
    # create virtual img
    touch test.hdd
    # fill it with 100MiB of zeros
    dd if=/dev/zero of=test.hdd bs=1M count=100
    # Create an efi system partition that takes up majority of the disk
    sgdisk -n 1:0MiB:99MiB test.hdd
    sgdisk -t 1:ef00 test.hdd
    # format said partition
    sudo mkfs.fat -F32 --offset=2048 test.hdd
    # seet up loopback devices for each virtual partition
    sudo kpartx -av test.hdd 
    # mount on partition 1
    sudo mount /dev/mapper/loop0p1 /mnt/p1/
    # make EFI and BOOT directories
    sudo mkdir -p /mnt/p1/EFI/BOOT
    # copy bootloader file to the BOOT directory 
    sudo cp BOOTX64.EFI /mnt/p1/EFI/BOOT/BOOTX64.EFI
    # unmout and delete loopback devices
    sudo umount /mnt/p1
    sudo kpartx -d test.hdd
  fi 
else
  echo "BOOTX64.EFI not found, aborting"
  exit 1
fi
exit 0
