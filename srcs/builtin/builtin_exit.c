/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:10:48 by yunseo            #+#    #+#             */
/*   Updated: 2024/10/12 19:10:48 by yunseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

long long	ft_atoll(char *nptr)
{
	int			negative;
	long long	result;

	negative = 0;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
		negative = 1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	if (negative)
		result = -result;
	return (result);
}

int	exit_count_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	int		len;
	char	*ptr;
	int		negative;
	int		tmp;

	len = exit_count_len(n);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	negative = 0;
	if (!ptr)
		return (NULL);
	if (n < 0)
		negative = 1;
	ptr[len] = '\0';
	while (len--)
	{
		tmp = (n % 10);
		if (tmp < 0)
			tmp = -tmp;
		ptr[len] = tmp + '0';
		n /= 10;
	}
	if (negative)
		ptr[0] = '-';
	return (ptr);
}

int	is_numeric(char *str)
{
	char	*num;
	int		result;

	result = 0;
	if (*str == '+')
		str++;
	num = ft_lltoa(ft_atoll(str));
	if (ft_strncmp(str, num, ft_strlen(str)) == 0)
		result = 1;
	free(num);
	return (result);
}

int	builtin_exit(t_list *list)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (list == NULL)
		shell_exit(0);
	if (is_numeric(list->content))
	{
		if (list->next != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		shell_exit(ft_atoi(list->content));
	}
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(list->content, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	shell_exit(2);
	return (2);
}
