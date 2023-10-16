/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:34:19 by jordan            #+#    #+#             */
/*   Updated: 2023/10/16 19:40:25 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int	g_status = 0;

static int	process_input(int ac, char *input, char ***envp)
{
	t_cmds	cmds;
	char	*formatted_input;

	if (input == NULL)
		ft_exit(1);
	if (only_space(input))
		return (1);
	formatted_input = format_input(input);
	if (formatted_input && formatted_input[0] != '\0')
	{
		if (parse(&cmds, formatted_input, envp))
			return (1);
		if (ft_strcmp("exit", cmds.cmd[0].name))
			ft_exit_cmd(&cmds.cmd[0]);
		if (ac > 1)
			print_cmds(cmds);
		if (cmds.cmd[0].name)
			exec_line(&cmds, envp);
		else
			printf("unknown error");
		free_cmds(&cmds);
	}
	free(formatted_input);
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
		add_history(input);
		g_status = 1;
		if (process_input(ac, input, &env))
			printf("Syntax error\n");
		input = NULL;
		free(prompt);
		g_status = 0;
	}
	return (0);
}
