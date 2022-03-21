# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbrillai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 10:29:14 by qbrillai          #+#    #+#              #
#    Updated: 2022/03/21 16:26:52 by qbrillai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Compilation
NAME = ft_container
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98

#SOURCES

FILES	=	main.cpp \
			
			


OBJS	= ${FILES:.cpp=.o}

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
				rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
