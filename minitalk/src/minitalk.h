/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:51:48 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/22 19:07:55 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include "../libft/libft.h"

/*-------- Client --------*/
void	get_pid(int *pid, char *nb);
void	input_error(void);

/*-------- Server --------*/
void	error_exit(int pid);

#endif