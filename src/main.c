/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/25 17:06:36 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int main(int ac, char **av, char **envp) 
{
	char	*input;
	char	*prompt;
	t_cmds	cmds;
	t_cmd	c;

	(void)ac;
	(void)av;
	start(ac, av, &envp);
	c.arg = add_str("SHLVL=", ft_itoa(ft_atoi(find_path(envp, "SHLVL", 5)) + 1), 0);
	ft_export(&c, &envp);
	while (1) {
		create_prompt(&prompt);
		input = readline(prompt);
		if (input == NULL) // C'est pour le CTRL+D
			ft_exit();
		if (input && input[0] != '\0')
		{
			parse(&cmds, input);
			if (ft_strcmp("exit", cmds.cmd[0].name)) //Il n'y a pas moyen de faire autrement
				ft_exit();
			if (ac > 1)
				print_cmds(cmds);
			if (cmds.cmd[0].name)
				exec_line(&cmds, &envp);
			else
				printf("unknown error");
			add_history(input);
			free(input);
			free_cmds(&cmds);
		}
		free(prompt);
	}
	return 0;
}

