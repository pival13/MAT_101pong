##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CC	 =	gcc

SRC	=	main.c 		\
		101pong.c

OBJ	=	$(SRC:.c=.o)

NAME	=	101pong

all: $(NAME)

$(NAME):
	make -C./lib/my
	$(CC) -g -o $(NAME) $(SRC) -lm -L./lib/my -lmy -I./include/

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C./lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
