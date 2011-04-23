/*
** server.c for  in /home/kizili_g//exo/my_irc
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Mon Apr 18 15:03:13 2011 guillaume kizilian
** Last update Thu Apr 21 18:29:34 2011 guillaume kizilian
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netdb.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<time.h>
#include	<stdio.h>
#include	<string.h>
#include	"common.h"
#include	"server.h"
#include	"fd_funct.h"
#include	"libx.h"

int			check_new_users(t_serv *serv, fd_set *rdfs, int nb_client)
{
  t_user		*tmp;

  if (!FD_ISSET(serv->s, rdfs))
    return (nb_client);
  if (serv->chan[0].users == NULL)
    {
      serv->chan[0].users = xmalloc(sizeof(*tmp));
      tmp = serv->chan[0].users;
    }
  else
    {
      tmp = serv->chan[0].users;
      for (tmp = tmp; tmp->n != NULL; tmp = tmp->n);
      tmp->n = xmalloc(sizeof(*tmp));
      tmp = tmp->n;
    }
  tmp->cs = accept(serv->s, (struct sockaddr *)serv->csin, (socklen_t *)&serv->csize);
  if (tmp->cs == -1)
    {
      xclose(serv->s);
      handle_error("accept");
    }
  printf("new\n");
  init_client(serv, tmp, nb_client);
  return (nb_client + 1);
}

int                     get_clients(t_serv *serv)
{
  static int		nb_client = 4;
  int			error;
  fd_set		rfds;
  fd_set		wfds;

  while (42)
    {
      fds_set(serv, &rfds, &wfds);
      if ((error = select(nb_client, &rfds, &wfds, NULL, NULL)) != -1)
	{
	  check_send_text(serv, &wfds);
	  nb_client = check_new_users(serv, &rfds, nb_client);
	  check_new_text(serv, &rfds);
	}
    }
  return (0);
}

void			init_serv(t_serv *serv, struct protoent *pe)
{
  int			error;

  serv->s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  srandom(time(0) * getuid());
  if (serv->s == -1)
    handle_error("socket");
  serv->sin->sin_family = AF_INET;
  serv->sin->sin_port = htons(serv->port);
  serv->sin->sin_addr.s_addr = INADDR_ANY;
  error = bind(serv->s, (const struct sockaddr *)serv->sin, sizeof(*serv->sin));
  if (error == -1)
    {
      xclose(serv->s);
      handle_error("bind");
    }
  error = listen(serv->s, 10);
  if (error == -1)
    {
      xclose(serv->s);
      handle_error("listen");
    }
}

void			init_struct(t_serv *serv)
{
  int			n;

  strncpy(serv->title, "GreenRC", TITLE_SIZE);
  serv->title[TITLE_SIZE] = '\0';
  for(n = 0; n < MAX_CHANNEL; n++)
    {
      serv->chan[n].title[0] = '\0';
      serv->chan[n].u_max = DEFAULT_MAX_USERS;
      serv->chan[n].users = NULL;
      serv->chan[n].buff[0] ='\0';
      serv->chan[n].buff_size = DEFAULT_CHAN_BUFF_SIZE;
    }
  strncpy(serv->chan[0].title, "Home", TITLE_SIZE);
  serv->chan[0].title[TITLE_SIZE] = '\0';
  serv->csize = sizeof(struct sockaddr_in);
}

int			main(int ac, char **av)
{
  t_serv		serv;
  struct sockaddr_in	sin;
  struct sockaddr_in	csin;

  if (ac != 2)
    {
      write(2, "Usage : ./serveur port\n", 24);
      exit(EXIT_FAILURE);
    }
  serv.sin = &sin;
  serv.csin = &csin;
  serv.port = atoi(av[1]);
  init_serv(&serv, getprotobyname("TCP"));
  init_struct(&serv);
  get_clients(&serv);
  xclose(serv.s);
  return (EXIT_SUCCESS);
}
