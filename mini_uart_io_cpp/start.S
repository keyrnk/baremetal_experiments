.extern main
.extern StaticInitialize

.section ".text.boot"
.global interrupt_vector

interrupt_vector:   
   ldr x5, reset_handler_ptr
   br x5
   ldr x5, undefined_handler_ptr
   br x5
   ldr x5, swi_handler_ptr
   br x5
   ldr x5, prefetch_handler_ptr
   br x5
   ldr x5, data_handler_ptr
   br x5
   ldr x5, unused_handler_ptr
   br x5
   ldr x5, irq_handler_ptr
   br x5
   ldr x5, fiq_handler_ptr
   br x5

reset_handler_ptr: .dword start
undefined_handler_ptr: .dword hang
swi_handler_ptr: .dword hang
prefetch_handler_ptr: .dword hang
data_handler_ptr: .dword hang
unused_handler_ptr: .dword hang
irq_handler_ptr: .dword hang
fiq_handler_ptr: .dword hang

start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    // cpu id > 0, stop
1:  wfe
    b       1b
2: // cpu id == 0
   
   ldr x1,=interrupt_vector
   mov x2,#0x0000
   ldp x3, x18, [x1], #128
   stp x3, x18, [x2], #128

   ldp x3, x10, [x1], #64
   stp x3, x10, [x2], #64

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

hang: b hang
