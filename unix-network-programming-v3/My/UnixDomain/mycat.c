#include "../../lib/unp.h"
#include "myopen.c"

int main(int argc, char **argv)
{
		int fd, n;
		char buff[MAXLINE];

		if (argc != 2)
				err_quit("usage: mycat <pathname>");

		if ( (fd = my_open2(argv[1], O_RDONLY)) < 0 )
				err_sys("cannot open %s", argv[1]);

		while ( (n = Read(fd, buff, BUFFSIZE)) > 0 )
				Write(STDOUT_FILENO, buff, n);

		exit(0);

}
