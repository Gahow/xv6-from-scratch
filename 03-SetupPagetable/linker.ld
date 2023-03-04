OUTPUT_ARCH("riscv")
ENTRY(_entry)

SECTIONS {
    . = 0x80000000;

    .text ALIGN(0x1000) : {
        *(.boot);
        *(.text .text.*);
        . = ALIGN(0x1000);
        PROVIDE(_etext = .);
    }

    .rodata ALIGN(0x1000) : {
        *(.rodata .rodata.*);
    }

    .data ALIGN(0x1000) : {
        *(.data .data.*);
    }

    .bss ALIGN(0x1000) : {
        *(.bss .bss.*);
        . = ALIGN(0x1000);
        PROVIDE(_stack = . + 0x1000);
    }

    . = ALIGN(0x1000);
    PROVIDE(_end = .);
}
