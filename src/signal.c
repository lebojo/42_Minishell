/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:03:59 by jchapell          #+#    #+#             */
/*   Updated: 2023/10/16 19:09:03 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	prompt(void)
{
	char	*prompt;

	create_prompt(&prompt);
	ft_putstr_fd(prompt, 1);
	free(prompt);
}

void	sig_handler(int sign_num)
{
	if (sign_num == SIGINT)
	{
		rl_save_prompt();
		rl_replace_line("", 0);
		rl_restore_prompt();
		rl_redisplay();
	}
	else if (sign_num == SIGQUIT)
	{
		if (g_status == 1)
			ft_putstr_fd("Quit: 3\n", 1);
		else
			ft_putstr_fd("\n", 1);
		prompt();
	}
}
