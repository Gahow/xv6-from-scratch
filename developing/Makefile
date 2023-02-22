OBJS = boot/boot.o \
       boot/start.o \
       kernel/main.o \
       kernel/uart.o

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

GDBPORT = 1234

all: $(OBJS) $(LINKER)
	$(LD) -T $(LINKER) $(OBJS) -o $(IMAGE)

boot/boot.o: boot/boot.S
	$(CC) $(CFLAGS) -c -o $@ $<

boot/start.o: boot/start.c
	$(CC) $(CFLAGS) -c -o $@ $<

kernel/main.o: kernel/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

kernel/uart.o: kernel/uart.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	$(QEMU) $(QEMUOPTS)

debug: all
	$(QEMU) $(QEMUOPTS) -gdb tcp::$(GDBPORT) -S

clean:
	rm -fv $(IMAGE) *.o

.PHONY: clean
