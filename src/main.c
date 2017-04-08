#include <stdio.h>
#include <stdlib.h>
#include "coder.h"
#include "command.h"

int main(int argc, char** argv)
{
	FILE* out = fopen("output", "rb");
	if(!out)
	{
		printf("Error 0\n");
		return 1;
	}
	CodeUnit unit;
	
	//encode(0x7B, &unit);//0111 1011
	read_next_code_unit(out, &unit);
	if(0x7B != decode(&unit))
		printf("Error 1\n");
	else
		print_code_unit(&unit);
	
	//encode(0xC27A, &unit);//1100 0010 0111 1010
	read_next_code_unit(out, &unit);
	if(0xC27A != decode(&unit))
		printf("Error 2\n");
	else
		print_code_unit(&unit);
	
	//encode(0x3BAA10, &unit);
	read_next_code_unit(out, &unit);
	if(0x3BAA10 != decode(&unit))
		printf("Error 3\n");
	else
		print_code_unit(&unit);
	
	//encode(0x3BAA1029, &unit);
	read_next_code_unit(out, &unit);
	if(0x3BAA1029 != decode(&unit))
		printf("Error 4\n");
	else
		print_code_unit(&unit);
	
	fclose(out);
	
	return 0;
}