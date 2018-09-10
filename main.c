/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:56:07 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/07/19 16:28:55 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_params params;

	struct_nulling(&params);
	while (get_next_line(0, &params.buf) > 0 && params.buf[0] == '#')
	{
		if (!pre_comments_parsing(&params))
		{
			ft_printf("%s\n", "ERROR");
			exit(0);
		}
	}
	if (params.buf)
	{
		if (!ants_saving(&params))
		{
			ft_printf("%s\n", "ERROR");
			exit(0);
		}
		if (!lemin_reading(&params))
		{
			ft_strdel(&params.buf);
			ft_printf("%s\n", "ERROR");
			exit(0);
		}
	}
}
