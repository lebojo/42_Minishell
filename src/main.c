/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/16 22:24:59 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

int main(int ac, char **av, char **envp) 
{
    char    *input;
    t_cmds    cmds;

    (void)ac;
    (void)av;
    while (1) {
        input = readline("💻> : ");
        parse(&cmds, input);
        if (ft_strcmp(input, "q") == 1) {
            free(input);
            break;
        }
        select_cmd(&cmds.cmd[0], envp);
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