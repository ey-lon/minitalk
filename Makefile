#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
TCOL = $(CYAN)
RMD = $(GREEN)successfully $(RED)removed$(NOCOL)
CMP = $(GREEN)successfully compiled$(NOCOL)

#----------------------------------------------

CC = cc

NAME = minitalk

LIBFT = Libft/libft.a

SNAME = server
CNAME = client

SER =	src/server.c
CLT =	src/client.c

SERBNS =	src_bonus/server_bonus.c
CLTBNS =	src_bonus/client_bonus.c

FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): libcomp comp

libcomp:
		@make -C Libft
	
comp:
	$(CC) $(FLAGS) $(SER) $(LIBFT) -o $(SNAME)
	$(CC) $(FLAGS) $(CLT) $(LIBFT) -o $(CNAME)
	echo "$(TCOL)$(SNAME) and $(CNAME) $(CMP)"
	
bonus: libcomp
	$(CC) $(FLAGS) $(SERBNS) $(LIBFT) -o $(SNAME)
	$(CC) $(FLAGS) $(CLTBNS) $(LIBFT) -o $(CNAME)
	echo "$(TCOL)$(SNAME) and $(CNAME) (bonus version) $(CMP)"
   
libclean:
		@make clean -C Libft
		
clean:		libclean

libfclean:
		@make fclean -C Libft

fclean:   	libfclean
		if [ -f $(SNAME) ] || [ -f $(CNAME) ]; then\
			rm -rf $(SNAME);\
			rm -rf $(CNAME);\
			echo "$(TCOL)$(SNAME) and $(CNAME) $(RMD)";\
		fi
		
re: fclean all

.PHONY: all re clean fclean bonus

.SILENT:
