# COLORS
GREEN = \033[0;32m
GREENGREEN = \033[38;5;46m
RED = \033[0;31m
BLUE = \033[0;34m
GREY = \033[38;5;240m
RESET = \033[0m

NAME	=	cat

LIBFT	=	includes/libft

HEADERS	=	headers

DIR_S	=	srcs

DIR_O	=	obj

O_SRCS	:=	srcs/main.c 

SRCS	:=	$(O_SRCS)

OBJS	:= $(SRCS:%.c=$(DIR_O)/%.o)

SUB_DIR_O := $(shell find $(DIR_S) -type d)
SUB_DIR_O := $(SUB_DIR_O:%=$(DIR_O)/%)

DEPS	=	$(HEADERS)/pipex.h

CC		=	gcc

# Change optimization flag to -O3 for faster execution
CFLAGS	=	-O3 -Wall -Wextra -Werror

LIBS	=	-lm -L./$(LIBFT) -lft

INCLUDES	= -I/$(LIBFT)/ -I/headers/

$(DIR_O)/%.o: %.c
	@mkdir -p $(DIR_O)
	@mkdir -p $(SUB_DIR_O)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(GREEN)//$(RESET)\c"

$(NAME):	$(DEPS) $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "\n\n[$(GREENGREEN)$(NAME)$(RESET)]: $(NAME) was created\n$(GREENGREEN)"
	@cat includes/graphic_assets/logo

all:		$(NAME)

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(DIR_O)
	@echo "[$(GREENGREEN)Pipex$(RESET)]: $(RED)Objects Directory was deleted$(RESET)"
	@echo "[$(GREENGREEN)Pipex$(RESET)]: $(RED)Object Files were deleted$(RESET)"

fclean:	clean
	@rm -f $(LIBFT)/libft.a
	@echo "[$(GREENGREEN)Pipex$(RESET)]: $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "[$(GREENGREEN)Pipex$(RESET)]: $(RED)$(NAME) was deleted$(RESET)\n"

re:			fclean all

.PHONY:		all clean fclean re bonus
