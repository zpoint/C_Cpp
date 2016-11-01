#include "apue.h"

ssize_t readn(int fd, void *ptr, size_t n)  // Read "n" bytes from a descriptor
{
		size_t nleft;
		ssize_t nread;

		nleft = n;
		while (nleft > 0)
		{
				if ((nread = read(fd, ptr, nleft)) < 0)
				{
						if (nleft == n)
								return(-1); // error ,return -1
						else
								break; // error, return amount read so far
				}
				else if (nread == 0)
				{
						break; // EOF
				}
				nleft -= nread;
				ptr += nread;
		}
		return (n - nleft); // return >= 0
}

ssize_t writen(int fd, const void *ptr, size_t n)  // write "n" bytes to a descripter
{
		size_t nleft;
		ssize_t nwritten;

		nleft = n;
		while (nleft > 0)
		{
				if ((nwritten = write(fd, ptr, nleft)) < 0)
				{
						if (nleft == n)
								return(-1); // error, return -1
						else 
								break; // error, return amount written so far
				}
				else if (nwritten == 0)
				{
						break;
				}
				nleft -= nwritten;
				ptr += nwritten;
		}
		return(n - nleft); // return >= 0
}

