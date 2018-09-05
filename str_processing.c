/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:14:40 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 16:28:07 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		proc_incorrect_str(t_params *params)
{
	if (ft_strcmp((*params).buf, "\n") == 0 ||
	(*params).buf[0] == 'L')
	{
		ft_strdel(&params->buf);
		if ((*params).links_count && (*params).rooms_count)
		{
			(*params).if_error = 1;
			return (1);
		}
		return (0);
	}
	return (2);
}

int		proc_comment_str(t_params *params, t_reading *read_params)
{
	if (comments_parsing(params, &read_params->ifstart,
		&read_params->ifend, &read_params->rooms))
	{
		ft_strdel(&params->buf);
		return (1);
	}
	else
		return (0);
}

int		proc_room_str(t_params *params, t_room **rooms)
{
	if (if_room(params, rooms, OTHER_ROOM))
	{
		(*params).rooms_count++;
		ft_strdel(&params->buf);
		if (!(*params).links_count)
			return (1);
		else
		{
			(*params).if_error = 1;
			return (0);
		}
	}
	else
		return (0);
}

int		proc_links_str(t_params *params, t_reading *read_params)
{
	ft_strdel(&params->buf);
	if (!(*params).rooms_count || !(*read_params).ifstart ||
	!(*read_params).ifend)
	{
		del_rooms_and_links((*read_params).rooms, (*read_params).links);
		return (0);
	}
	(*params).links_count++;
	return (1);
}

int		proc_else_str(t_params *params, t_reading read_params)
{
	if ((*params).links_count && (*params).rooms_count)
	{
		(*params).if_error = 1;
		return (1);
	}
	del_rooms_and_links(read_params.rooms, read_params.links);
	return (0);
}
