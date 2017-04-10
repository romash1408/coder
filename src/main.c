#include <stdio.h>
#include <stdlib.h>
#include "coder.h"
#include "command.h"

int main(int argc, char** argv)
{
	if(argc < 4 )
	{
		printf("Usage: %s encode|decode <input file> <output file>\n", argv[0]);
		return 1;
	}
	
	int result;
	if(strcmp(argv[1], "encode") == 0)
	{
		result = encode_file(argv[2], argv[3]);
	}
	else if(strcmp(argv[1], "decode") == 0)
	{
		result = decode_file(argv[2], argv[3]);
	}
	else
	{
		printf("Undefined command %s. Please, use encode or decode.\n", argv[1]);
		return 1;
	}
	
	if(result == 0)
	{
		printf("All done successfully\n");
	}
	else
	{
		printf("Some troubles when %s :(\n", argv[1]);
		return 1;
	}
	
	return 0;
}