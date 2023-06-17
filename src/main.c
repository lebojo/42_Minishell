/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/17 03:46:18 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

int main(int ac, char **av, char **envp) 
{
	char	*input;
	t_cmds	cmds;

	(void)ac;
	(void)av;
	while (1) {
		input = readline("💻> : ");
		parse(&cmds, input);
		exec_line(&cmds, envp);
		free(input);
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