/*
** server.h for  in /home/kizili_g//exo/my_irc
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Mon Apr 18 15:02:04 2011 guillaume kizilian
** Last update Thu Apr 21 17:26:00 2011 guillaume kizilian
*/

#ifndef			_SERVER_H_
# define		_SERVER_H_

# define		TITLE_SIZE 255
# define		NAME_SIZE 55
# define		MAX_CHANNEL 5
# define		DEFAULT_MAX_USERS 10
# define		DEFAULT_CHAN_BUFF_SIZE 4096

#include		<sys/types.h>
#include		<sys/socket.h>

typedef struct		s_user
{
  char			name[NAME_SIZE + 1];
  int			id;
  int			cs;
  struct s_user		*n;
}			t_user;

typedef struct		s_chan
{
  char			title[TITLE_SIZE + 1];
  int			u_max;
  char			buff[DEFAULT_CHAN_BUFF_SIZE];
  int			buff_size;
  t_user		*users;
}			t_chan;

typedef struct		s_serv
{
  char			title[TITLE_SIZE + 1];
  t_chan		chan[MAX_CHANNEL];
  int			s;
  struct sockaddr_in	*sin;
  int			port;
  struct sockaddr_in	*csin;
  int			csize;
}			t_serv;

#endif
