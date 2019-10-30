#ifndef _ESP8266_LEDS_H_
#define _ESP8266_LEDS_H_

#define PERIPHS_IO_MUX_FUNC   0x13
#define PERIPHS_IO_MUX_FUNC_S 4

#define PERIPHS_IO_MUX        0x60000800
#define PERIPHS_IO_MUX_MTDI_U (PERIPHS_IO_MUX + 0x04)
#define PERIPHS_IO_MUX_MTCK_U (PERIPHS_IO_MUX + 0x08)

#define FUNC_GPIO12           3
#define FUNC_GPIO13           3

#define BIT2  (1 << 2)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)

#define WRITE_PERI_REG(addr, val) (*((volatile unsigned int *)(addr))) = (unsigned int)(val)
#define READ_PERI_REG(addr) (*((volatile unsigned int *)(addr)))

#define PIN_FUNC_SELECT(PIN_NAME, FUNC) \
    WRITE_PERI_REG(PIN_NAME, (READ_PERI_REG(PIN_NAME) & (~(PERIPHS_IO_MUX_FUNC << PERIPHS_IO_MUX_FUNC_S))) | ( (((FUNC & BIT2) << 2) | (FUNC & 0x3)) << PERIPHS_IO_MUX_FUNC_S));


#define GPIO_OUTPUT_CATALOG_REGISTER (*((volatile unsigned int *)0x6000030C)) // Полный каталог пинов, бит 0 - input, бит 1 - output
#define GPIO_OUTPUT_MASK_REGISTER    (*((volatile unsigned int *)0x60000310)) // Или можно ставить маской output-ы
#define GPIO_INPUT_MASK_REGISTER     (*((volatile unsigned int *)0x60000314)) // Или исключать инверсной маской input-ы

#define GPIO_RAW_OUTPUT_VALUES_REGISTER        (*((volatile unsigned int *)0x60000300)) // Полный каталог значений output пинов
#define GPIO_HIGH_OUTPUT_VALUES_MASK_REGISTER  (*((volatile unsigned int *)0x60000304)) // Или можно включать output пины в high маской
#define GPIO_LOW_OUTPUT_VALUES_MASK_REGISTER   (*((volatile unsigned int *)0x60000308)) // Или исключать инверсной маской в low

#define GPIO_RAW_INPUT_VALUES_REGISTER (*((volatile unsigned int *)0x60000318)) // Полный каталог значений input пинов. Масок не предусмотрено :)

#define GREEN_LED BIT12
#define RED_LED   BIT13

#define SET_LED_STATUS(ledColor, ledStatus) ledStatus ? GPIO_HIGH_OUTPUT_VALUES_MASK_REGISTER = ledColor : GPIO_LOW_OUTPUT_VALUES_MASK_REGISTER = ledColor;

#define SWITCH_LEDS { \
                        unsigned int status = GPIO_RAW_OUTPUT_VALUES_REGISTER & (GREEN_LED | RED_LED); \
                        GPIO_LOW_OUTPUT_VALUES_MASK_REGISTER = status & (GREEN_LED | RED_LED); \
                        GPIO_HIGH_OUTPUT_VALUES_MASK_REGISTER = ~status & (GREEN_LED | RED_LED); \
                    }


inline static void init_leds(void)
{
    // Микшируем пины GPIO-переферии, соответствующие светодиодам, с процессорными функциями "просто I/O"
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);

    // Переключаем пины GPIO-переферии, соответствующие светодиодам, в режим OUTPUT
    GPIO_OUTPUT_MASK_REGISTER = GREEN_LED | RED_LED;
}

#endif // _ESP8266_LEDS_H_
