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
2:  // cpu id == 0

    // set stack before our code
    ldr     x1, =_start
    mov     sp, x1

    // clear bss
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
3:  cbz     w2, init_globals
    str     xzr, [x1], #8
    sub     w2, w2, #1
    b       3b

init_globals:
    ldr     x1, =__init_array_start
    ldr     x2, =__init_array_end
//init_loop:
    sub x4, x2, x1
    cbz     x4, 4f
    ldr     x3, [x1], #8
    blr     x3
    //sub     w2, w2, #1
 //   b       init_loop
    

4: bl main
   b  1b
