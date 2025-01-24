# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	cub3D

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		:=	includes

LIBFTDIR	:=	libft

MLXDIR		:= 	MLX42

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			:=	

MLX_FLAG	:=	.mlx_flag

HEADER		:=	$(INCLUDES)/

MAKE		:=	Makefile

OBJS		:=	$(SRC:%.c=%.o)

LIBS		:=	$(LIBFTDIR)/libft.a $(MLXDIR)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so \
				-lm -ldl -Ofast -pthread -lglfw

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	-cc

CFLAGS		:=	-Werror -Wextra -Wall -Ofast -g#-lglfw

INCLUDE		:=	-Iincludes

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft libmlx $(NAME)

libmlx:
	@cmake -DDEBUG=1 $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS) Makefile includes/fdf.h
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBS) -o $(NAME)

make_libft:
	make -C libft

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft
	rm -fr MLX42/build

re: fclean all

.PHONY:  all clean fclean re bonus make_libft libmlx