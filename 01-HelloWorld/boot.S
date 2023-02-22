.section .boot
.global _entry

_entry:
    // set sp point to _stack
    la sp, _stack

    // jump to start
    call start
