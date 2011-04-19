##
## Makefile for  in /home/kizili_g//exo/nm-objdump
## 
## Made by guillaume kizilian
## Login   <kizili_g@epitech.net>
## 
## Started on  Sun Mar 13 19:23:53 2011 guillaume kizilian
## Last update Mon Apr 18 15:04:19 2011 guillaume kizilian
##

NAME_SERV	= serveur
NAME_CLT	= client

SRCS_SERV	=	serveur.c

SRCS_CLT	=	client.c

SRCS_COM	=	common.c	\
			libx.c		\
			libx2.c		\
			str_to_wordtab.c

CC		= gcc
CFLAGS		= -W -Wall -Werror
OBJS_SERV	= $(SRCS_SERV:.c=.o)
OBJS_CLT	= $(SRCS_CLT:.c=.o)
OBJS_COM	= $(SRCS_COM:.c=.o)

all		: serveur client

serveur		: $(OBJS_SERV) $(OBJS_COM)
		$(CC) $(CFLAGS) $(OBJS_SERV) $(OBJS_COM) -o $(NAME_SERV)

client		: $(OBJS_CLT) $(OBJS_COM)
		$(CC) $(CFLAGS) $(OBJS_CLT) $(OBJS_COM) -o $(NAME_CLT)

$(OBJS_SERV)	:
		$(CC) $(CFLAGS) -c $(SRCS_SERV)

$(OBJS_CLT)	:
		$(CC) $(CFLAGS) -c $(SRCS_CLT)

$(OBJS_COM)	:
		$(CC) $(CFLAGS) -c $(SRCS_COM)

clean	:
	rm -f $(OBJS_SERV) $(OBJS_CLT) $(OBJS_COM)

fclean	: clean
	rm -f $(NAME_SERV) $(NAME_CLT)

re	: fclean all