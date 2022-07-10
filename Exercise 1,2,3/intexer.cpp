// intexer.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct sigrecord {
	int signum;
	char signame[20];
	char sigdesc[100];
};

int main(int argc, char* argv[]) {
	char c;
	int i, j;
	int idx;
	int size;
	char input[10];

	char *file;
	char *full_path;
	FILE *in;
	struct sigrecord *sigdb;

	if (argc != 2) {
		printf("Usage: %s data_base\n", argv[0]);
		return 0;
	}

	file = getenv("DATA_PATH");

	if (file != '\0') {
		full_path = (char *)malloc(1000 + strlen(argv[1])+1);
		strncpy(full_path, file, 999); //cannot malloc because user can change size
		if (full_path[strlen(full_path)-1]!='/') {
			full_path=strcat(full_path,"/");
		}
		full_path=strcat(full_path, argv[1]);
		printf("path:%s", full_path);
	}
	else {
		full_path=argv[1];
	}

	if ((in = fopen(full_path, "r"))== NULL) {
		printf("Cannot open input file \n");
		goto free_path;
	}

	fscanf(in, "%i", &size);
	sigdb = (struct sigrecord *) malloc(size * sizeof(struct sigrecord));
	if (sigdb == NULL) goto close_files;

	for (i = 0; i < size; i++) {
		j = 0;
		fscanf(in, "%i", &sigdb[i].signum);
		fscanf(in, "%s", sigdb[i].signame);

		// read in description
		while ((c = (char)fgetc(in)) != EOF) {

			// don't read more than 100 chars or until a line feed or carriage return is found
			if ( (j == 99) || (c == '\r' /* 0x0A */ ) || (c == '\n' /* 0x0D */ ) ) break;
			sigdb[i].sigdesc[j] = c;
			j++;
		} // read end of file not reached
		sigdb[i].sigdesc[j] = '\0';
	} // end for each signal record

	/* Loop until 'q' and print out signal information */

	while (1) {
		puts("Enter a signal number or 'q' to quit:");
		if (NULL == fgets(input, 10, stdin)) {
			fprintf(stderr, "input error");
			break;
		}
		if (input[0] == 'q') {
			break;
		}
		else {
			idx = atoi(input);
			if (idx < size) {
				printf("%d %s %s\n", sigdb[idx].signum, sigdb[idx].signame, sigdb[idx].sigdesc);
			}
			else {
				printf("Value out of range.\n");
			}
		}
	}

close_files:
	fclose(in);

	free_path:
	free(full_path);

	return 0;
}
