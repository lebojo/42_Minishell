/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:34:19 by jordan            #+#    #+#             */
/*   Updated: 2023/10/06 04:03:09 by jordan           ###   ########.fr       */
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
			ft_exit_free(envp, &cmds);
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
