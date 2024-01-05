.POSIX:
.PHONY: all clean

SOURCE = efi.c
OBJS = $(SOURCE:.c=.o)
DEPENDS = $(OBJS:.o=.d)
TARGET = BOOTX64.EFI

# Uncomment for gcc
CC = x86_64-w64-mingw32-gcc \
	-Wl,--subsystem,10 \
	-e efi_main 

# Uncomment for clang
#CC = clang \
	-target x86_64-unknown-windows \
	-fuse-ld=lld-link \
	-Wl,-subsystem:efi_application \
	-Wl,-entry:efi_main

CFLAGS = \
	-std=c17 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-mno-red-zone \
	-MMD \
	-ffreestanding \
	-nostdlib 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

-include $(DEPENDS)
 

clean:
	rm -rf $(TARGET) 
	rm $(OBJS)

