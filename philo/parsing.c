/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:26:19 by cfiachet          #+#    #+#             */
/*   Updated: 2025/04/11 12:22:52 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	return_error(void)
{
	printf("error");
	exit(1);
}

static int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	parsing(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (check_num(av[i]))
			return_error();
		i++;
	}
}
