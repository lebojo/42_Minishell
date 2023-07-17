/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/07/18 01:52:32 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_prompt(char **prompt)
{
	*prompt = add_str("💻 \e[0;32m➜ \e[0;36m", actual_folder(), 2);
	*prompt = add_str(*prompt, "\e[0;32m > \e[0m", 1);
}

int main(int ac, char **av, char **envp) 
{
	char	*input;
	char	*prompt;
	t_cmds	cmds;

	(void)ac;
	(void)av;
	while (1) {
		create_prompt(&prompt);
		input = readline(prompt);
		if (input)
		{
			parse(&cmds, input);
			if (cmds.cmd[0].name)
				select_cmd(&cmds.cmd[0], &envp);
			else
				printf("unknown error");
			free(input);
		}
	}
	return 0;
}
