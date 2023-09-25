/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:29:43 by arthur            #+#    #+#             */
/*   Updated: 2023/09/25 16:02:19 by jchapell         ###   ########.fr       */
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
		else if (new_path[0] != '/')
			new_path = add_str("/", new_path, 0);
		else if (chdir(add_str(pwd, new_path, 0)))
			if(chdir(new_path))
				printf("Path not found\n");
	}
	else 
		printf("ERROR\n");
}