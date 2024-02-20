/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@42student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:06:47 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/15 17:13:19 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int g_sigaction //client
int g_sigaction[2] --> 0 | PID //serveur

// g_sigaction = 2
// Kill
while (g_sigaction[1] == 2)
{
	continue;
}
// stack

/* Le client envoie un bit
 * Le client attend d'avoir recus un bit en checkant  g_sigaction == 2
 * Le client recois le signal de reception
 * Le client reset la global a 2;
 * Le client envoie le prochain bit
 *
 * Le serveur attend d'avoir recus un bit en checkant g_sigaction_serve == 2
 * Le serveur recois le signal
 * Le serveut place le pid dans l'indexe 1 de la global
 * Le serveur place le bit dans l'indexe 0 de la global
 * Le serveur place l'indexe 0 de la global dans le char
 * Le serveur reset l'indexe 0 de la global a 2
 * Le serveur reset l'indexe 1 de la global a 0
 * Le serveur envoie un signal de reception au client
 *
 * /