/*
 * libn5110.c
 *
 * Created: 29/01/2016 21:39:53
 *  Author: dariusz.mucha
 */ 

#include "libn5110.h"
#include "libspi.h"
#include "os_delay.h"
#include "os_hal.h"

#define N5110_FONT_HEIGHT		8
#define N5110_FONT_WIDTH		6
#define N5110_LINES				N5110_PIXEL_HEIGHT / N5110_FONT_HEIGHT
#define N5110_CHAR_PER_LINE		N5110_PIXEL_WIDTH / N5110_FONT_WIDTH

typedef enum {
	n5110_command,
	n5110_data
} n5110_data_command_t;

static const uint8_t font_table[][N5110_FONT_WIDTH] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},		// NULL
	{0x7C, 0x0A, 0x09, 0x0A, 0x7C, 0x00},		// A
	{0x7F, 0x49, 0x49, 0x49, 0x76, 0x00},		// B
	{0x3E, 0x41, 0x41, 0x41, 0x22, 0x00},		// C
	{0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00},		// D
	{0x7F, 0x49, 0x49, 0x49, 0x41, 0x00},		// E
		
	{0x1F, 0x05, 0x05, 0x00, 0x00, 0x00},		// F
	{0x0E, 0x11, 0x13, 0x00, 0x00, 0x00},		// G
	{0x1F, 0x04, 0x1F, 0x00, 0x00, 0x00},		// H
	{0x11, 0x1F, 0x11, 0x00, 0x00, 0x00},		// I
	{0x11, 0x11, 0x0F, 0x00, 0x00, 0x00},		// J
	{0x1F, 0x04, 0x11, 0x00, 0x00, 0x00},		// K
	{0x1F, 0x10, 0x10, 0x00, 0x00, 0x00},		// L
		
	{0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00},		// M OK
		
	{0x1F, 0x15, 0x0A, 0x00, 0x00, 0x00},		// N
	{0x1F, 0x15, 0x0A, 0x00, 0x00, 0x00},		// O
		
	{0x7F, 0x09, 0x09, 0x09, 0x06, 0x00},		// P OK
		
	{0x1F, 0x15, 0x0A, 0x00, 0x00, 0x00},		// Q
		
	{0x7F, 0x09, 0x19, 0x29, 0x46, 0x00},		// R OK
		
	{0x1F, 0x15, 0x0A, 0x00, 0x00, 0x00},		// S
		
	{0x01, 0x01, 0x7F, 0x01, 0x01, 0x00},		// T OK
	{0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00},		// U OK
		
	{0x1F, 0x15, 0x0A, 0x00, 0x00, 0x00},		// W
	{0x1F, 0x15, 0x0A, 0x00, 0x00, 0x00},		// Z
};

static const uint8_t ascii_lut[] = {
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x00 - 0x0F
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x10 - 0x1F
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x20 - 0x2F
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x30 - 0x3F
 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, // 0x40 - 0x4F
16, 17, 18, 19, 20, 21, 22, 23,  0,  0,  0,  0,  0,  0,  0,  0, // 0x50 - 0x5F
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x60 - 0x6F
 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 0x70 - 0x7F
};

static void N5110_clear(void)
{
	uint8_t i = 0;
	for(i = 0; i < N5110_LINES * N5110_CHAR_PER_LINE; i++)
	{
		N5110_Print(" \0");
	}
}

static void N5110_datacommand_change(n5110_data_command_t setting)
{
	if(setting == n5110_command)
	{
		N5110_PINS_SET &= ~(1 << N5110_DC);
	}
	else if(setting == n5110_data)
	{
		N5110_PINS_SET |= (1 << N5110_DC);
	}
}

void N5110_Init(void)
{
	N5110_PINS_OUT |= (1 << N5110_RST) | (1 << N5110_DC) | (1 << N5110_SCE);
	SPI_MasterInit(spi_clock_div_16, 1);
	N5110_PINS_SET &= ~(1 << N5110_RST) & ~(1 << N5110_DC) & ~(1 << N5110_SCE);
	
	os_delay_ms(1);
	N5110_PINS_SET |= (1 << N5110_RST);
	
	SPI_MasterTransmit(0x21);
	SPI_MasterTransmit(0xB1);
	SPI_MasterTransmit(0x04);
	SPI_MasterTransmit(0x14);
	SPI_MasterTransmit(0x20);
	SPI_MasterTransmit(0x0C);
	
	N5110_clear();
}

void N5110_Transfer_Buf(const uint8_t *data, uint16_t buff_size)
{
	uint16_t i = 0;
	N5110_datacommand_change(n5110_data);
	
	for(i = 0; i < buff_size; i++)
	{
		SPI_MasterTransmit(data[i]);
	}
}

void N5110_Print(const char *data)
{
	N5110_datacommand_change(n5110_data);
	uint8_t i = 0;
	uint8_t j = 0;
	while(data[i] != 0)
	{
		const uint8_t* font = font_table[ ascii_lut[ (uint8_t)data[i]] ];
		for(j = 0; j < N5110_FONT_WIDTH; j++)
		{
			SPI_MasterTransmit(font[j]);
		}
		i++;
	}
}