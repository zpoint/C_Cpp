#include <sys/types.h>
#include "errorlog.c"
typedef struct { // open Client struct per connected client
		int fd; // fd, or -1 if available
		uid_t uid;
}Client;
#include <syslog.h>
#include "opend.h"
#include "loop.c"
#include "init_daemon.c"

int debug, oflag, client_size, log_to_stderr;
char errmsg[MAXLINE];
char *pathname;
Client *client = NULL;

int main(int argc, char *argv[])
{
		int c;
		log_open("open.serv", LOG_PID, LOG_USER);

		opterr = 0; // don't want getopt() writing to stderr
		while ((c = getopt(argc, argv, "d")) != EOF)
		{
				switch (c)
				{
						case 'd': // debug
								debug = log_to_stderr = 1;
								break;

						case '?':
								err_quit("unrecognized option: -%c", optopt);
				}
		}

		if (debug == 0)
				daemonize("opend");

		loop(); // never returns
}
