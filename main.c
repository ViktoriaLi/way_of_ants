#include "lem_in.h"

void struct_nulling(t_params *params)
{
	(*params).buf = NULL;
	(*params).ants = 0;
	(*params).step = 0;
	(*params).links_count = 0;
	(*params).rooms_count = 0;
	(*params).start = NULL;
  (*params).end = NULL;
}

int lemin_reading(t_params *params)
{
	int ifstart;
	int ifend;
	t_room *rooms;
	t_link *links;

	ifstart = 0;
	ifend = 0;
	rooms = NULL;
	links = NULL;
	while (get_next_line(0, &params->buf) > 0)
	{
		if (ft_strcmp((*params).buf, "\n") == 0 || (*params).buf[0] == 'L')
		{
			ft_printf("%s\n", "non valid");
			return (0);
		}

		if (!ft_strchr((*params).buf, '-') && (*params).buf[0] != '#'
		&& if_room(params, &rooms, OTHER_ROOM))
		{
			ft_printf("%s\n", "room");
			(*params).rooms_count++;
			if (!(*params).links_count)
				continue ;
			else
			{
				ft_strdel(&params->buf);
				ft_printf("%s\n", "ERROR7");
				break ;
			}
		}
		else if ((*params).buf[0] == '#' &&
		comments_parsing(params, &ifstart, &ifend, &rooms))
		{
			ft_printf("%s\n", "comment");
			continue ;
		}

		else if (ft_strchr((*params).buf, '-') && save_link(&links, params))
		{
			ft_printf("%s\n", "link");
			(*params).links_count++;
			continue ;
		}
		else
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR8");
			return (0);
		}
	}
	make_rooms_with_links(rooms, links, params);
	/*while (links)
	{
		ft_printf("name%s %s\n", (links)->first,
			(links)->second);
		links = links->next;
	}*/
	/*while (rooms)
	{
		ft_printf("name%s x%d y%d dist%d\n", (rooms)->name,
			(rooms)->x, (rooms)->y, (rooms)->which_room);
		rooms = rooms->next;
	}*/
	return (1);
}


int main(void)
{
	t_params params;
	struct_nulling(&params);
	while (get_next_line(0, &params.buf) > 0 && params.buf[0] == '#')
	{
		if (!pre_comments_parsing(&params))
			return (0);
	}
	if (!ants_saving(&params))
		return (0);
	if (!lemin_reading(&params))
	{
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR9");
		return (0);
	}
}
