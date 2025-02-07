# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	cub3D

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		:=	incs

LIBFTDIR	:=	libs/libft
PRINTFDIR	:= 	libs/libft/ft_printf/

MLXDIR		:= 	libs/mlx42
MLX42LIB	:=	$(MLXDIR)/build/libmlx42.a

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC 		:= 	main/main.c					\
				main/cub3d.c				\
				init/init.c					\
				init/init_sprites.c			\
				parse/parse.c				\
				parse/parse_format.c		\
				parse/parse_populator.c 	\
				parse/parse_content.c		\
				parse/parse_map.c			\
				parse/parse_map_utils1.c	\
				parse/parse_map_utils2.c	\
				parse/transfer.c			\
				parse/transfer_utils.c		\
				rendering/raycast.c			\
				rendering/doorcast.c		\
				rendering/doors.c			\
				rendering/draw.c			\
				rendering/draw_utils1.c		\
				rendering/draw_utils2.c		\
				rendering/draw_player.c		\
				rendering/draw_behind.c		\
				rendering/draw_front.c		\
				rendering/draw_cow.c		\
				rendering/draw_horse.c		\
				rendering/draw_npcs.c		\
				rendering/textures_wall.c	\
				rendering/textures_player.c	\
				rendering/textures_cow.c	\
				rendering/textures_horse.c	\
				rendering/textures_npc_1.c	\
				hooks/hooks.c				\
				hooks/movements.c			\
				hooks/pet.c					\
				hooks/pet_utils.c			\
				utils/utils.c				\
				utils/sprite_utils.c		\
				utils/sort_sprites.c		\
				utils/cleanup1.c			\
				utils/cleanup2.c			\
				utils/cleanup3.c			\

SRCDIR		= src
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR		= .obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR		= .dep
DEPS		= $(addprefix $(DEPDIR)/, $(SRC:.c=.d))
DEPDIRS		= $(DEPDIR)/main		\
			$(DEPDIR)/parse			\
			$(DEPDIR)/utils			\
			$(DEPDIR)/rendering		\
			$(DEPDIR)/init			\
			$(DEPDIR)/hooks

HEADER		:=	incs/cub3d.h		\
				incs/init.h			\
				incs/parse.h		\
				incs/rendering.h	\
				incs/utils.h		\
				incs/hooks.h

MAKE		:=	Makefile

LIBS		:=	$(LIBFTDIR)/libft.a $(MLXDIR)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so \
				-lm -ldl -Ofast -pthread -lglfw

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	cc

CFLAGS		:=	-Werror -Wextra -Wall -Ofast -g -fsanitize=address #-lglfw

DFLAGS		:= 	-MT $@ -MMD -MP

INCLUDE		:=	-I/incs -I./$(LIBFTDIR)/includes -I./$(MLXDIR)/include

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
	$(CC) $(CFLAGS) $(INCLUDE) -MT $@ -MMD -MP -c $< -o $@
	@mkdir -p $(DEPDIR) $(DEPDIRS)
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJDIR),$(DEPDIR),$(@D))/

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBS) -o $(NAME)

bonus: all

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(PRINTFDIR)
	@$(RM) $(OBJDIR) $(DEPDIR) 
	@echo "$(RED)Cleaned object files and dependencies$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME) $(PRINTFDIR)libftprintf.a $(LIBFTDIR)libft.a
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"
	@$(RM) MLX42/build

re: fclean all

-include $(DEPS)

.PHONY:  all clean fclean re bonus libft mlx