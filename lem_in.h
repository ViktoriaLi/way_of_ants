/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 18:21:51 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"


typedef	struct	s_params
{
  int player_number;
  int oppos_number;
  int x_board;
  int y_board;
  int x_figure;
  int y_figure;
  char **board;
  char **figure;
  int x_diff;
  int y_diff;
}				t_params;

t_params params;

typedef	struct	s_room
{
	void			*name;
  int x;
  int y;
  int distance;
  int which_room;
  struct s_link *links;
  struct s_room *next;
}				t_room;

typedef struct	s_link
{
	struct s_room *link;
  struct s_link *next;
}				t_link;

char  *ft_strchr(const char *s, int c);

int		get_next_line(const int fd, char **line);
int		ft_printf(const char *format, ...);
void  ft_strdel(char **as);

int   ft_strcmp(const char *s1, const char *s2);
t_list  *ft_lstnew(void const *content, size_t content_size);
char  *ft_strrchr(const char *s, int c);

char	*ft_strstr(const char *big, const char *little);
char		**ft_strsplit(char const *s, char c);
int			ft_atoi(const char *str);
char	**two_dim_arr_mem(char **field, int x, int y, char c);
size_t		ft_strlen(const char *s);

char	*ft_strsub(char const *s, unsigned int start, size_t len);

#endif
