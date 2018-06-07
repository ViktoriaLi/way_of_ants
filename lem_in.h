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

#define START_ROOM 1
#define END_ROOM 2
#define OTHER_ROOM 0

typedef	struct	s_params
{
  int ants;
  int step;
  char *buf;
  char *start;
  char *end;
}				t_params;

typedef struct  s_room
{
  void      *name;
  int x;
  int y;
  int distance;
  int which_room;
  int usage;
  struct s_room *enter;
  struct  s_room_list *links;
}       t_room;

typedef	struct	s_room_list
{
  struct  s_room *room;
  struct  s_room_list *next;
}				t_room_list;

typedef struct	s_link
{
	//struct s_room *link;
  char *first;
  char *second;
  struct s_link *next;
}				t_link;

typedef struct	s_ways
{
  char *name;
  struct s_ways *way;
  struct s_ways *next;
}				t_ways;

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
