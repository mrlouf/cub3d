# Colors
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m
CYAN = \033[0;96m
GREEN = \033[0;92m
BLUE = \033[0;94m
RED = \033[0;91m

NAME = libft.a
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC = ft_itoa.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strjoin_free.c ft_strmapi.c \
      ft_strnstr.c ft_strrchr.c ft_substr.c ft_split.c ft_atoi.c \
      ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
      ft_isspace.c ft_isvalidsign.c ft_memcmp.c ft_tolower.c ft_toupper.c \
      ft_strncmp.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_bzero.c \
      ft_calloc.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c \
      ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
      ft_striteri.c ft_strtrim.c ft_free.c get_next_line.c ft_array_count.c \
      ft_append_c.c cucufu.c ft_print_array.c ft_strtok.c                 \
      ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c \
      ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
      ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstcpy_bonus.c \
      ft_strrchr_n.c ft_strspn.c ft_strcspn.c ft_strchr_n.c ft_isdigit_str.c ft_strjoin3.c \
      ft_lstsub_bonus.c ft_strndup.c ft_min_len.c ft_count_words.c ft_lstsort.c ft_strcmp.c \
      ft_strdup_lower.c ft_strtoll.c ft_free_narray.c ft_exit_error.c ft_array_flip.c ft_get_current_time.c \
      ft_strcpy_pad.c

OBJ = $(SRC:.c=.o)

%.o: %.c libft.h Makefile
	@$(CC) $(FLAGS) -I. -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

