
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:17:13 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 16:26:50 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_correct_str(t_reading *read_params, t_params *params)
{
	if (!ft_strchr((*params).buf, '-') && (*params).buf[0] != '#')
	{
		if (!proc_room_str(params, &read_params->rooms))
			return (2);
		return (1);
	}
	else if ((*params).buf[0] == '#')
	{
		if (!proc_comment_str(params, read_params))
			return (2);
		return (1);
	}
	else if (ft_strchr((*params).buf, '-') && (*params).buf[0] != '#'
		&& save_link(&read_params->links, params, read_params->rooms))
	{
		if (!proc_links_str(params, read_params))
			return (0);
		return (1);
	}
	return (-1);
}

int		stop_reading(t_params *params, t_reading *read_params)
{
	ft_strdel(&params->buf);
	if (!read_params->ifstart || !read_params->ifend ||
		!make_rooms_with_links(read_params->rooms,
			read_params->links, params))
	{
		del_rooms_and_links(read_params->rooms, read_params->links);
		return (0);
	}
	return (1);
}

int		lemin_reading(t_params *params)
{
	t_reading read_params;

	read_params_nulling(&read_params);
	while (get_next_line(0, &params->buf) > 0)
	{
		read_params.res = proc_incorrect_str(params);
		if (!read_params.res)
		{
			del_rooms_and_links(read_params.rooms, read_params.links);
			return (0);
		}
		if (read_params.res == 1)
			break ;
		read_params.res = check_correct_str(&read_params, params);
		if (read_params.res == -1 && proc_else_str(params))
			break ;
		if (read_params.res == -1 && !proc_else_str(params))
		{
			del_rooms_and_links(read_params.rooms, read_params.links);
			return (0);
		}
		if (read_params.res == 0)
			return (0);
		if (read_params.res == 1)
		{
			ft_strdel(&params->buf);
			continue ;
		}
		if (read_params.res == 2)
			break ;
	}
	if (!stop_reading(params, &read_params))
		return (0);
	//del_rooms_and_links(read_params.rooms, read_params.links);
	return (1);
}
