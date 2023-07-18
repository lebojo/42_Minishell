/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/18 03:50:11 by jchapell         ###   ########.fr       */
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
		cmds.cmd = malloc(sizeof(t_cmd) * 3);
		cmds.cmd[0].name = ft_strjoin("","cat");
		cmds.cmd[0].arg = ft_strjoin("","test.txt");
		cmds.cmd[1].name = ft_strjoin("","cat");
		cmds.cmd[1].arg = ft_strjoin("","-e");
		cmds.cmd[2].name = ft_strjoin("","cat");
		cmds.cmd[2].arg = ft_strjoin("","-e");
		cmds.nb_cmd = 3;
		cmds.nb_pipe = 2;
		cmds.sep = malloc(sizeof(enum e_sep) * 2);
		cmds.sep[0] = Pipe;
		cmds.sep[1] = Pipe;
	while (1) {
		create_prompt(&prompt);
		input = readline(prompt);
		if (input)
		{
			parse(&cmds, input);
			if (cmds.cmd[0].name)
				exec_line(&cmds, &envp);
			else
				printf("unknown error");
			free(input);
		}
	}
	return 0;
}
