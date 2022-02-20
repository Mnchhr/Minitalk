/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:16:39 by mkuehl            #+#    #+#             */
/*   Updated: 2021/10/18 16:30:52 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putnbr_fd(int n, int fd)
{
	long	i;
	char	c;

	i = n;
	if (i < 0)
	{
		write(fd, "-", 1);
		i = -i;
	}
	if (i >= 10)
	{
		ft_putnbr_fd((i / 10), fd);
		c = (i % 10 + '0');
		write(fd, &c, 1);
	}
	else
	{
		c = (i + '0');
		write(fd, &c, 1);
	}
}

static void	ft_convert_to_char(int bit)
{
	if (g_minitalk.counter--)
	{
		g_minitalk.newchar <<= 1;
		g_minitalk.newchar |= bit;
	}
	if (!g_minitalk.counter)
	{
		if (g_minitalk.newchar == '\0')
		{
			write(1, "\n", 1);
			write(1, &g_minitalk.newchar, 1);
		}
		else
			write(1, &g_minitalk.newchar, 1);
		g_minitalk.newchar = 0;
		g_minitalk.counter = 8;
	}
}

static void	ft_sigact(int signum, siginfo_t *sig, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		ft_convert_to_char(1);
	else if (signum == SIGUSR2)
		ft_convert_to_char(0);
	if (kill(sig->si_pid, SIGUSR1) == -1)
		write(1, "Client not found\n", 17);
}

int	main(void)
{
	struct sigaction	sigact;
	pid_t				pid;

	g_minitalk.counter = 8;
	g_minitalk.newchar = 0;
	g_minitalk.flag = 0;
	pid = getpid();
	write(1, "The server PID is ", 18);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigact.sa_sigaction = ft_sigact;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
