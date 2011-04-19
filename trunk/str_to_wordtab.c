/*
** str_to_wordtab.c for  in /home/kizili_g//exo/my_ftp/new_ftp
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Sun Apr  3 12:12:29 2011 guillaume kizilian
** Last update Sun Apr  3 17:07:23 2011 guillaume kizilian
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	"str_to_wordtab.h"
#include	"libx.h"

int		my_wordlen(const char *s)
{
  int           n = 0;

  while (s[n] != '\0')
    {
      if (s[n] != ' ' && s[n] != '\t')
        n++;
      else
        return (n);
    }
  return (n);
}

int		count_word(const char *s)
{
  int		nb_word = 0;
  int		n = 0;

  while (s[n] != '\0')
    {
      if ((n == 0 || s[n - 1] == ' ' || s[n - 1] == '\t') &&    \
          s[n] != ' ' && s[n] != '\t')
        nb_word++;
      n++;
    }
  return (nb_word);
}

char		**str_to_wordtab(const char *s)
{
  int           n = 0;
  int           i = 0;
  int           nb_word = count_word(s);
  int           wd_len = 0;
  char          **tab;

  tab = xmalloc(sizeof(*tab) * (nb_word + 1));
  while (n < nb_word)
    {
      while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
        i++;
      wd_len = my_wordlen(&s[i]);
      tab[n] = xmalloc(sizeof(**tab) * (wd_len + 1));
      strncpy(tab[n], &s[i], wd_len);
      tab[n][wd_len] = '\0';
      while (s[i] != '\0' && (s[i] != ' ' && s[i] != '\t'))
        i++;
      n++;
    }
  tab[nb_word] = NULL;
  return (tab);
}

void		free_wordtab(char **s)
{
  int		n;

  for (n = 0; s[n] != NULL; n++)
    free(s[n]);
  free(s);
}
