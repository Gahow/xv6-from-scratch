# 01-Hello World

In this chapter, we will boot our OS and make it print "Hello world" in
the screen.

## Prerequisite

- [linker script manual](
https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html)
- [RISC-V assembly](https://shakti.org.in/docs/risc-v-asm-manual.pdf)
- [GNU make manual](https://www.gnu.org/software/make/manual/make.html)
- [QEMU documentation](https://www.qemu.org/docs/master/system/qemu-manpage.html)

## Code

We use `linker.ld` to describe how to arrange the memory and rovide a definition
of `_stack` which used in `boot.S`.

`boot.S` just set `sp` and jump to function `start`.

In `start.c`, we define something about UART(universal asynchronous receiver /
transmitter) to print "Hello world" to screen, we will introduce this in the
next chapter, you can go on to next chapter.

You can use `make run` to run your OS, and `Ctrl-a x` to quit QEMU.
