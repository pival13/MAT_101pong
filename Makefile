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
	make -C./lib/my && make clean -C./lib/my
	$(CC) -g -o $(NAME) $(SRC) -lm -L./lib/my -lmy -I./include/
	$(CC) -o game bonus/moved_picture.c -lcsfml-graphics -Llib/my -lmy -Iinclude

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C./lib/my
	rm -f $(NAME) game

re:	fclean all

.PHONY: all clean fclean
