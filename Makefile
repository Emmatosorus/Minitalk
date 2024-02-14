NAME_S = server

NAME_C = client

CC = cc

CFLAGS = -g3 -Wall -Wextra -Werror

HDR = src/minitalk.h

LIB_HDR = libft/libft.h

LIB_AR = libft/libft.a

FTLINKER = -Llibft -lft

OBJ_DIR = .obj/

#--------Sources--------#

S_SRC = \
	src/server.c

S_OBJ = $(S_SRC:%.c=$(OBJ_DIR)%.o)

C_SRC = \
	src/client.c

C_OBJ = $(C_SRC:%.c=$(OBJ_DIR)%.o)
#---------Rules---------#

all : Makefile
	$(MAKE) $(NAME_S)
	# $(MAKE) $(NAME_C)

$(OBJ_DIR)%.o: %.c $(HDR)
	mkdir -p $(OBJ_DIR)src/
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_S) : $(S_OBJ) $(LIB_AR)
	$(CC) $(CFLAGS) -o $(NAME_S) $(S_OBJ) $(FTLINKER)

$(NAME_C) : $(C_OBJ) $(LIB_AR)
	$(CC) $(CFLAGS) -o $(NAME_C) $(C_OBJ) $(FTLINKER)

$(LIB_AR): force
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: clean fclean all re mlx force