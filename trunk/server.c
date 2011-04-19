/*
** server.c for  in /home/kizili_g//exo/my_irc
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Mon Apr 18 15:03:13 2011 guillaume kizilian
** Last update Mon Apr 18 17:04:15 2011 guillaume kizilian
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netdb.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<stdio.h>
#include	"common.h"
#include	"server.h"

void			do_client(int cs1, int cs2)
{
  char			buff[512];
  int			len;

  len = read(cs1, buff, 511);
  if (len == -1)
    {
      write(2, "error on read\n", 14);
      exit(EXIT_FAILURE);
    }
  write(cs2, buff, len);
}

int                     get_clients(int s)
{
  struct sockaddr_in    csin;
  static int		nb_client = 4;
  int                   csize;
  int                   cs1;
  int                   cs2;
  int			error;
  fd_set		readfds;

  csize = sizeof(csin);
  cs1 = accept(s, (struct sockaddr *)&csin, (socklen_t *)&csize);
  cs2 = accept(s, (struct sockaddr *)&csin, (socklen_t *)&csize);
  if (cs1 == -1 || cs2 == -1)
    {
      xclose(s);
      handle_error("listen");
    }
  printf("connected to clients\n");
  while (42)
    {
      FD_ZERO(&readfds);
      if ((error = select(nb_client, &readfds, NULL, NULL, NULL)) != -1)
	{
	  if (FD_ISSET(cs1, &readfds))
	    do_client(cs1, cs2);
	  if (FD_ISSET(cs2, &readfds))
	    do_client(cs2, cs1);
	}
    }
  return (0);
}

int			init_serv(int port, struct protoent *pe)
{
  struct sockaddr_in    sin;
  int			s;
  int			error;

  srand(time(0) * getuid());
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    handle_error("socket");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  error = bind(s, (const struct sockaddr *)&sin, sizeof(sin));
  if (error == -1)
    {
      xclose(s);
      handle_error("bind");
    }
  error = listen(s, 10);
  if (error == -1)
    {
      xclose(s);
      handle_error("listen");
    }
  return (s);
}

int			main(int ac, char **av)
{
  int			s;

  if (ac != 2)
    {
      write(2, "Usage : ./serveur port\n", 24);
      exit(EXIT_FAILURE);
    }
  s = init_serv(atoi(av[1]), getprotobyname("TCP"));
  get_clients(s);
  xclose(s);
  return (0);
}
