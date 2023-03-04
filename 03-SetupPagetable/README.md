# 03-Setup pagetable

In this chapter, we will write some code to implement pagetable and set `satp`
to open pagetable.  

## Prerequisite

- [an introduction to RISC-V](
https://cdn2.hubspot.net/hubfs/3020607/An%20Introduction%20to%20the%20RISC-V%20Architecture.pdf)
- [privileged registers](
https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf)

## Code

1. We add `panic.c` to write a simple function `panic`. The function just print
error messages and go into infinity loop.
2. Write the most important part for pagetbale. In folder `mm`, we create two
files, `kalloc.c` and `vm.c`.  
In `kalloc.c` we defite a struct `page` to represent a pagetable, and a global
variable `kmem` for a list of free page. When initing, we free the physical
memory from `_end` to `PHYSTOP`. For every page in the range, we clear it and
add it to `free_list`. When we need a page, we call `kalloc()` to get a free
page in the top of free_list.  
In `vm.c`, we do page map. In function `mappg()`, we map `sz` space started from
`va` to `pa`, we just use `walk` to find the `pte` and set the `pa` and `perm`
to the `pte`. In function `walk()`, we go through 3 level map to find the
address of pte, if `alloc`, we will `kalloc()` a new page for middle page
directories. And we use `kernel_pgtb` as the base page for `satp`, in
`kvmmake()`, we map the physical space we use now, including `URAT0`,
`KERNELBASE` and `RAM`. Then we can init our pagetable.
3. In the `lib` directory, we add file `printf.c` to implement a limited
function `printf()`.
4. In `main()`, we do some test for pagetable.

If you are doing code by yourself, do not forget to update `*.h` file and
`Makefile`.
