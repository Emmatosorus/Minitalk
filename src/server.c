/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:29:00 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/19 16:21:40 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sigaction_s;

void	error_exit(void)
{
	ft_printf("\x1b[1;31mERROR\nft_calloc has failed\x1b[0m");
	exit(EXIT_FAILURE);
}

int	get_size(int sig)
{
	static int		len = 0;

	len <<= 1;
	if (sig == SIGUSR1)
		len |= 1;
	else
		len |= 0;
	return (len);
}

void	get_char(int sig, char **str)
{
	static char		result = 0;
	static int		i = 0;
	static int		pos = 0;

	if (i < 8)
	{
		result <<= 1;
		if (sig == SIGUSR1)
			result |= 1;
		else
			result |= 0;
		i++;
	}
	if (i == 8)
	{
		*str[pos] = result;
		result = 0;
		i = 0;
		pos++;
	}
}

void	get_message(int sig, siginfo_t *info, void *context)
{
	int			pid;
	static char	*str = NULL;
	static int	s = -1;
	static int	len = 0;

	pid = info->si_pid;
	g_sigaction_s = 1;
	if (++s < 64)
		len = get_size(sig);
	else
	{
		if (!str)
			str = ft_calloc(len * sizeof(char));
		if (!str)
			error_exit();
		get_char(sig, &str);
		if (str[len - 2] != 0)
		{
			write(1, &str, len);
			free(str);
		}
	}
	kill(pid, SIGUSR1);
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
		if (g_sigaction_s != 2)
			g_sigaction_s = 2;
		while (g_sigaction_s == 2)
			continue ;
	}
	return (0);
}
