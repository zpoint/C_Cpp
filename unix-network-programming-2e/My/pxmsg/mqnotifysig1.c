#include "../../lib/unpipc.h"

mqd_t mqd;
void *buff;
struct mq_attr attr;
struct sigevent sigev;

static void sig_usr1(int);

int main(int argc, char **argv)
{
		if (argc != 2)
				err_quit("usage: mqnotifysig1 <name>");

		/* open queue, get attributes, allocate read buffer */
		mqd = Mq_open(argv[1], O_RDONLY);
		Mq_getattr(mqd, &attr);
		buff = Malloc(attr.mq_msgsize);

		/* establish signal handler, enable notification */
		Signal(SIGUSR1, sig_usr1);
		sigev.sigev_notify = SIGEV_SIGNAL;
		sigev.sigev_signo = SIGUSR1;
		Mq_notify(mqd, &sigev);

		for ( ; ; ) /* signal handler does everything */
		{
				pause();
		}
		exit(0);
}

static void sig_usr1(int signo)
{
		ssize_t n;

		Mq_notify(mqd, &sigev); /* reregister first */
		n = Mq_receive(mqd, buff, attr.mq_msgsize, NULL);
		printf("SIGUSR1 received, read %ld bytes\nm", (long) n);
		return;
}
