# 02-Jump to Supervisor Mode

In this chapter, we will jump to supervisor mode and learn more about UART.

Meanwhile, we will rearrange the structure of our source code to keep the
project neat.

Finally, we will learn how to use gdb which can help us debug in the future.

## Prerequisite

- [an introduction to RISC-V](
https://cdn2.hubspot.net/hubfs/3020607/An%20Introduction%20to%20the%20RISC-V%20Architecture.pdf)
- [privileged registers](
https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf)
- [UART registers](http://byterunner.com/16550.html)
- [QEMU riscv virt memmap](
https://github.com/qemu/qemu/blob/79b677d658d3d35e1e776826ac4abb28cdce69b8/hw/riscv/virt.c#L87)

## Code

First, we modify `start.c`, add a series of functions to read or write M-level
registers. You can follow the comment before `start()` to learn the use of these
registers, and do some bit set to transfer to supervisor mode.

Second, we add `uart.c` and create a function `uartinit()` to set UART chip, a
function `getchar()` to receive user input. You can read the
[UART registers](http://byterunner.com/16550.html) to get the infomation you
need.

Finnaly, we do a litte change to `main.c` to test our new code.

By the way, after adding some new files and changing in file structure, we need
to modify our `Makefile` which is easy to understand.

## gdb

We add a `.gitinit` file so that gdb can init to connect with our OS.

And add a `gdb` target in `Makefile`, so that you can use `make gdb` to start
debug. Then you need to open `riscv-unknown-elf-gdb`(maybe the binary name can
be different in your environment) in a new terminal. You can add some
breakpoints and print some middle info now!
