/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:00 by abettini          #+#    #+#             */
/*   Updated: 2023/03/26 14:11:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../Libft/libft.h"

int	g_check = 0;

static void	ft_msg_stat(int signal)
{
	if (signal == SIGUSR2)
	{
		write(1, "\rMessage Sent!\n", 15);
		exit(0);
	}
	g_check = 1;
}

static void	ft_conv(char c, int pid)
{
	int	i;
	int	check;

	i = 0;
	while (i < 8)
	{
		while (!g_check)
			usleep(0);
		g_check = 0;
		if (c & 1 << i)
			check = kill(pid, SIGUSR2);
		else
			check = kill(pid, SIGUSR1);
		if (check == -1)
			exit(0);
		i++;
	}
}

static void	ft_send_msg(char *str, int pid)
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

static void	ft_establish_connection(int pid)
{
	while (!g_check)
	{
		if (kill(pid, SIGUSR1) == -1)
			exit(0);
		else if (!g_check)
		{
			write(1, "\rSending...", 11);
			sleep(1);
		}
	}
}

int	main(int argc, char **argv)
{
	int	s_pid;

	signal(SIGUSR1, ft_msg_stat);
	signal(SIGUSR2, ft_msg_stat);
	if (argc == 3 && argv[2][0])
	{
		s_pid = ft_atoi(argv[1]);
		if (s_pid > 0)
		{
			ft_establish_connection(s_pid);
			ft_send_msg(argv[2], s_pid);
			while (1)
				pause();
		}
	}
	return (0);
}
