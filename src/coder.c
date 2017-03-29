#include "coder.h"

static const uint32_t MaxVal[] = {0, (1 << 7) - 1, (1 << 11) - 1, (1 << 16) - 1, (1 << 21) - 1};
static const byte Header[] = {0x80, 0x00, 0xC0, 0xE0, 0xF0};
static const char *HeaderStr[] = {"10", "0", "110", "1110", "11110"};
static const byte BodyLen[] = {6, 7, 5, 4, 3};
static const char BodyMask[] = {(1 << 6) - 1, (1 << 7) - 1, (1 << 5) - 1, (1 << 4) - 1, (1 << 3) - 1};

int encode(uint32_t code_point, CodeUnit *code_unit)
{
	int error = 0;
	for(code_unit->length = 1; code_point > MaxVal[code_unit->length]; ++code_unit->length);
	
	if(code_unit->length > MaxCodeLength) 
	{
		code_unit->length = MaxCodeLength;
		error = 1;
	}
	
	for(int i = code_unit->length - 1; i > 0; --i)
	{
		code_unit->code[i] = Header[0] + (BodyMask[0] & code_point);
		code_point >>= BodyLen[0];
	}
	
	code_unit->code[0] = Header[code_unit->length] + (BodyMask[code_unit->length] & code_point);
	
	return error;
}

uint32_t decode(const CodeUnit *code_unit)
{
	return 0;
}

int read_next_code_unit(FILE *in, CodeUnit *code_unit)
{
	return 0;
}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{
	return 0;
}

void print_code_unit(const CodeUnit *unit)
{
	printf("%s_", HeaderStr[unit->length]);
	for(int bit = 1 << (BodyLen[unit->length] - 1); bit; bit >>= 1)
	{
		putchar('0' + ((unit->code[0] & bit) > 0));
	}
	
	for(int i = 1; i < unit->length; ++i)
	{
		printf(" %s_", HeaderStr[0]);
		for(int bit = 1 << (BodyLen[0] - 1); bit; bit >>= 1)
		{
			putchar('0' + ((unit->code[i] & bit) > 0));
		}
	}
	
	putchar('\n');
}