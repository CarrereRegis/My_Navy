##
## EPITECH PROJECT, 2023
## Navy
## File description:
## Main Makefile of the project
##

CC	:=	gcc -std=gnu11

CFLAGS	=	-W
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wundef
CFLAGS	+=	-Wshadow
CFLAGS	+=	-Wunreachable-code
CFLAGS	+=	-Wmissing-prototypes
CFLAGS	+=	-Wno-unknown-pragmas
CFLAGS	+=	-pedantic
CFLAGS	+=	-I./include/

T_CFLAGS	:= $(CFLAGS)
T_CFLAGS	+=	-lcriterion
T_CFLAGS	+=	--coverage

LIBS_FLAGS	=	-L./lib/ -lmy

BDIR	=	.build
T_BDIR	=	.buildTests

NAME	=	my_navy
T_NAME	=	unit_tests

SRC	=	./sources/my_navy.c
SRC	+=	./sources/connection_handler.c
SRC	+=	./sources/connection_io.c
SRC	+=	./sources/str_utils.c
SRC	+=	./sources/game_loop.c
SRC	+=	./sources/my_parser.c
SRC	+=	./sources/render.c
SRC	+=	./sources/destroyer.c
SRC	+=	./sources/player_io.c
SRC	+=	./sources/connection_handler_extra.c

T_SRC	:=	$(SRC)
T_SRC	+=	./tests/my_tests.c

SRC	+=	./main.c

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
T_OBJ	=	$(T_SRC:%.c=$(T_BDIR)/%.o)

all:	$(NAME)

$(NAME):	build_lib $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBS_FLAGS)

$(T_NAME):	fclean build_lib $(T_OBJ)
	$(CC) $(T_OBJ) $(T_CFLAGS) -o $(T_NAME) $(LIBS_FLAGS)

$(T_BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(T_CFLAGS)

$(BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

asan:	CFLAGS += -fsanitize=address,leak,undefined -g3
asan: re

tests_run:	$(T_NAME)
	@ -./$(T_NAME) --verbose --full-stats --color=always -j8

build_lib:
	@ make -C ./lib/my

clean:
	@ rm -f $(T_OBJ)
	@ rm -f $(OBJ)
	@ rm -rf $(T_BDIR)
	@ rm -rf $(BDIR)

fclean:	clean
	@ rm -f $(NAME)
	@ rm -f $(T_NAME)
	@ make -C ./lib/my fclean

re:	fclean all

.PHONY : all tests_run build_lib clean fclean re
