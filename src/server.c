/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:29:00 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/15 10:38:45 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void get_size (int sig)
{
	static char		result = 0;
	static int		i = 0;

	if (i < 8)
	{
		result <<= 1;
		if (sig == SIGUSR1)
			result |= 1;
		else
			result |= 0;
		i++;
	}
	//ft_printf(1, "%d. %d\n", i, result);
	if (i == 8)
	{
		//ft_printf(1, "%c\n", result);
		write(1, &result, 1);
		i = 0;
		result = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	act;

	pid = getpid();
	ft_printf(1, "PID : %d\n", pid);
	act.sa_handler = &get_size;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
		kill();
	}
	return (0);
}
