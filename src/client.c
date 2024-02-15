/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:24:35 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/15 10:31:40 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	send_char(int pid, int c)
{
	int	i;

	i = (sizeof(char) * 8) - 1;
	(void)pid;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i--;
	}
}

int	main(int ac, char **av)
{
	size_t				len;
	int					pid;
	struct sigaction	act;

	if (ac < 3)
	{
		ft_printf(2, "\x1b[1;31mERROR\n");
		ft_printf(2, "Client must be called as: ./client <PID> <msg>\x1b[0m");
		exit(EXIT_FAILURE);
	}
	get_pid(&pid, av[1]);
	act.sa_handler = &send_char;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	len = ft_strlen(av[2]);
	while (len > 0)
	{
		len--;
		pause();
	}
}
