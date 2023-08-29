/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/28 15:29:36 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_prompt(char **prompt)
{
	*prompt = add_str("💻 \e[0;32m➜ \e[0;36m", actual_folder(), 2);
	*prompt = add_str(*prompt, "\e[0;32m > \e[0m", 1);
}

void	print_cmds(t_cmds cmds)
{
	int i = 0;
	int j = 0;
	while (i < cmds.nb_cmd)
	{
		printf("cmd[%d] = %s\n", i, cmds.cmd[i].name);
		printf("arg[%d] = %s\n", i, cmds.cmd[i].arg);
		if (cmds.nb_cmd > 1)
			printf("sep[%d] = %d\n", i, cmds.sep[i]);
		i++;
	}	
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
		if (input && input[0] != '\0')
		{
			parse(&cmds, input);
			print_cmds(cmds);
			if (cmds.cmd[0].name)
				exec_line(&cmds, &envp);
			else
				printf("unknown error");
			add_history(input);
			free(input);
			free_cmds(&cmds);
		}
	}
	return 0;
}

