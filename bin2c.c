#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	if(argc != 4)
	{
		printf("Usage: %s <infile> <outfile> <array name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *infile  = fopen(argv[1], "rb");
	if(infile == NULL)
	{
		printf("Could not open '%s'.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	FILE *outfile = fopen(argv[2], "w");
	if(outfile == NULL)
	{
		printf("Could not open '%s'.\n", argv[2]);
	}

	fseek(infile, 0, SEEK_END);
	size_t file_size = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	fprintf(outfile, "/*\tThis file was automatically generated from the file %s\n", argv[1]);
	fprintf(outfile, "\t%s contains the raw byte stream of the entire file. \t\t\t*/\n\n", argv[3]);
	fprintf(outfile, "const unsigned long %s_size = %lu;\n", argv[3], file_size);
	fprintf(outfile, "const unsigned char %s[%lu] =\n{\n\t", argv[3], file_size);
	for(size_t i = 0; i < file_size - 1; i++)
	{
		unsigned c = fgetc(infile);
		fprintf(outfile, "0x%02x, ", c);
		
		if( (i % 12) == 11)
			fprintf(outfile, "\n\t");
	}
	unsigned c = fgetc(infile);
	fprintf(outfile, "0x%02x\n};\n", c);

	fclose(infile);
	fclose(outfile);
}
