/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:41:48 by jchauvet          #+#    #+#             */
/*   Updated: 2023/03/10 15:29:17 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/* INITIATE THE ENVIRON (stores everything that <<printenv>> shows you.) */

int	env_init(void)
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	if (i == 0)
		return (0);
	g_env = malloc((i + 1) * sizeof(char *));
	if (g_env == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = 0;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(&g_env);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		i++;
	}
	g_env[i] = NULL;
	return (0);
}

/* GET THE VALUE OF A SPECIFIC VARIABLE STORED IN ENV. */

char	*env_get_value(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	else
		return (NULL);
}

/* RETURNS A POINTER TO THE VARIABLE <<NAME>> STORED IN ENVIRON.*/

char	*env_find_var(char *name)
{
	int	l_name;
	int	i;

	if (name == NULL || g_env == NULL)
		return (NULL);
	if (ft_strchr(name, '='))
		l_name = ft_strchr(name, '=') - name;
	else
		l_name = ft_strlen(name);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(name, g_env[i], l_name) && g_env[i][l_name] == '=')
			return (g_env[i]);
		i++;
	}
	return (NULL);
}

/* CHECKS IF A VARIABLE IS EQUAL TO <<VALUE>> */

bool	env_var_is_value(char *var_name, char *value)
{
	char	*env_value;

	env_value = env_get_value(var_name);
	if (env_value)
		if (ft_strncmp(env_value, value, ft_strlen(value) + 1) == 0)
			return (true);
	return (false);
}

bool	env_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
