/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:08 by abettini          #+#    #+#             */
/*   Updated: 2023/03/26 15:00:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../Libft/libft.h"

static char	*ft_free_join(char *old_msg, char *new_char)
{
	char	*full_msg;

	if (!old_msg)
		old_msg = ft_calloc(1, 1);
	full_msg = ft_strjoin(old_msg, new_char);
	free(old_msg);
	return (full_msg);
}

static int	ft_deal_msg(int signal, int pid)
{
	static char	*full_msg;
	static char	msg;
	static int	i;
	int			status;

	status = 0;
	if (signal == SIGUSR2)
		msg = msg | 1 << i;
	i++;
	if (i >= 8)
	{
		if (msg)
			full_msg = ft_free_join(full_msg, &msg);
		else if (msg == '\0')
		{
			ft_printf("[Client_%d]:\n\"%s\"\n", pid, full_msg);
			free(full_msg);
			full_msg = NULL;
			status = 1;
		}
		i = 0;
		msg = 0;
	}
	return (status);
}

static void	ft_sighandler(int signal, siginfo_t *info, void *ucontext)
{
	static int	pid;

	(void)ucontext;
	if (!pid)
	{
		pid = info->si_pid;
		kill(pid, SIGUSR1);
	}
	else if (pid == info->si_pid)
	{
		if (ft_deal_msg(signal, pid))
		{
			kill(pid, SIGUSR2);
			pid = 0;
		}
		else
			kill(pid, SIGUSR1);
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO | SA_NODEFER;
	sa.sa_sigaction = ft_sighandler;
	pid = getpid();
	ft_printf("Server_PID = [%d]\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
