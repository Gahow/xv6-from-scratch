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
