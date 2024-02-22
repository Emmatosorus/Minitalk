/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:51:07 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/22 12:05:44 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sigaction_c;

void	msg_received(int sig)
{
	(void)sig;
	if (sig == SIGUSR2)
	{
		ft_printf(1, "\x1b[1;31mServer has failed\n\x1b[0m");
		exit(EXIT_FAILURE);
	}
	g_sigaction_c = 1;
}

void	send_char(int pid, int c)
{
	static int	i = (sizeof(char) * 8) - 1;

	if (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
	}
	if (i < 0)
		i = (sizeof(char) * 8) - 1;
}

void	send_size_t(int len, int pid)
{
	static int	i = (sizeof(size_t) * 8) - 1;
	
	if ((len >> i) & 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	i--;
}

void	send_sig(int pid, char *str, size_t len)
{
	static size_t	pos = 0;
	static int		i = 0;
	static int		size = 0;

	g_sigaction_c = 2;
	(void)str;
	if (++size <= 64)
		send_size_t(len, pid);
	else
	{
		i++;
		if (pos < len)
			send_char(pid, str[pos]);
		if (i >= 8)
		{
			pos++;
			i = 0;
		}
	}
}

int	main(int ac, char **av)
{
	size_t				len;
	ssize_t				count;
	int					pid;
	struct sigaction	act;

	if (ac < 3)
		input_error();
	get_pid(&pid, av[1]);
	act.sa_handler = &msg_received;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	len = ft_strlen(av[2]);
	count = (len * 8) + 64;
	while (--count >= 0)
	{
		send_sig(pid, av[2], len);
		while (g_sigaction_c == 2)
			continue ;
	}
}
