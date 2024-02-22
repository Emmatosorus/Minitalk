/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:03:15 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/22 19:06:35 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_exit(int pid)
{
	kill(pid, SIGUSR2);
	ft_printf(1, "\x1b[1;31mERROR\nft_calloc has failed\x1b[0m");
	exit(EXIT_FAILURE);
}
