/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:51:19 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/21 10:49:44 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sigaction_s;

void	error_exit(void)
{
	ft_printf(1, "\x1b[1;31mERROR\nft_calloc has failed\x1b[0m");
	exit(EXIT_FAILURE);
}

// void	get_size(int sig, int *len)
// {
// 	*len <<= 1;
// 	if (sig == SIGUSR1)
// 		*len |= 1;
// 	else
// 		*len |= 0;
// }

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
	static int	c = 0;
	static int	s = 0;
	//static int	len = 0;

	pid = info->si_pid;
	g_sigaction_s = 1;
	(void)context;
	if (s <= 8)
	{
		c <<= 1;
		if (sig == SIGUSR1)
		{
			c |= 1;
			//write(1, "1", 1);
		}
		else
		{
			c |= 0;
			//write(1, "0", 1);
		}
		s++;
	}
	if (s == 8)
	{
		write(1, &c, 1);
		c = 0;
		s = 0;
		//len = 0;
	}
	//write(1, &c, 1);
		// if (!str)
		// 	str = ft_calloc(len, sizeof(char));
		// if (!str)
		// 	error_exit();
		// get_char(sig, &str);
		// if (str[len - 2] != 0)
		// {
		// 	write(1, &str, len);
		// 	free(str);
		// }
	kill(pid, SIGUSR1);
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
