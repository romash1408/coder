#include "coder.h"

static const uint32_t MaxVal[] = {0,	0x7F,	0x7FF,	0xFFFF,	0x1FFFFF,	0x3FFFFFF, 	0xFFFFFFFF};
static const byte Header[] = 	 {0x80,	0x00,	0xC0, 	0xE0, 	0xF0, 		0xF8, 		0xFC};
static const char *HeaderStr[] = {"10",	"0",	"110", 	"1110", "11110", 	"111110", 	"111111"};
static const byte BodyLen[] = 	 {6,	7,		5, 		4,		3,			2,			2};
static const char BodyMask[] = 	 {0x3F,	0x7F, 	0x1F, 	0x0F, 	0x07,		0x03,		0x03};

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
	uint32_t ret = 0;
	ret = code_unit->code[0] & BodyMask[code_unit->length];
	
	for(int i = 1; i < code_unit->length; ++i)
	{
		ret <<= BodyLen[0];
		ret += code_unit->code[i] & BodyMask[0];
	}
	return ret;
}

static int check_head_byte(const byte _head, const int _num)
{
	return !((_head & ~BodyMask[_num]) ^ Header[_num]);
}

int read_next_code_unit(FILE *in, CodeUnit *code_unit)
{
	if(!code_unit) return 1;
	code_unit->length = 0;
	
	byte head, len;
	do{
		if(feof(in)) return 1;
		fread(&head, 1, 1, in);
	} while(check_head_byte(head, 0));
	code_unit->code[0] = head;
	
	for(len = 1; len <= MaxCodeLength; ++len)
		if(check_head_byte(head, len)) break;
	
	if(len > MaxCodeLength) return 1;
	if(len > 1) if(fread(code_unit->code + 1, 1, len - 1, in) != len - 1) return 1;
	code_unit->length = len;
	return 0;
}

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{
	return fwrite(code_unit->code, sizeof(*code_unit->code), code_unit->length, out) != code_unit->length;
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