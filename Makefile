#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
TCOL = $(CYAN)

#----------------------------------------------

CC = cc

RM = rm -rf

FLAGS = -Wall -Werror -Wextra -g

NAME = minitalk

SNAME = server
CNAME = client

LIBFT = libft.a

SER =	server.c
CLT =	client.c

SERBNS =	server_bonus.c
CLTBNS =	client_bonus.c

#paths_and_prefix--------------------------------

SRC_F =	src/
BNS_F =	src_bonus/
LBT_F =	Libft/

SER := $(addprefix $(SRC_F),$(SER))
CLT := $(addprefix $(SRC_F),$(CLT))

SERBNS := $(addprefix $(BNS_F),$(SERBNS))
CLTBNS := $(addprefix $(BNS_F),$(CLTBNS))

LIBFT := $(addprefix $(LBT_F),$(LIBFT))

#object_files-----------------------------------

SER_O = $(SER:.c=.o)
CLT_O = $(CLT:.c=.o)

SERBNS_O = $(SERBNS:.c=.o)
CLTBNS_O = $(CLTBNS:.c=.o)

#rules------------------------------------------

all: $(NAME)

libcomp:
		@make -C Libft

libclean:
		@make clean -C Libft

libfclean:
		@make fclean -C Libft
	
$(NAME): libcomp $(SER_O) $(CLT_O)
	$(CC) $(FLAGS) $(SER_O) $(LIBFT) -o $(SNAME)
	$(CC) $(FLAGS) $(CLT_O) $(LIBFT) -o $(CNAME)
	echo "$(TCOL)make ($(NAME))$(NOCOL)"
	
bonus: libcomp $(SERBNS_O) $(CLTBNS_O)
	$(CC) $(FLAGS) $(SERBNS_O) $(LIBFT) -o $(SNAME)
	$(CC) $(FLAGS) $(CLTBNS_O) $(LIBFT) -o $(CNAME)
	echo "$(TCOL)make bonus $(NAME)$(NOCOL)"
		
clean:		libclean
	$(RM) $(SER_O)
	$(RM) $(CLT_O)
	$(RM) $(SERBNS_O)
	$(RM) $(CLTBNS_O)
	echo "$(TCOL)make clean ($(NAME))$(NOCOL)"

fclean:   	libfclean clean
	$(RM) $(SNAME)
	$(RM) $(CNAME)
	echo "$(TCOL)make fclean ($(NAME))$(NOCOL)"

re: fclean all

.PHONY: all re clean fclean bonus libcomp libclean libfclean

.SILENT:
