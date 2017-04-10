#include "command.h"
#include "coder.h"
#include <inttypes.h>

int encode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "r");
	if(!in) return 1;
	FILE *out = fopen(out_file_name, "wb");
	if(!out)
	{
		fclose(in);
		return 1;
	}
	
	uint32_t cp;
	CodeUnit cu;
	while(!feof(in) && fscanf(in, "%"SCNx32, &cp))
	{
		if(encode(cp, &cu) != 0) continue;
		write_code_unit(out, &cu);
	}
	
	fclose(in);
	fclose(out);
	return 0;
}

int decode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in = fopen(in_file_name, "rb");
	if(!in) return 1;
	FILE *out = fopen(out_file_name, "w");
	if(!out)
	{
		fclose(in);
		return 1;
	}
	
	CodeUnit cu;
	while(!feof(in))
	{
		if(read_next_code_unit(in, &cu) != 0) continue;
		fprintf(out, "%"PRIx32"\n", decode(&cu));
	}
	
	fclose(in);
	fclose(out);
	return 0;
}