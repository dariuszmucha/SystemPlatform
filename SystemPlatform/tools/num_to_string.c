/*
 * num_to_string.c
 *
 * Created: 06/09/2015 19:21:37
 *  Author: dariusz.mucha
 */ 
#include "num_to_string.h"

void num_to_string_hex(uint32_t num, char* string)
{
	uint8_t shift, shift_bits;
	uint8_t idx = 0;
	string[idx++] = '0';
	string[idx++] = 'x';
	for(shift = 0; shift < 8; shift++)
	{
		shift_bits = (7 - shift) * 4;
		string[idx] = (char)((num >> shift_bits) & 0x0F);
		if(string[idx] >= 0x0A) string[idx] += 0x37;
		else string[idx] += 0x30;
		idx++;
	}
}