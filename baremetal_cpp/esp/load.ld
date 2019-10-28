MEMORY
{
  dram0_0_seg :                         org = 0x3FFE8000, len = 0x14000
  iram1_0_seg :                         org = 0x40100000, len = 0x8000
}

PHDRS
{
  dram0_0_phdr PT_LOAD;
  dram0_0_bss_phdr PT_LOAD;
  iram1_0_phdr PT_LOAD;
}

/*  Default entry point:  */
ENTRY(karina_main)

SECTIONS
{
  .rodata : ALIGN(4)
  {
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    *(.gcc_except_table)
    *(.gnu.linkonce.e.*)
    *(.gnu.version_r)
    *(.eh_frame)
    /*  C++ constructor and destructor tables, properly ordered:  */
	. = ALIGN(4);
    init_array_start = ABSOLUTE(.);
    KEEP (*(EXCLUDE_FILE (*crtend.* *crtbegin.*) .ctors .ctors.*))
    init_array_end = ABSOLUTE(.);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /*  C++ exception handlers table:  */
    *(.gnu.linkonce.h.*)
    *(.dynamic)
    *(.gnu.version_d)
  } >dram0_0_seg :dram0_0_phdr

  .bss ALIGN(8) (NOLOAD) : ALIGN(4)
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);
    *(.dynsbss)
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    *(.scommon)
    *(.sbss2)
    *(.sbss2.*)
    *(.gnu.linkonce.sb2.*)
    *(.dynbss)
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
    heap_start = ABSOLUTE(.);
    heap_end = ORIGIN(dram0_0_seg) + LENGTH(dram0_0_seg);
  } >dram0_0_seg :dram0_0_bss_phdr
  
  .text : ALIGN(4)
  {
    . = ALIGN (16);
    *(.entry.text)
    *(.init.literal)
    *(.init)
    *(.literal .text .literal.* .text.* .stub .gnu.warning .gnu.linkonce.literal.* .gnu.linkonce.t.*.literal .gnu.linkonce.t.*)
    *(.fini.literal)
    *(.fini)
    *(.gnu.version)
  } >iram1_0_seg :iram1_0_phdr
}

PROVIDE ( ets_delay_us = 0x40002ecc );
