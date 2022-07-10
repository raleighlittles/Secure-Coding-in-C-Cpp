#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define	LINELENGTH 80

char *decrypt(char*, int);
int usage(char*);

int main(int argc, char *argv[])
{
	char *inbuf, *keystr, *outbuf;
	char *errmsg;
	FILE *infile, *keyfile, *outfile;
	int oflag=0;

	if (argc != 3 && argc != 4) {
		 /* the error message won't be more than 80 chars */
		errmsg = (char *)malloc(LINELENGTH);
		sprintf(errmsg, "sorry, %s\nUsage: caesar secret_file keys_file [output_file]\n", getenv("USER"));
		usage(errmsg);
		free(errmsg);
		exit(1);
	}

	if ((infile = fopen(argv[1], "r")) == NULL)
		errx(1, "Cannot open input file.");

	if ((keyfile = fopen(argv[2], "r")) == NULL)
		errx(1, "Cannot open keys file.");

	if (argc == 4) {
		if ((outfile = fopen(argv[3], "w")) == NULL)
			errx(1, "Cannot open output file.");
		oflag=1;
	}

	if (!(inbuf = malloc(LINELENGTH)))
		errx(1, "Couldn't allocate memory.");

	while (fgets(inbuf, 100, infile) && !feof(infile)) {
		/* the key won't be more than 4 */
		if (!(keystr = malloc(4*sizeof(char))))
			errx(1, "Couldn't allocate memory.");
		fgets(keystr, 4*sizeof(char), keyfile);
		outbuf = decrypt(inbuf, atoi(keystr));
		fputs(outbuf, (oflag ? outfile : stdout));
	}
}

char *decrypt(char *msg, int rot)
{
	int i;
	char ch, *outbuf;

	if ((rot < 0) || ( rot >= 26))
		errx(i, "bad rotation value");

	if(!(outbuf = malloc(100)))
		errx(1, "Couldn't allocate memory.");

	i = 0;
	while (ch = msg[i]) {
		outbuf[i] = isupper(ch) ? ('A' + (ch - 'A' + rot) % 26) : islower(ch) ? ('a' + (ch - 'a' + rot) % 26) : ch;
		++i;
	}
	return outbuf;
}

int usage(char *errmsg)
{
	fprintf(stderr, errmsg);
	free(errmsg);
}
