#define PERIPHERAL_BASE_ADDRESS 0x3F000000

#define AUX_ENABLE_REG 0x3F215004

#define AUX_MU_IO_REG 0x3F215040
#define AUX_MU_IIR_REG 0x3F215044
#define AUX_MU_IER_REG 0x3F215048
#define AUX_MU_LCR_REG 0x3F21504C
#define AUX_MU_MCR_REG 0x3F215050
#define AUX_MU_LSR_REG 0x3F215054
#define AUX_MU_MSR_REG 0x3F215058
#define AUX_MU_SCRATCH_REG 0x3F21505C
#define AUX_MU_CNTL_REG 0x3F215060
#define AUX_MU_STAT_REG 0x3F215064
#define AUX_MU_BAUD_REG 0x3F215068

#define GPFSEL1 0x3F200004
#define GPPUD 0x3F200094
#define GPPUDCLK0 0x3F200098

void WriteToRegister(unsigned int reg, const unsigned int val)
{
	*(volatile unsigned int*)reg = val;
}

void ReadFromRegister(unsigned int reg, unsigned int* val)
{
	*val = *(volatile unsigned int*)reg;
}

static void SetUpGPIO(void)
{
	//alternate pin 14 and pin 15 to miniuart tx/rx mode
	unsigned int reg;
	ReadFromRegister(GPFSEL1, &reg);

	//clean pin 14 bits (12-14)
	reg &= ~(7 << 12);

	//clean pin 15 bits (15-17)
	reg &= ~(7 << 15);

	//set pin 14/15 alt5 function for tx1/rx1
	reg |= (2 << 12);
	reg |= (2 << 15);

	WriteToRegister(GPFSEL1, reg);

	WriteToRegister(GPPUD, 0);

	//according to broadcom documentation we need to wait 150 cycles
	const unsigned int CyclesNum = 150; 
	unsigned int i;
	for(i = 0; i < CyclesNum; i++) 
		dummy(i);

    	WriteToRegister(GPPUDCLK0,(1<<14)|(1<<15));
    	for(i = 0; i < CyclesNum; i++) 
		dummy(i);

    	WriteToRegister(GPPUDCLK0, 0);
}

void InitMiniUart()
{
	const unsigned int MiniUartEnable = 0x1;
	WriteToRegister(AUX_ENABLE_REG, MiniUartEnable);
	WriteToRegister(AUX_MU_IER_REG, 0);
	
	const unsigned int FifoClearEnable = 0xC6;
	WriteToRegister(AUX_MU_IIR_REG, FifoClearEnable);
	
	const unsigned int eightBitUartMode = 0x01;
	WriteToRegister(AUX_MU_LCR_REG, eightBitUartMode);
	WriteToRegister(AUX_MU_MCR_REG, 0);
	WriteToRegister(AUX_MU_CNTL_REG, 0);
	WriteToRegister(AUX_MU_BAUD_REG, 270);

	SetUpGPIO();

	const unsigned int ReceiverTransmitterEnable = 0x03;
	WriteToRegister(AUX_MU_CNTL_REG, ReceiverTransmitterEnable);
}

void GetChar(char* ch)
{
	const unsigned int DataReadyBit = 0x01;
	while (1)
	{
		unsigned int lsrRegVal;
		ReadFromRegister(AUX_MU_LSR_REG, &lsrRegVal);
		if (lsrRegVal & DataReadyBit)
			break;
	}

	ReadFromRegister(AUX_MU_IO_REG, (unsigned int*)ch);
}

void PutChar(const char ch)
{
	WriteToRegister(AUX_MU_IO_REG, (const unsigned int)ch);
}

void notmain(void)
{
	InitMiniUart();

	while(1)
	{
		char ch;
		GetChar(&ch);
		PutChar(ch);
	}
}
