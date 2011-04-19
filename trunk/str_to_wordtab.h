/*
** str_to_wordtab.h for  in /home/kizili_g//exo/my_ftp/new_ftp
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Sun Apr  3 12:11:48 2011 guillaume kizilian
** Last update Sun Apr  3 12:27:30 2011 guillaume kizilian
*/

#ifndef		_STR_TO_WORDTAB_H_
# define	_STR_TO_WORDTAB_H_

char		**str_to_wordtab(const char *s);
int		my_wordlen(const char *s);
int		count_word(const char *s);
void		free_wordtab(char **s);

#endif
