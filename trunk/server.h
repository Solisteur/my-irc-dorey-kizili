/*
** server.h for  in /home/kizili_g//exo/my_irc
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Mon Apr 18 15:02:04 2011 guillaume kizilian
** Last update Tue Apr 19 15:54:20 2011 guillaume kizilian
*/

#ifndef			_SERVER_H_
# define		_SERVER_H_

# define		TITLE_SIZE 255
# define		NAME_SIZE 55
# define		MAX_CHANNEL 5

typedef struct		s_user
{
  char			name[NAME_SIZE + 1];
  int			id;
  struct s_user		*n;
}			t_user;

typedef struct		s_chan
{
  char			title[TITLE_SIZE + 1];
  int			id;
  int			u_max;
  t_user		*users;
  struct s_chan		*n;
}

typedef struct		s_serv
{
  char			title[TITLE_SIZE + 1];
  int			c_max;
  t_chan		*chan;
  int			s;
  struct sockaddr_in	*sin;
  int			port;
}			t_serv;

#endif
