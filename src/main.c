/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/24 19:49:19 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_prompt(char **prompt)
{
	char	*af;

	af = actual_folder();
	if (ft_strcmp(af, "Jordan"))
		*prompt = add_str("❤️ \e[0;32m➜ \e[0;36m", af, 2);
	else
		*prompt = add_str("💻 \e[0;32m➜ \e[0;36m", af, 2);
	*prompt = add_str(*prompt, "\e[0;32m > \e[0m", 1);
}

void	print_cmds(t_cmds cmds)
{
	int i = 0;
	int j = 0;
	printf("\033[1;33m======DEBUG======\033[0m\n");
	printf("nb_cmd: %i, nb_pipe: %i\n", cmds.nb_cmd, cmds.nb_pipe);
	while (i < cmds.nb_cmd)
	{
		printf("cmd[%d] name = %s, arg = %s, pipe = %i\n", i, cmds.cmd[i].name, cmds.cmd[i].arg, cmds.cmd[i].which_pipe);
		if (cmds.nb_cmd > 1)
			printf("sep[%d] = %d\n", i, cmds.sep[i]);
		i++;
	}
	printf("\033[1;33m=======END=======\033[0m\n");
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
	t_cmd	c;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler); //Pour que le CTRL+C ne quitte pas le programme
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

