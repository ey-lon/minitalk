/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:08 by abettini          #+#    #+#             */
/*   Updated: 2024/01/16 15:39:25 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "../Libft/libft.h"

static char	*ft_free_join(char *old_msg, char chr)
{
	char	*full_msg;
	char	str[2];

	str[1] = '\0';
	str[0] = chr;
	if (!old_msg)
	{
		old_msg = ft_calloc(1, 1);
	}
	full_msg = ft_strjoin(old_msg, str);
	free(old_msg);
	return (full_msg);
}

static void	ft_sighandler(int signal, siginfo_t *info, void *ucontext)
{
	static char	*full_msg;
	static char	chr;
	static int	i;

	(void)ucontext;
	if (signal == SIGUSR2)
		chr = chr | 1 << i;
	i++;
	if (i >= 8)
	{
		if (chr)
			full_msg = ft_free_join(full_msg, chr);
		else
		{
			ft_printf("[Client_%d]:\n\"%s\"\n", info->si_pid, full_msg);
			free(full_msg);
			full_msg = 0;
		}
		i = 0;
		chr = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sighandler;
	pid = getpid();
	ft_printf("Server_PID = [%d]\n", pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
