/*
** fd_funct.h for  in /home/kizili_g//exo/my-irc-dorey-kizili
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Thu Apr 21 15:20:59 2011 guillaume kizilian
** Last update Thu Apr 21 18:14:56 2011 guillaume kizilian
*/


#ifndef			_FD_FUNCT_H_
# define		_FD_FUNCT_H_

void			fds_set(t_serv *serv, fd_set *rfds, fd_set *wfds);
void			check_new_text(t_serv *serv, fd_set *rfds);
void			check_send_text(t_serv *serv, fd_set *wfds);
void			init_client(t_serv *serv, t_user *new, int id);

#endif
