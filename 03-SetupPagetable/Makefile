ASMS = boot/boot.o
OBJS = boot/start.o \
       kernel/main.o \
       kernel/uart.o \
       kernel/panic.o \
       mm/vm.o \
       mm/kalloc.o \
       lib/string.o \
       lib/printf.o \

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

all: $(ASMS) $(OBJS) $(LINKER)
	$(LD) -T $(LINKER) $(ASMS) $(OBJS) -o $(IMAGE)

boot/boot.o: boot/boot.S
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	$(QEMU) $(QEMUOPTS)

debug: all
	$(QEMU) $(QEMUOPTS) -gdb tcp::$(GDBPORT) -S

clean:
	rm -fv $(IMAGE) *.o **/*.o

.PHONY: clean
