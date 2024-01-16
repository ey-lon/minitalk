/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:00 by abettini          #+#    #+#             */
/*   Updated: 2024/01/16 15:12:56 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../Libft/libft.h"

int	g_check = 0;

static void	ft_msgstat(int signal)
{
	g_check = 0;
	(void)signal;
}

static void	ft_sendchr(char c, int pid)
{
	int	i;
	int	signal;

	i = 0;
	while (i < 8)
	{
		while (g_check)
			usleep(0);
		g_check = 1;
		if (c & 1 << i)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		if (kill(pid, signal) == -1)
			exit(0);
		i++;
	}
}

static void	ft_sendmsg(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_sendchr(str[i], pid);
		i++;
	}
	ft_sendchr('\0', pid);
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc == 3 && argv[2][0])
	{
		signal(SIGUSR1, ft_msgstat);
		signal(SIGUSR2, ft_msgstat);
		server_pid = ft_atoi(argv[1]);
		if (server_pid > 0)
		{
			ft_sendmsg(argv[2], server_pid);
		}
	}
	return (0);
}
