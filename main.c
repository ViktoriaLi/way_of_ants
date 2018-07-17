/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:07 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/16 10:56:14 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void del_rooms_and_links(t_room *rooms, t_link *links)
{
	t_room *tmp_rooms;
	t_link *tmp_links;

	while (rooms)
	{
		tmp_rooms = rooms->next;
		free(rooms);
		rooms = tmp_rooms;
	}
	while (links)
	{
		tmp_links = links->next;
		free(links);
		links = tmp_links;
	}
}

void struct_nulling(t_params *params)
{
	(*params).buf = NULL;
	(*params).ants = 0;
	(*params).links_count = 0;
	(*params).rooms_count = 0;
	(*params).if_error = 0;
	(*params).end_entries = 0;
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
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR11");
			if ((*params).links_count && (*params).rooms_count)
			{
				(*params).if_error = 1;
				break;
			}
			del_rooms_and_links(rooms, links);
			exit (0);
		}
		if (!ft_strchr((*params).buf, '-') && (*params).buf[0] != '#'
		&& if_room(params, &rooms, OTHER_ROOM))
		{
			(*params).rooms_count++;
			ft_strdel(&params->buf);
			if (!(*params).links_count)
				continue ;
			else
			{
				ft_printf("%s\n", "ERROR7");
				(*params).if_error = 1;
				break ;
			}
		}
		else if ((*params).buf[0] == '#' &&
		comments_parsing(params, &ifstart, &ifend, &rooms))
		{
			ft_strdel(&params->buf);
			continue ;
		}
		else if (ft_strchr((*params).buf, '-') && (*params).buf[0] != '#'
			&& save_link(&links, params, rooms))
		{
			ft_strdel(&params->buf);
			if (!(*params).rooms_count || !ifstart || !ifend)
			{
				del_rooms_and_links(rooms, links);
				exit (0);
			}
			(*params).links_count++;
			continue ;
		}
		else
		{
			ft_strdel(&params->buf);
			ft_printf("%s\n", "ERROR8");
			if ((*params).links_count && (*params).rooms_count)
			{
				(*params).if_error = 1;
				break;
			}
			del_rooms_and_links(rooms, links);
			exit (0);
		}
	}
	if (!ifstart || !ifend || !(*params).links_count || !(*params).rooms_count)
	{
		del_rooms_and_links(rooms, links);
		exit (0);
	}
	if (!make_rooms_with_links(rooms, links, params))
	{
		del_rooms_and_links(rooms, links);
		exit (0);
	}
	return (1);
}


int main(void)
{
	t_params params;

	struct_nulling(&params);
	while (get_next_line(0, &params.buf) > 0 && params.buf[0] == '#')
	{
		if (!pre_comments_parsing(&params))
			exit (0);
	}
	if (!ants_saving(&params))
		exit (0);
	if (!lemin_reading(&params))
	{
		ft_strdel(&params.buf);
		ft_printf("%s\n", "ERROR9");
		exit (0);
	}
}
