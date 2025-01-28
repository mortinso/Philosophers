NAME	=	philo
CC		=	@cc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=thread
RM		=	rm -rf

OBJ_DIR	=	obj
SRC_PHL	=	main.c check.c init.c routine.c utils.c

SRCS	=	$(addprefix src/, $(SRC_PHL))

OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRC_PHL:%.c=%.o))

INC		=	-pthread

GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
RED		=	"\033[0;31m"
NC		=	"\033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@clear -x
	@echo $(YELLOW)"Compiling..."$(NC)
	@$(CC) $(CFLAGS) $(INC) $(SRCS) -o $(NAME)
	@echo $(GREEN)"Philosophers ready!"$(NC)

$(OBJ_DIR)/%.o: $(SRCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

val: $(NAME)
	@valgrind --memcheck:leak-check=full --memcheck:track-origins=yes --memcheck:show-leak-kinds=all ./philo 4 310 200 100

clean:
	@$(RM) $(OBJS) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo $(GREEN)"Files cleaned."$(NC)

re: fclean all

.PHONY: all clean fclean re val

#test valgrind with --tool=drd and --tool=helgrind (separately)
