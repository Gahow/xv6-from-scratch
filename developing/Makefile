OBJS = start.o boot.o

LINKER = linker.ld
IMAGE = kernel.img

CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-as
LD = riscv64-unknown-elf-ld

CFLAGS  = -ffreestanding -nostdlib
CFLAGS += -mcmodel=medany
CFLAGS += -Wall -Wextra
CFLAGS += -Iinclude
CFLAGS += -g

QEMU = qemu-system-riscv64
QEMUOPTS = -nographic -machine virt -bios none -kernel $(IMAGE)

all: $(OBJS) $(LINKER)
	$(LD) -T $(LINKER) $(OBJS) -o $(IMAGE)

start.o: start.c
	$(CC) $(CFLAGS) -c -o $@ $<

boot.o: boot.S
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	$(QEMU) $(QEMUOPTS)

clean:
	rm -fv $(IMAGE) *.o

.PHONY: clean
