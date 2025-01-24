/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:45:35 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/01/09 18:28:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif
# ifndef FD
#  define FD 1
# endif
# ifndef ULL_MAX
#  define ULL_MAX ULLONG_MAX
# endif
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <aio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <errno.h>
# include "ft_printf/includes/ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char *s1, const char *s2);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
long long	ft_strtoll(const char *str, char **endptr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_isvalidsign(char a, char b);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstcpy(t_list *original);

int			ft_printf(char const *str, ...);
ssize_t		ft_write_str(char *str);
ssize_t		ft_write_int(int n);
ssize_t		ft_write_char(char c);
ssize_t		ft_write_int_base(int num, int bsize, char *base, ssize_t *digits);
ssize_t		ft_write_hex_low(unsigned int n);
ssize_t		ft_write_hex_upp(unsigned int n);
ssize_t		ft_write_ptr(void *ptr);
ssize_t		ft_wub(unsigned long long c, unsigned long long s, char *b, \
	ssize_t *d);
ssize_t		ft_write_dec(int n);
ssize_t		ft_write_uns(unsigned int n);

void		ft_free(char **str);
char		*get_next_line(int fd);
char		*ft_free_gnl(char **str);
int			ft_array_count(char **ptr);
char		*ft_append_c(char *start, char c);
void		ft_print_array(char **array);
void		cucufu(int index);
char		*ft_strtok(char *str, const char *delim);
char		*ft_strrchr_n(const char *s, int c, int n);
char		*ft_strchr_n(const char *s, int c, int n);
size_t		ft_strcspn(const char *s, const char *reject);
size_t		ft_strspn(const char *s, const char *accept);
int			ft_isdigit_str(char *str);
t_list		*ft_lstsub(t_list *lst, int start, int count);
char		*ft_strndup(const char *s, size_t n);
size_t		ft_min_strlen(const char *s1, const char *s2);
int			ft_count_words(const char *str);
t_list		*ft_lstsort(t_list *l, int (*cmp)(const void *, const void *, \
	size_t));
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup_lower(const char *str);

#endif
