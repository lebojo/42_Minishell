/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordan <jordan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:33:51 by arthur            #+#    #+#             */
/*   Updated: 2023/06/17 01:58:29 by jordan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/proto.h"

char	*actual_folder(void)
{
	char	pwd[4096];
	char	*res;
	int		i;
	int		size;

	if (getcwd(pwd, 4096))
	{
		i = 0;
		size = ft_strlen(pwd);
		size--;
		while (pwd[size] && pwd[size] != '/')
			size--;
		i = ft_strlen(pwd) - size - 1;
		res = ft_calloc(i + 1, sizeof(char));
		i--;
		size = ft_strlen(pwd) - 1;
		while (pwd[size] && pwd[size] != '/')
			res[i--] = pwd[size--];
		return(res);
	}
	printf("ERROR -> get actual folder");
}

void	ft_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, 4096))
	{
		printf("%s\n", pwd); 
		return ;
	}
	printf("ERROR\n");
}