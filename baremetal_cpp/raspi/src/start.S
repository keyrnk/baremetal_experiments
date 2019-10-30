.extern main
.extern GlobalInitialize
.extern stack_start

.section ".text.boot"
.global interrupt_vector

interrupt_vector:   
/*   ldr x5, reset_handler_ptr
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
*/
start:
    // read cpu id, stop slave cores
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, continue
    // cpu id > 0, stop 
    wfe
    b       hang

continue: 
    // cpu id == 0
/*    msr DAIFClr, #15

    ldr sp,=interrupt_vector
    mov x1,#0x0000
    ldp x2, x17, [x0], #128
    stp x2, x17, [x1], #128

    ldp x2, x9, [x0], #64
    stp x2, x9, [x1], #64
*/
    //set interrupt stacks
    ldr x0, =stack_start
/*    mov x1, #0x1000

    msr DAIFSet, #2
    mov sp,x0
    sub x0,x0,x1

    msr DAIFSet, #1
    mov sp,x0
    sub x0,x0,x1

    msr DAIFClr, #15
 */
    // set stack
    mov sp,x0

    // clear bss
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size
bss_loop:  
    cbz     w2, init_globals
    str     xzr, [x1], #8
    sub     w2, w2, #1
    b       bss_loop

init_globals:
    bl GlobalInitialize

    bl main
    b  hang

hang: b hang
