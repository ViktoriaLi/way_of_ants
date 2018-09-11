/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 13:31:58 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/09/11 13:32:01 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

intmax_t	long_main_atoi(const char *str, int i, int sign)
{
	intmax_t	tmp;
	intmax_t	res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res * 10 + sign * (str[i] - '0');
		if (tmp / 10 != res && sign == -1)
			return (0);
		if (tmp / 10 != res && sign == 1)
			return (-1);
		res = tmp;
		i++;
	}
	return (res);
}

intmax_t	ft_long_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (long_main_atoi(str, i, sign));
}
