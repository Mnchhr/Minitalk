# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 14:09:11 by mkuehl            #+#    #+#              #
#    Updated: 2021/10/16 13:24:11 by mkuehl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER =		server

CLIENT =		client

CC =			gcc

CFLAGS =		-Wall -Wextra -Werror

HEADER =		minitalk.h

HEADERB =		minitalk_bonus.h

SRCSERVER =		server.c

SRCCLIENT =		client.c

SRCSERVERB =	server_bonus.c

SRCCLIENTB =	client_bonus.c

OBJSERVER =		$(SRCSERVER:.c=.o)

OBJCLIENT =		$(SRCCLIENT:.c=.o)

OBJSERVERB =	$(SRCSERVERB:.c=.o)

OBJCLIENTB =	$(SRCCLIENTB:.c=.o)

all:		$(SERVER) $(CLIENT)

%.o:		%.c
			$(CC) -c $(CFLAGS) $? -o $@

$(SERVER):	$(OBJSERVER) $(HEADER)
			$(CC) $(CFLAGS) $< -o $@

$(CLIENT):	$(OBJCLIENT) $(HEADER)
			$(CC) $(CFLAGS) $< -o $@

bonus:		fclean $(OBJSERVERB) $(OBJCLIENTB) $(HEADERB)
			$(CC) $(CFLAGS) $(OBJSERVERB) -o $(SERVER)
			$(CC) $(CFLAGS) $(OBJCLIENTB) -o $(CLIENT)

clean:
			rm -f $(OBJSERVER) $(OBJCLIENT)
			rm -f $(OBJSERVERB) $(OBJCLIENTB)

fclean:		clean
			rm -f $(SERVER) $(CLIENT)

re: 		fclean all

.PHONY:		re clean fclean all bonus