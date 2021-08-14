NAME       :=	minitalk
SRC1       :=	client.c	ft_utils.c
SRC2       :=	server.c	ft_utils.c
OBJ1       :=	$(SRC1:.c=.o)
OBJ2       :=	$(SRC2:.c=.o)
HDR        :=	minitalk.h
CC         :=	gcc
CFLAGS     :=	-Wall -Wextra -Werror -MMD

all:		$(NAME)

$(NAME):	client server

client:		$(OBJ1) $(HDR)
			$(CC) $(CFLAGS) -o $@ $(OBJ1)

server:		$(OBJ2) $(HDR)
			$(CC) $(CFLAGS) -o $@ $(OBJ2)

bonus:		$(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -c $<

#include	$(wildcard *.d)

clean:
			rm -rf *.o *.d

fclean:		clean
			rm -rf client server

re:			fclean all

.PHONY:		all clean fclean re bonus
