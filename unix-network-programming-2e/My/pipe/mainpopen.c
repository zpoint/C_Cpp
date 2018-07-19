#include "../../lib/unpipc.h"

int main(int argc, char **argv)
{
		size_t n;
		char buff[MAXLINE], command[MAXLINE];
		FILE *fp;

		/* read pathname */
		Fgets(buff, MAXLINE, stdin);
		n = strlen(buff); /* fgets guarantees null byte at end */
		if (buff[n - 1] == '\n')
				buff[n - 1] = '\0'; /* delete newline from fgets() */

		snprintf(command, sizeof(command), "cat %s", buff);
		fp = Popen(command, "r");

		/* copy from pipe to standard output */
		while (Fgets(buff, MAXLINE, fp) != NULL)
				Fputs(buff, stdout);

		Pclose(fp);
		exit(0);
}
