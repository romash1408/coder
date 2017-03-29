#include <stdio.h>
#include "coder.h"
#include "command.h"

int main(int argc, char** argv)
{
	CodeUnit unit;
	encode(0x7B, &unit);//0111 1011
	print_code_unit(&unit);
	encode(0xC27A, &unit);//1100 0010 0111 1010
	print_code_unit(&unit);
	encode(0x3BAA10, &unit);
	print_code_unit(&unit);
	encode(0x3BAA1029, &unit);
	print_code_unit(&unit);
	return 0;
}