/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:43 by arthur            #+#    #+#             */
/*   Updated: 2023/06/19 14:47:23 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

void	ft_cd(char *new_path)
{
	char	pwd[4096];

	if (!new_path || ft_strcmp(new_path, "~"))
		chdir(getenv("HOME"));
	else if (getcwd(pwd, 4096))
	{
		if (new_path[0] == '~')
		{
			new_path++;
			new_path = add_str(getenv("HOME"), new_path, 0);
		}
		if (new_path[0] != '/')
			new_path = add_str("/", new_path, 0);
		if (chdir(add_str(pwd, new_path, 0)))
			if(chdir(new_path))
				printf("Path not found\n");
		return ;
	}
	else 
		printf("ERROR\n");
}