#!/bin/sh
sudo mkdir -p /mnt/p1
if [ -e test.hdd ]
then
  sudo mount test.hdd /mnt/p1/
  sudo mkdir -p /mnt/p1/EFI/BOOT
  sudo cp BOOTX64.EFI /mnt/p1/EFI/BOOT/BOOTX64.EFI
  sudo umount /mnt/p1
else
  touch test.hdd
  dd if=/dev/zero of=test.hdd bs=1M count=100
  sgdisk -n 1:0MiB:33MiB test.hdd
  sgdisk -t 1:ef00 test.hdd
  sgdisk -n 2:34MiB:66MiB test.hdd
  sgdisk -t 2:0700 test.hdd
  sudo mkfs.fat -F32 --offset=2048 test.hdd
  sudo kpartx -av test.hdd 
  sudo mount /dev/mapper/loop0p1 /mnt/p1/
  sudo mkdir -p /mnt/p1/EFI/BOOT
  sudo cp BOOTX64.EFI /mnt/p1/EFI/BOOT/BOOTX64.EFI
  sudo umount /mnt/p1
  sudo kpartx -d test.hdd
fi 
