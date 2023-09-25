/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:03:59 by jchapell          #+#    #+#             */
/*   Updated: 2023/09/25 17:04:25 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	sigint_handler(int sig)
{
	char *prompt;

	(void)sig;
	create_prompt(&prompt);
	printf("\n%s", prompt);
}