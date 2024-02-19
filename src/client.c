/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:24:35 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/19 18:21:43 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sigaction_c;

void	msg_received(int sig)
{
	g_sigaction_c = 1;
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

send int 

int	main(int ac, char **av)
{
	size_t				len;
	int					pid;
	struct sigaction	act;

	if (ac < 3)
		input_error();
	get_pid(&pid, av[1]);
	act.sa_handler = &msg_received;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	len = ft_strlen(av[2]);
	while (--len >= 0)
	{
		if (g_sigaction_c != 2)
			g_sigaction_c = 2;
		while (g_sigaction_c == 2)
			continue ;
		send_char(pid, av[2][len]);
	}
}
