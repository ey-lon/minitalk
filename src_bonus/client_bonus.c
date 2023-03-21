/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:00 by abettini          #+#    #+#             */
/*   Updated: 2023/01/24 10:25:02 by abettini         ###   ########.fr       */
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
	if (signal == SIGUSR1)
	{
		write(1, "Message Sent!\n", 14);
		exit(0);
	}
}

static void	ft_conv(char c, int pid)
{
	int	i;
	int	check;

	i = 0;
	while (i < 8)
	{
		while (g_check)
			usleep(0);
		g_check = 1;
		if (c & 1 << i)
			check = kill(pid, SIGUSR2);
		else
			check = kill(pid, SIGUSR1);
		if (check == -1)
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
		ft_conv(str[i], pid);
		i++;
	}
	ft_conv('\0', pid);
}

int	main(int argc, char **argv)
{
	int	s_pid;

	signal(SIGUSR1, ft_msgstat);
	signal(SIGUSR2, ft_msgstat);
	if (argc == 3 && argv[2][0])
	{
		s_pid = ft_atoi(argv[1]);
		if (s_pid > 0)
		{
			ft_sendmsg(argv[2], s_pid);
			while (1)
				pause();
		}
	}
	return (0);
}
