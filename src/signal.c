/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:03:59 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/21 03:04:52 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	sig_handler(int sign_num)
{
	if (sign_num == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0); 
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sign_num == SIGQUIT)
	{
		if (g_status == 1)
			ft_putstr_fd("Quit: 3\n", 1);
		else
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
