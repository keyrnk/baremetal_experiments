I've spent a lot of time solving following problems and some of them are still opened:

1. It's necessary to stop slave cores in start.s

2. Despite of BCM2835 Datasheet description it's necessary to write 0x03 instead of 0x01 to AUX_MU_LCR_REG for enabling 8 bit mode

3. Baud rate register value is used for baud rate evaluation in a following way:
baud_rate = (system_clock_freq) / 8 * (baud_rate_reg + 1)
Thus, for baud_rate_reg = 270 and default system_clock_freq = 250 Mhz (although I saw 400 Mhz for Raspi 3), baud rate value is 115200

