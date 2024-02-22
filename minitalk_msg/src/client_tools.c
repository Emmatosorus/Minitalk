/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:16:53 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/22 13:36:03 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	input_error(void)
{
	ft_printf(2, "\x1b[1;31mERROR\n");
	ft_printf(2, "Client must be called as: ./client <PID> <msg>\x1b[0m");
	exit(EXIT_FAILURE);
}

void	get_pid(int *pid, char *nb)
{
	int	i;

	i = -1;
	while (nb[++i] != '\0')
	{
		if (ft_isdigit(nb[i]) != 1)
		{
			ft_printf(2, "\x1b[1;31mERROR\nPID must be a number\x1b[0m");
			exit(EXIT_FAILURE);
		}
	}
	*pid = ft_atoi(nb);
	if (kill(*pid, 0) == -1)
	{
		ft_printf(2, "\x1b[1;31mERROR\nNo process of ID: %d\x1b[0m", *pid);
		exit(EXIT_FAILURE);
	}
}