.section ".text.boot"

.global _start

_start:
    // set stack before our code
    ldr     r0, =_start
    mov     sp, r0
    bl      main
    b       .
