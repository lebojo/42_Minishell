/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/02 01:23:01 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int	process_input(int ac, char *input, char ***envp)
{
	t_cmds	cmds;

	if (input == NULL) // C'est pour le CTRL+D
			ft_exit();
	if (input && input[0] != '\0')
	{
		parse(&cmds, input, envp);
		if (ft_strcmp("exit", cmds.cmd[0].name)) //Il n'y a pas moyen de faire autrement
			ft_exit();
		if (ac > 1)
			print_cmds(cmds);
		if (cmds.cmd[0].name)
			exec_line(&cmds, envp);
		else
			printf("unknown error");
		add_history(input);
		free(input);
		free_cmds(&cmds);
	}
	return (0);
}

int main(int ac, char **av, char **envp) 
{
	char	*input;
	char	*prompt;
	char	**env;

	(void)av;
	start(ac, av, &envp);
	env = copy_tab(envp);
	while (1) {
		create_prompt(&prompt);
		input = readline(prompt);
		if (process_input(ac, input, &env))
		{
			printf("CRITICAL ERROR\n");
			return (1);
		}
		free(prompt);
	}
	return (0);
}

