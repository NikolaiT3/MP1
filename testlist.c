#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv) {
	int blockSize = 128;
	int memSize = 512 * 1024;
	int c;

	if (!(argc == 1 || argc == 3 || argc == 5)) {
		fprintf(stderr, "The number of arguments is incorrect.\n");
		return 0;
	}
	else printf("The number of args is correct!\n");

	opterr = 0;

	while ((c = getopt(argc, argv, "b:s:")) != -1)
		if (atoi(optarg) == 0) {
			break;
		}
		else {
			switch(c) {
			case 'b':
				// printf("optarg: %d\n", atoi(optarg));
				blockSize = atoi(optarg);
				break;
			case 's':
				// printf("optarg: %d\n", atoi(optarg));
				memSize = atoi(optarg);
				break;
			case '?':
				if (isprint(optopt))
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
			}
		}

	printf("blockSize = %d, memSize = %d\n", blockSize, memSize);

	return 0;
}
