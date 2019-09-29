.extern main
.extern StaticInitialize

.section ".text.boot"

.global _start

_start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    // cpu id > 0, stop
1:  wfe
    b       1b
2: // cpu id == 0

    // set stack before our code
    ldr     x1, =stack_start
    mov     sp, x1

    // clear bss
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, init_globals
    str     xzr, [x1], #8
    sub     w2, w2, #1
    b       3b

init_globals:
    bl StaticInitialize

4: bl main
   b  1b
