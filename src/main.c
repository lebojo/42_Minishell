/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/17 02:03:38 by jordan           ###   ########.fr       */
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
				select_cmd(&cmds.cmd[0], envp);
			free(input);
		}
	}
	return 0;
}
/*MAIN POUR TESTER LE PARSING:
int main(int ac, char **av, char **envp) 
{
	char 	*tmp;
	int		i;
	t_cmds cmds;

	(void)ac;
	(void)av;
	(void)envp;
	tmp = ft_strdup("echo -n Je mange du sexe | cmd2 je sexe ta mère");
	parse(&cmds, tmp);
	i = 0;
	printf("[INPUT] %s\n", tmp);
	while (i++ < cmds.nb_cmd)
		printf("[CMD N°%i] Name: %s; Arg: %s\n", i, cmds.cmd[i - 1].name, cmds.cmd[i - 1].arg);
	printf("[GENERAL] Nb pipe:%i, Nb cmd: %i\n", cmds.nb_pipe, cmds.nb_cmd);
	return 0;
}
*/