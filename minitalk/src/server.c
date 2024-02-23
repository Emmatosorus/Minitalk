/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:51:19 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/23 10:58:18 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sigaction_s;

void	get_size(int sig, int pid, size_t *len)
{
	*len <<= 1;
	if (sig == SIGUSR1)
		*len |= 1;
	else
		*len |= 0;
	if (kill(pid, SIGUSR1) == -1)
		*len = 0;
}

int	make_char(int sig, int pid)
{
	static char	c = 0;
	static int	s = 0;
	char		buf;

	buf = -1;
	if (s <= 8)
	{
		c <<= 1;
		if (sig == SIGUSR1)
			c |= 1;
		else
			c |= 0;
		s++;
	}
	if (s == 8)
		buf = c;
	if (kill(pid, SIGUSR1) == -1 || s == 8)
	{
		c = 0;
		s = 0;
	}
	return (buf);
}

void	get_char(int sig, int pid, int len, int *state)
{
	static char		*str = NULL;
	static int		counter[2] = {0, 0};
	char			c;

	if (!str)
	{
		str = ft_calloc((len + 1), sizeof(char));
		if (!str)
			error_exit(pid);
	}
	c = make_char(sig, pid);
	if (++counter[0] >= 8)
	{
		counter[0] = 0;
		str[counter[1]++] = c;
	}
	if (c == 0)
	{
		*state = 0;
		counter[1] = 0;
		ft_printf(1, "%s\n", str);
		if (str)
			free(str);
		str = NULL;
	}
}

void	get_message(int sig, siginfo_t *info, void *context)
{
	int				pid;
	static int		state = 0;
	static int		size = 0;
	static size_t	len = 0;

	(void)context;
	pid = info->si_pid;
	g_sigaction_s = 1;
	if (state == 0 && ++size <= 64)
	{
		get_size(sig, pid, &len);
		if (size == 64)
		{
			size = 0;
			state = 1;
		}
	}
	else
		get_char(sig, pid, len, &state);
	if (kill(pid, 0) == -1)
		size = 0;
}

int	main(void)
{
	int					pid;
	struct sigaction	act;

	pid = getpid();
	ft_printf(1, "PID : %d\n", pid);
	act.sa_sigaction = &get_message;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		if (g_sigaction_s != 2)
			g_sigaction_s = 2;
		while (g_sigaction_s == 2)
			continue ;
	}
	return (0);
}
