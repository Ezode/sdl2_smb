##
## Perso
## Makefile
## File description:
## Makefile for Mario Bros project
##

SRC		=	src/main.c					\
			src/map_functions.c			\
			src/render_functions.c		\

OBJ		=	$(SRC:.c=.o)

NAME	=	smb

CFLAGS 	= 	-I ./include -lSDL2 -lSDL2_image -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	all clean

.PHONY: all clean fclean re
