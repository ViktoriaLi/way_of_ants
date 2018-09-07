/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comments_ants_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:40:32 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 16:41:38 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		comments_parsing(t_params *params, int *ifstart, int *ifend,
t_room **rooms)
{
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "start"))
	{
		if (ft_strlen((*params).buf) == 7 &&
			main_rooms_saving(ifstart, params, rooms, START_ROOM))
			return (1);
		return (0);
	}
	if ((*params).buf[1] == '#' && ft_strstr(&params->buf[2], "end"))
	{
		if (ft_strlen((*params).buf) == 5 &&
			main_rooms_saving(ifend, params, rooms, END_ROOM))
			return (1);
		return (0);
	}
	else
	{
		ft_printf("%s\n", (*params).buf);
		ft_strdel(&params->buf);
		return (1);
	}
}

int		pre_comments_parsing(t_params *params)
{
	if ((*params).buf[1] == '#' && (ft_strstr(&params->buf[2], "start")
	|| ft_strstr(&params->buf[2], "end")))
	{
		ft_strdel(&params->buf);
		return (0);
	}
	ft_printf("%s\n", (*params).buf);
	ft_strdel(&params->buf);
	return (1);
}

int		ants_saving(t_params *params)
{
	int i;

	i = 0;
	if ((*params).buf[0] < '1' || (*params).buf[0] > '9')
	{
		ft_strdel(&params->buf);
		return (0);
	}
	while ((*params).buf[i] >= '0' && (*params).buf[i] <= '9')
		i++;
	if ((*params).buf[i] || i > 10)
	{
		ft_strdel(&params->buf);
		return (0);
	}
	(*params).ants = ft_uns_atoi((*params).buf);
	if ((*params).ants > 2147483647 || (*params).ants <= 0)
	{
		ft_strdel(&params->buf);
		return (0);
	}
	ft_printf("%s\n", (*params).buf);
	ft_strdel(&params->buf);
	return (1);
}
