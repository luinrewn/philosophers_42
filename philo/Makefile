NAME := philo

CC := clang
CFLAGS := -Wall -Werror -Wextra
SRC := ft_atol.c ft_strlen.c main.c vlaid_input.c init.c clean.c pthreads.c sleepydipop.c philo_routine.c printing.c monitoring.c
OBJ_DIR := ./obj
DEP_DIR := ./dep

OBJ := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP := $(patsubst %.c,$(DEP_DIR)/%.d,$(SRC))
#OBJ := $(SRC:.c=$(OBJ_DIR)/%.o)
#DEP := $(SRC:.c=$(DEP_DIR)/%.d)
HEADERS := -Iphilo.h

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(DEP_DIR):
	mkdir -p $(DEP_DIR)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

-include $(DEP)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJ) -o $(NAME)
	@echo "Making objects and stuff.."

clean:
	@rm -f $(OBJ) $(DEP)
	@echo "Cleaning objects and dependecies.."

fclean:	clean
	@rm -f $(NAME)
	@echo "Cleaning all..."

re: fclean all

m: re
	@make clean

debug: CFLAGS += -g
debug: fclean $(NAME)
	@echo "Build debug..."

git: fclean
	rm .*.swp; git add .; git commit -m "make commit"; git push;
.PHONY: clean fclean re all git
