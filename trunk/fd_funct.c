/*
** fd_funct.c for  in /home/kizili_g//exo/my-irc-dorey-kizili
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Thu Apr 21 15:21:04 2011 guillaume kizilian
** Last update Thu Apr 21 19:06:03 2011 guillaume kizilian
*/

#include	<sys/socket.h>
#include	<sys/select.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	"server.h"
#include	"common.h"
#include	"fd_funct.h"
#include	"libx.h"

void		fds_set(t_serv *serv, fd_set *rfds, fd_set *wfds)
{
  int		n;
  t_user	*tmp;

  FD_ZERO(rfds);
  FD_ZERO(wfds);
  FD_SET(serv->s, rfds);
  for (n = 0; n < MAX_CHANNEL; n++)
    {
      tmp = serv->chan[n].users;
      while (tmp != NULL)
	{
	  FD_SET(tmp->cs, rfds);
	  FD_SET(tmp->cs, wfds);
	  tmp = tmp->n;
	}
    }
}

void			check_new_text(t_serv *serv, fd_set *rfds)
{
  int		n;
  int		len;
  char		buff[512];
  t_user	*tmp;

  for (n = 0; n < MAX_CHANNEL; n++)
    {
      tmp = serv->chan[n].users;
      while (tmp != NULL)
	{
	  if (FD_ISSET(tmp->cs, rfds))
	    {
	      len = read(tmp->cs, buff, 511);
	      if (len == -1)
		handle_error("read");
	      buff[len] = '\0';
	      strcat(serv->chan[n].buff, tmp->name);
	      strcat(serv->chan[n].buff, " : ");
	      strcat(serv->chan[n].buff, buff);
	    }
	    tmp = tmp->n;
	}
    }
}

void			check_send_text(t_serv *serv, fd_set *wfds)
{
  int		n;
  t_user	*tmp;

  for (n = 0; n < MAX_CHANNEL; n++)
    {
      tmp = serv->chan[n].users;
      while (tmp != NULL)
	{
	  if (FD_ISSET(tmp->cs, wfds) && serv->chan[n].buff[0] != '\0')
	    xwrite(tmp->cs, serv->chan[n].buff, strlen(serv->chan[n].buff));
	  tmp = tmp->n;
	}
      serv->chan[n].buff[0] = '\0';
    }
}

int			set_login(t_serv *serv, t_user *user, char *name, int mess)
{
  int		n;
  t_user	*tmp;

  for (n = 0; n < MAX_CHANNEL; n++)
    {
      tmp = serv->chan[n].users;
      while (tmp != NULL)
	{
	  if (strcmp(name, tmp->name) == 0)
	    {
	      if (mess)
		xwrite(user->cs, "this login is already used\n", 28);
	      return (-1);
	    }
	  tmp = tmp->n;
	}
      serv->chan[n].buff[0] = '\0';
    }
  strcpy(user->name, name);
  xwrite(user->cs, "you're logged as ", 17);
  xwrite(user->cs, user->name, strlen(user->name));
  xwrite(user->cs, "\n", 1);
  return (0);
}

void			init_client(t_serv *serv, t_user *new, int id)
{
  int			nb;
  char			tmp[NAME_SIZE + 1];

  nb = rand() % 424242;
  snprintf(tmp, NAME_SIZE, "guest_%d", nb);
  while (set_login(serv, new, tmp, 0) == -1)
    {
      printf("b\n");
      nb = rand() % 424242;
      snprintf(tmp, NAME_SIZE, "guest_%d", nb);
    }
  new->n = NULL;
  new->id = id;
}
