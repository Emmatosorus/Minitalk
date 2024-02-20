/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:51:07 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/20 16:23:30 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sigaction_c;

void	msg_received(int sig)
{
	(void)sig;
	g_sigaction_c = 1;
}

void	send_char(int pid, int c)
{
	static int	i = (sizeof(char) * 8) - 1;

	if (i > 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
	}
	else
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

void	send_sig(int pid, char *str, int len)
{
	static int	s = -1;
	//static int	pos = 0;

	if (++s < 32)
		send_size_t(len, pid);
	else {
		ft_printf(1, "sent all\n");
		kill(pid, SIGUSR1);
		exit(EXIT_SUCCESS);}
		// if (pos < len)
		// 	send_char(pid, str[pos++]);
	(void)str;
}

int	main(int ac, char **av)
{
	ssize_t				len;
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
	len = ft_strlen(av[2]);
	count = len + 64;
	while (--count >= 0)
	{
		send_sig(pid, av[2], len);
		if (g_sigaction_c != 2)
			g_sigaction_c = 2;
		while (g_sigaction_c == 2)
			continue ;
	}
}
