/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:14 by jordan            #+#    #+#             */
/*   Updated: 2023/06/12 20:49:58 by jordan           ###   ########.fr       */
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
	char	*input;  // Déclarer un pointeur de chaîne de caractères pour stocker l'entrée utilisateur$
	char	*tmp;
	t_envp  env;
	t_cmd	cmd;

	(void)ac;
	tmp = find_path(envp, "PATH", 4);
	env.pwd = find_path(envp, "PWD", 3);
	env.bin_path = ft_split(tmp, ':');
	while (1) {
		input = readline("?> : ");  // Afficher le prompt et lire l'entrée de l'utilisateur
		parse(&cmd, input);
		if (ft_strcmp(input, "q") == 1) {
			free(input);  // Libérer la mémoire allouée par readline()
			break;
		}
		parse(&cmd, input);
		cmd.name = get_cmd(env.bin_path, cmd.name);
		execve(cmd.name, av, envp);
		free(cmd.name);
		free(input);  // Libérer la mémoire allouée par readline()
	}
	return 0;
}
