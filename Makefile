# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	cub3D

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		:=	incs

LIBFTDIR	:=	libs/libft
PRINTFDIR	:= 	libs/libft/ft_printf/

MLXDIR		:= 	libs/mlx42
MLX42LIB	:=	$(MLXDIR)/build/libmlx42.a

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC 		:= 	main/main.c			\
				main/cub3d.c		\
				init/init.c			\
				parse/parse.c		\
				raycast/raycast.c

SRCDIR		= src
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR		= .obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIRS		= $(OBJDIR)/main		\
			$(OBJDIR)/parser		\
			$(OBJDIR)/utils

DEPDIR		= .dep
DEPS		= $(addprefix $(DEPDIR)/, $(SRC:.c=.d))
DEPDIRS		= $(DEPDIR)/main		\
			$(DEPDIR)/parser		\
			$(DEPDIR)/utils

HEADER		:=	incs/cub3d.h		\
				incs/init.h			\
				incs/parse.h		\
				incs/raycast.h		

MAKE		:=	Makefile

LIBS		:=	$(LIBFTDIR)/libft.a $(MLXDIR)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so \
				-lm -ldl -Ofast -pthread -lglfw

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	-cc

CFLAGS		:=	-Werror -Wextra -Wall -Ofast -g#-lglfw

DFLAGS		:= 	-MMD -MP 

INCLUDE		:=	-I./$(INCS) -I./$(LIBFTDIR)/includes -I./$(MLXDIR)/include

RM			:=	/bin/rm -fr

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: libft mlx $(NAME)

libft:
	make -C $(LIBFTDIR)

mlx:
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "MLX42 library not found, cloning from GitHub..."; \
		git clone https://github.com/42-Fundacion-Telefonica/MLX42.git $(MLXDIR); \
	fi
	@if [ ! -d "$(MLXDIR)/build/" ]; then \
		cmake -DDEBUG=1 $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4; \
	fi

# -=-=-=-=-    RULES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@mkdir -p $(DEPDIR)/$(dir $<)
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDE) -c $< -o $@ -MF $(DEPDIR)/$(<:.c=.d) -MT $@

$(NAME): $(OBJS) $(SRCS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBS) -o $(NAME)

bonus: all

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(PRINTFDIR)
	@$(RM) $(OBJDIR) $(DEPDIR) 
	@echo "$(RED)Cleaned object files and dependencies$(DEF_COLOR)"

fclean: clean
	@$(RM) minishell $(PRINTFDIR)libftprintf.a $(LIBFTDIR)libft.a
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"
	@$(RM) MLX42/build

re: fclean all

-include $(DEPS)

.PHONY:  all clean fclean re bonus libft mlx