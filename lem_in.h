#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"

#define START_ROOM 0
#define END_ROOM 1
#define OTHER_ROOM 2

typedef	struct	s_params
{
  int ants;
  int links_count;
  int rooms_count;
  int if_error;
  int end_entries;
  char *buf;
  char *start;
  char *end;
}				t_params;

typedef struct  s_room
{
  void      *name;
  int x;
  int y;
  int which_room;
  int usage;
  struct s_room *enter;
  struct s_room *next;
  struct  s_room_list *links;
}       t_room;

typedef	struct	s_room_list
{
  struct  s_room *room;
  struct  s_room_list *next;
}				t_room_list;

typedef struct	s_link
{
  char *first;
  char *second;
  struct s_link *next;
}				t_link;

typedef struct	s_way
{
  char *name;
  int distance;
  int if_empty;
  struct s_way *next;
}				t_way;

typedef struct	s_ways
{
  int number;
  int ant;
  struct s_way *way;
  struct s_ways *next;
}				t_ways;

char  *ft_strchr(const char *s, int c);

int		get_next_line(const int fd, char **line);
int		ft_printf(const char *format, ...);
void  ft_strdel(char **as);

int   ft_strcmp(const char *s1, const char *s2);
char  *ft_strrchr(const char *s, int c);

char	*ft_strstr(const char *big, const char *little);
char		**ft_strsplit(char const *s, char c);
int			ft_atoi(const char *str);
char	**two_dim_arr_mem(char **field, int x, int y, char c);
size_t		ft_strlen(const char *s);

char	*ft_strsub(char const *s, unsigned int start, size_t len);


int	save_link(t_link **head, t_params *params, t_room *rooms);
int	save_room(t_room **head, t_params *params, int which_room);
int if_room(t_params *params, t_room **rooms, int which_room);
int ants_saving(t_params *params);
int pre_comments_parsing(t_params *params);
int comments_parsing(t_params *params, int *ifstart, int *ifend, t_room **rooms);
int make_rooms_with_links(t_room *rooms, t_link *links, t_params *params);
void add_links(t_room_list **farm, t_link *links, t_params *params);
int search_way(t_room_list *farm, t_params *params);
void del_rooms_and_links(t_room *rooms, t_link *links);

#endif
