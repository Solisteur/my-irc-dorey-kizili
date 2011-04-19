/*
** libx.c for  in /home/kizili_g//exo/my_ftp
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Thu Mar 31 14:09:27 2011 guillaume kizilian
** Last update Sun Apr  3 19:50:01 2011 guillaume kizilian
*/

#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"libx.h"

int		xopen(const char *pathname, int flags)
{
  int		fd;

  if (pathname && strlen(pathname) > 0)
    fd = open(pathname, flags);
  else
    return (-1);
  if (fd == -1)
    HANDLE_ERROR("open");
  return (fd);
}

ssize_t		xread(int fd, void *buf, size_t count)
{
  int		nb;

  if (buf)
    nb = read(fd, buf, count);
  else
    return (0);
  if (nb == -1)
    HANDLE_ERROR("read");
  return (nb);
}

int		xclose(int fd)
{
  fd = close(fd);
  if (fd == -1)
    HANDLE_ERROR("close");
  return (0);
}

ssize_t		xwrite(int fd, const void *buf, size_t count)
{
  ssize_t	nb;

  nb = write(fd, buf, count);
  if (nb == -1)
    HANDLE_ERROR("write");
  return (nb);
}
