NAME = cub3D

SRC =	cub3d.c \
		utils/ft_wrmalloc.c \
		parsing/checkelements.c \
		parsing/cub.c \
		parsing/ft_strtrim.c \
		parsing/get_next_line.c \
		parsing/islinevalid.c \
		parsing/libftstuff.c \
		parsing/structstuff.c \
		parsing/whatsthemap.c

OBJ = ${SRC:.c=.o}

CC  = gcc

RM  = rm -f

CFLAGS = -I. -O3 #-g3 -fsanitize=address #-Wall -Wextra -Werror

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) ${CFLAGS} -L. -lmlx $^ -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all