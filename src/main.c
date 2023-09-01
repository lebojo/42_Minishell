/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/01 17:52:41 by abourgue         ###   ########.fr       */
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
	printf("======DEBUG======\n");
	while (i < cmds.nb_cmd)
	{
		printf("cmd[%d] = %s\n", i, cmds.cmd[i].name);
		printf("arg[%d] = %s\n", i, cmds.cmd[i].arg);
		if (cmds.nb_cmd > 1)
			printf("sep[%d] = %d\n", i, cmds.sep[i]);
		i++;
	}
	printf("=======END=======\n");
}

void sigint_handler(int sig)
{
	char *prompt;

	(void)sig;
	create_prompt(&prompt);
	printf("\n%s", prompt);
}

int main(int ac, char **av, char **envp) 
{
	char	*input;
	char	*prompt;
	t_cmds	cmds;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler); //Pour que le CTRL+C ne quitte pas le programme
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

