heap_size = 1M;
stack_size = 1M;

SECTIONS
{
    . = 0x80000;
    .text : { KEEP(*(.text.boot)) *(.text .text.* .gnu.linkonce.t*) }
    .rodata : { *(.rodata .rodata.* .gnu.linkonce.r*) }
    PROVIDE(_data = .);
    .data : { *(.data .data.* .gnu.linkonce.d*) }
    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    } 
    . = ALIGN(16);
    .init.array :
    {
        init_array_start = .;
        *(.init_array)
        *(.init_array.*)
        init_array_end = .;
    }
    . = ALIGN(16);
    .heap : {
    	heap_start = .;
	. = . + heap_size;
	heap_end = .;
    }
    .stack : {
        stack_end = .;
        . = . + stack_size;
        stack_start = .;
    }
    _end = .;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start)>>3;


