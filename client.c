/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:16:23 by mkuehl            #+#    #+#             */
/*   Updated: 2021/10/18 16:39:11 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_is_pid(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		while ((*str >= '0') && (*str <= '9'))
			str++;
		if (*str != '\0')
			return (0);
	}
	return (1);
}

static int	ft_atoi(char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' || \
		*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * negative);
}

static void	ft_confirm_from_server(int signum)
{
	if (signum == SIGUSR1)
		g_minitalk.flag = 1;
}

static void	ft_send_signal(int pid, char c)
{
	int	num;

	num = 128;
	while (num > 0)
	{
		usleep(50);
		g_minitalk.flag = 0;
		if (num & c)
		{
			if (kill(pid, SIGUSR1) == -1)
				write(1, "Server not found\n", 17);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				write(1, "Server not found\n", 17);
		}
		num /= 2;
		while (!g_minitalk.flag && c != '\0')
			;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;

	signal(SIGUSR1, ft_confirm_from_server);
	if (argc == 3)
	{
		if (ft_atoi(argv[1]) == 0 || ft_is_pid(argv[1]) == 0)
		{
			write(1, "Wrong server pid\n", 17);
			return (-1);
		}
		i = 0;
		pid = ft_atoi(argv[1]);
		while (argv[2][i])
			ft_send_signal(pid, argv[2][i++]);
		ft_send_signal(pid, '\0');
	}
	else
	{
		write(1, "Wrong number of arguments\n", 26);
		return (-1);
	}
	return (0);
}
