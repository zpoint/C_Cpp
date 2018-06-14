#include <time.h>
#include "../../lib/unp.h"

char* my_gf_time(void)
{
		struct timeval tv;
		static char str[30];
		char *ptr;

		if (gettimeofday(&tv, NULL) < 0)
				err_sys("gettimeofday error");

		ptr = ctime(&tv.tv_sec);
		strcpy(str, &ptr[11]);
		/* Fir Sep 13 00:00:00 1986\n\0 */
		/* 0123456789012345678901234 5 */
		snprintf(str + 8, sizeof(str) - 8, ".%06d", tv.tv_usec);
		return (str);
}

void str_cli_nonblock(FILE *fp, int sockfd)
{
		int maxfdp1, val, stdineof;
		ssize_t n, nwritten;
		fd_set rset, wset;
		char to[MAXLINE], fr[MAXLINE];
		char *toiptr, *tooptr, *friptr, *froptr;

		val = Fcntl(sockfd, F_GETFL, 0);
		Fcntl(sockfd, F_SETFL, val | O_NONBLOCK);

		val = Fcntl(STDIN_FILENO, F_GETFL, 0);
		Fcntl(STDIN_FILENO, F_SETFL, val | O_NONBLOCK);

		val = Fcntl(STDOUT_FILENO, F_GETFL, 0);
		Fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);

		toiptr = tooptr = to; /* initialize buffer pointers */
		friptr = froptr = fr;
		stdineof = 0;

		maxfdp1 = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;

		for ( ; ; )
		{
				FD_ZERO(&rset);
				FD_ZERO(&wset);
				if (stdineof == 0 && toiptr < &to[MAXLINE])
						FD_SET(STDIN_FILENO, &rset); /* read from stdin */
				if (friptr < &fr[MAXLINE])
						FD_SET(sockfd, &rset); /* read from socket */
				if (tooptr != toiptr)
						FD_SET(sockfd, &wset); /* data to write to socket */
				if (froptr != friptr)
						FD_SET(STDOUT_FILENO, &wset); /* data to write to stdout */

				Select(maxfdp1, &rset, &wset, NULL, NULL);

				if (FD_ISSET(STDIN_FILENO, &rset))
				{
						if ( (n = read(STDIN_FILENO, toiptr, &to[MAXLINE] - toiptr)) < 0 )
						{
								if (errno != EWOULDBLOCK)
										err_sys("read error on stdin");
						}
						else if (n == 0)
						{
								fprintf(stderr, "%s: EOF on stdin\n", my_gf_time());
								stdineof = 1; /* all done with stdin */
								if (tooptr == toiptr)
										Shutdown(sockfd, SHUT_WR); /* send FIN */
						}
						else
						{
								fprintf(stderr, "%s: read %ld bytes from stdin\n", my_gf_time(), n);
								toiptr += n; /* # just read */
								FD_SET(sockfd, &wset); /* try and write to socket below */
						}
				}

				if (FD_ISSET(sockfd, &rset))
				{
						if ( (n = read(sockfd, friptr, &fr[MAXLINE] - friptr)) < 0 )
						{
								if (errno != EWOULDBLOCK)
										err_sys("read error on socket");
						}
						else if (n == 0)
						{
								fprintf(stderr, "%s: EOF on socket\n", my_gf_time());
								if (stdineof)
										return; /* normal termination */
								else
										err_quit("str_cli: server termionated prematurely");
						}
						else
						{
								fprintf(stderr, "%s: read %ld bytes from socket\n", my_gf_time(), n);
								friptr += n; /* # just read */
								FD_SET(STDOUT_FILENO, &wset); /* try and write below */
						}
				}

				if (FD_ISSET(STDOUT_FILENO, &wset) && (n = friptr - froptr) > 0)
				{
						if ( (nwritten = write(STDOUT_FILENO, froptr, n)) < 0 )
						{
								if (errno != EWOULDBLOCK)
										err_sys("write error to stdout");
						}
						else
						{
								fprintf(stderr, "%s wrote %ld bytes to stdout\n", my_gf_time(), nwritten);
								froptr += nwritten; /* just written */
								if (froptr == friptr)
										froptr = friptr = fr; /* back to beginning of buffer */
						}
				}

				if (FD_ISSET(sockfd, &wset) && (n = toiptr - tooptr) > 0)
				{
						if ( (nwritten = write(sockfd, tooptr, n)) < 0 )
						{
								if (errno == EWOULDBLOCK)
										err_sys("write error to socket");
						}
						else
						{
								fprintf(stderr, "%s: wrote %ld bytes to socket\n", my_gf_time(), nwritten);
								tooptr += nwritten; /* just written */
								if (tooptr == toiptr)
								{
										toiptr = tooptr = to; /* back to beginning of buffer */
										if (stdineof)
												Shutdown(sockfd, SHUT_WR); /* send FIN */
								}
						}
				}
		}
}
