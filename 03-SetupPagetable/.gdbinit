set confirm off
set architecture riscv:rv64
set disassemble-next-line auto
set riscv use-compressed-breakpoints yes
target remote 127.0.0.1:1234
symbol-file kernel.img
