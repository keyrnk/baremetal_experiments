#define MMIO_BASE       0x3F000000

#define AUX_ENABLE_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215004))
#define AUX_MU_IO_REG       ((volatile unsigned int*)(MMIO_BASE+0x00215040))
#define AUX_MU_IER_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215044))
#define AUX_MU_IIR_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215048))
#define AUX_MU_LCR_REG      ((volatile unsigned int*)(MMIO_BASE+0x0021504C))
#define AUX_MU_MCR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215050))
#define AUX_MU_LSR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215054))
#define AUX_MU_MSR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215058))
#define AUX_MU_SCRATCH_REG  ((volatile unsigned int*)(MMIO_BASE+0x0021505C))
#define AUX_MU_CNTL_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215060))
#define AUX_MU_STAT_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215064))
#define AUX_MU_BAUD_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215068))
#define GPFSEL1_REG        ((volatile unsigned int*)(MMIO_BASE+0x00200004))
#define GPPUD_REG           ((volatile unsigned int*)(MMIO_BASE+0x00200094))
#define GPPUDCLK0_REG       ((volatile unsigned int*)(MMIO_BASE+0x00200098))

void WriteToRegister(volatile unsigned int* reg, const unsigned int val)
{
    *reg = val;
}

void ReadFromRegister(volatile unsigned int* reg, unsigned int* val)
{
    *val = *reg;
}

static void SetUpGPIO(void)
{
    //alternate pin 14 and pin 15 to miniuart tx/rx mode
    unsigned int reg;
    ReadFromRegister(GPFSEL1_REG, &reg);

    //clean pin 14 bits (12-14)
    reg &= ~((7 << 12) | (7 << 15));

    //set pin 14/15 alt5 function for tx1/rx1
    reg |= (2 << 12);
    reg |= (2 << 15);

    WriteToRegister(GPFSEL1_REG, reg);

    WriteToRegister(GPPUD_REG, 0);

    //according to broadcom documentation we need to wait 150 cycles
    const unsigned int CyclesNum = 150;
    unsigned int i;
    for(i = 0; i < CyclesNum; i++)
        asm volatile("nop");

    WriteToRegister(GPPUDCLK0_REG, ((1<<14)|(1<<15)));
    for(i = 0; i < CyclesNum; i++)
        asm volatile("nop");

    WriteToRegister(GPPUDCLK0_REG, 0);
}

void InitMiniUart()
{
    unsigned int auxEnableReg;
    ReadFromRegister(AUX_ENABLE_REG, &auxEnableReg);
    auxEnableReg |= 1;
    WriteToRegister(AUX_ENABLE_REG, auxEnableReg);
    WriteToRegister(AUX_MU_IER_REG, 0);

    const unsigned int FifoClearEnable = 0xC6;
    WriteToRegister(AUX_MU_IIR_REG, FifoClearEnable);

    const unsigned int eightBitUartMode = 3;
    WriteToRegister(AUX_MU_LCR_REG, eightBitUartMode);
    WriteToRegister(AUX_MU_MCR_REG, 0);
    WriteToRegister(AUX_MU_CNTL_REG, 0);
    WriteToRegister(AUX_MU_BAUD_REG, 270);

    SetUpGPIO();

    const unsigned int ReceiverTransmitterEnable = 0x03;
    WriteToRegister(AUX_MU_CNTL_REG, ReceiverTransmitterEnable);
}

char GetChar()
{
    const unsigned int DataReadyBit = 0x01;
    char r;
    do {
        asm volatile("nop");
    }
    while(!(*AUX_MU_LSR_REG & DataReadyBit));

    r=(char)(*AUX_MU_IO_REG);
    return r=='\r'?'\n':r;
}

void PutChar(const char ch)
{
    const unsigned int DataReadyBit = 0x20;
    while (1)
    {
        unsigned int lsrRegVal;
        ReadFromRegister(AUX_MU_LSR_REG, &lsrRegVal);
        if (lsrRegVal & DataReadyBit)
            break;
    }

    WriteToRegister(AUX_MU_IO_REG, (const unsigned int)ch);
}

void PutStr(const char* s)
{
    while(*s != '\0')
    {
        if (*s == '\n')
            PutChar('\r');

        PutChar(*s);
        s++;
    }
}

void main(void)
{
    InitMiniUart();

    PutStr("Hello fucking world!\n");
    while(1)
    {
        PutChar(GetChar());
    }
}
