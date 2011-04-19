/*
** libx.h for  in /home/kizili_g//exo/my_ftp
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Thu Mar 31 14:08:48 2011 guillaume kizilian
** Last update Sun Apr  3 10:29:07 2011 guillaume kizilian
*/

#ifndef		_LIBX_H_
# define	_LIBX_H_

# define HANDLE_ERROR(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)

# include	<sys/types.h>

int		xclose(int fd);
void		*xmalloc(size_t size);
ssize_t		xread(int fd, void *buf, size_t count);
int		xopen(const char *pathname, int flags);
ssize_t		xwrite(int fd, const void *buf, size_t count);
void		*xrealloc(void *ptr, size_t size);

#endif
