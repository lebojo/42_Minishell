/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:03:59 by jchapell          #+#    #+#             */
/*   Updated: 2023/09/26 17:45:51 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	sigint_handler(int sig)
{
	char *prompt;

	(void)sig;
	printf("\nOMG CTRL+C\n");
	create_prompt(&prompt);
	printf("\n%s", prompt);
}