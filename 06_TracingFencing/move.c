#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 4096

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(
			stderr,
			"Invalid number of arguments.\n"
			"Usage: %s infile outfile\n",
			argv[0]
		);
		return EXIT_FAILURE;
	}

	const char* infile_path  = argv[1];
	const char* outfile_path = argv[2];

	FILE* infile = fopen(infile_path, "rb");
	if (infile == NULL) {
		fprintf(
			stderr,
			"Can't open input file %s\n"
			"Error: %s\n",
			infile_path, strerror(errno)
		);
		return EXIT_FAILURE;
	}
	
	FILE* outfile = fopen(outfile_path, "wb");
	if (outfile == NULL) {
		fprintf(
			stderr,
			"Can't open output file %s\n"
			"Error: %s\n",
			outfile_path, strerror(errno)
		);
		fclose(infile);
		return EXIT_FAILURE;
	}

	/* Moving */
	char buf[BUF_SIZE];
	while (!feof(infile)) {
		const size_t n_read = fread(buf, sizeof(*buf), BUF_SIZE, infile);
		if (ferror(infile)) {
			fprintf(
				stderr,
				"Error: cannot read from infile\n"
			);

			fclose(outfile);
			fclose(infile);

			remove(outfile_path);

			return EXIT_FAILURE;
		}

		const size_t n_write = fwrite(buf, n_read, sizeof(char), outfile);
		if (ferror(outfile)) {
			fprintf(
				stderr,
				"Error: cannot write to outfile\n"
			);

			fclose(outfile);
			fclose(infile);

			remove(outfile_path);

			return EXIT_FAILURE;
		}
	}

	fclose(outfile);
	fclose(infile);

	remove(infile_path);
}