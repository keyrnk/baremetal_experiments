#ifndef _KARINA_MAIN_H_
#define _KARINA_MAIN_H_

extern "C" {
    extern unsigned char _bss_start;
    extern unsigned char _bss_end;

    extern void ets_delay_us(unsigned int us);
}

inline static void mem_clr_bss(void)
{
    unsigned char *ptr = &_bss_start;
    while (ptr < &_bss_end)
        *ptr++ = 0;
}

#endif // _KARINA_MAIN_H_
