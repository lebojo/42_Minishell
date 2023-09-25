/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:43 by arthur            #+#    #+#             */
/*   Updated: 2023/09/25 16:57:05 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	update_pwds(char *pwd, char *new_path, char ***envp)
{
	t_cmd	old_pwd;
	t_cmd	new_pwd;

	old_pwd = create_cmd("", add_str("OLDPWD=", pwd, 0), 0);
	getcwd(pwd, 4096);
	new_pwd = create_cmd("", add_str("PWD=", pwd, 0), 0);
	ft_export(&old_pwd, envp);
	ft_export(&new_pwd, envp);
	printf("\n===PWD_UPDATE===\n%s\n%s\n", old_pwd.arg, new_pwd.arg);
}

void	ft_cd(char *new_path, char ***envp)
{
	char	pwd[4096];	

	if (!new_path || ft_strcmp(new_path, "~"))
		chdir(hm_get_value(*envp, "HOME"));
	else if (getcwd(pwd, 4096))
	{
		if (ft_strcmp(new_path, "-"))
		{
			chdir(hm_get_value(*envp, "OLDPWD"));
			update_pwds(pwd, new_path, envp);
			return ;
		}
		if (new_path[0] == '~')
		{
			new_path++;
			new_path = add_str(hm_get_value(*envp, "HOME"), new_path, 0);
		}
		if (new_path[0] != '/')
			new_path = add_str("/", new_path, 0);
		if (chdir(add_str(pwd, new_path, 0)))
			if(chdir(new_path))
				printf("Path not found\n");
		update_pwds(pwd, new_path, envp);
	}
	else 
		printf("Unknown error\n");
}