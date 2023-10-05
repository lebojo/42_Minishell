/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:34:19 by jordan            #+#    #+#             */
/*   Updated: 2023/10/05 03:21:52 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int	g_status = 0;

static int	process_input(int ac, char **input, char ***envp)
{
	t_cmds	cmds;

	if (*input == NULL)
		ft_exit();
	if (*input && *input[0] != '\0')
	{
		parse(&cmds, *input, envp);
		if (ft_strcmp("exit", cmds.cmd[0].name))
			ft_exit();
		if (ac > 1)
			print_cmds(cmds);
		if (cmds.cmd[0].name)
			exec_line(&cmds, envp);
		else
			printf("unknown error");
		add_history(*input);
		free(*input);
		free_cmds(&cmds);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	*prompt;
	char	**env;

	(void)av;
	env = copy_tab(envp);
	start(&env);
	// printf("%s -- %s\n", env[0], env[61]);
	// printf("%s -- %s\n", envp[0], envp[61]);
	while (1)
	{
		create_prompt(&prompt);
		input = readline(prompt);
		g_status = 1;
		if (process_input(ac, &input, &env))
		{
			printf("CRITICAL ERROR\n");
			return (1);
		}
		free(prompt);
		g_status = 0;
	}
	return (0);
}
