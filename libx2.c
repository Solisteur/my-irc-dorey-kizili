/*
** libx2.c for  in /home/kizili_g//exo/my_ftp/my_ftp
** 
** Made by guillaume kizilian
** Login   <kizili_g@epitech.net>
** 
** Started on  Sun Apr  3 19:49:39 2011 guillaume kizilian
** Last update Thu Apr 21 17:11:29 2011 guillaume kizilian
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"common.h"

void		*xmalloc(size_t size)
{
  void		*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    handle_error("malloc");
  return (ptr);
}

void		*xrealloc(void *ptr, size_t size)
{
  ptr = realloc(ptr, size);
  if (ptr == NULL)
    handle_error("realloc");
  return (ptr);
}
