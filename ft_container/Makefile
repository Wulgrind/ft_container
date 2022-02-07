#Compilation
NAME = ft_container
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

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
