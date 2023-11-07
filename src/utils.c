/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:11:50 by lebojo            #+#    #+#             */
/*   Updated: 2023/11/07 13:33:43 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	print_cmds(t_cmds cmds)
{
	int	i;

	i = 0;
	printf("\033[1;33m======DEBUG======\033[0m\n");
	printf("nb_cmd: %i, nb_pipe: %i\n", cmds.nb_cmd, cmds.nb_pipe);
	while (i < cmds.nb_cmd)
	{
		printf("cmd[%d] name = %s, arg = %s, pipe = %i\n", i,
			cmds.cmd[i].name, cmds.cmd[i].arg, cmds.cmd[i].which_pipe);
		// if (cmds.nb_cmd >= 1)
		// 	printf("sep[%d] = %d\n", i, cmds.sep[i]);
		i++;
	}
	printf("\033[1;33m=======END=======\033[0m\n");
}

void	create_prompt(char **prompt, char **env)
{
	char	*af;
	char	*home;
	char	*lst;
	char	pwd[4096];
 
	af = actual_folder();
	home = hm_get_value(env, "HOME");
	lst = hm_get_value(env, "?");
	if (ft_strcmp(af, "Jordan") || ft_strcmp(af, "Arthur"))
		*prompt = add_str("<3 ➜ ", af, 2);
	else if (ft_strcmp(getcwd(pwd, 4096), home))
		*prompt = add_str("~ ➜ ", af, 2);
	else if (!ft_strcmp(lst, "0"))
		*prompt = add_str(":( ➜ ", af, 2);
	else
		*prompt = add_str(":) ➜ ", af, 2);
	*prompt = add_str(*prompt, " > ", 1);
	free(home);
	free(lst);
}

int	char_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str && *str && str[i])
	{
		if (str[i++] == c)
			return (1);
	}
	return (0);
}
