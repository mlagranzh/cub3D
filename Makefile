NAME		=	cub3d

DIR_MINILIBX	=	minilibx/
DIR_LIBA		=	libft/

HEADER		=	cub3d.h

GCC			=	gcc -g#-Wall -Wextra -Werror

#DIR_PARSER 	= 	parser_utils/
#DIR_UTILS	=	utils/
#DIR_EXECUTE	=	execute/

#SRC_PARSER	= 	preparser.c quotes.c dollar.c args.c redirect.c comm_args.c control_symbol.c \
				pars_pipe.c redirect_utils1.c redirect_delimiter.c dollar_utils.c
#SRC_UTILS	=	utils0.c utils1.c utils2.c utils3.c utils4.c utils5.c utils6.c utils7.c
#SRC_EXECUTE	=	pipex.c cd.c exit.c unset.c echo.c pwd.c env.c export.c execute.c

#SRCS		= main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRCS		= cleonia/vse_huinia_davai_po_novoi.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

#SRCS_PARSER	=	$(addprefix $(DIR_PARSER), $(SRC_PARSER))
#UTILS		=	$(addprefix $(DIR_UTILS), $(SRC_UTILS))
#EXECUTE		=	$(addprefix $(DIR_EXECUTE), $(SRC_EXECUTE))

#OBJ			=	$(SRCS:.c=.o) $(SRCS_PARSER:.c=.o) $(UTILS:.c=.o) $(EXECUTE:.c=.o)

OBJ			=	$(SRCS:.c=.o)
all: libft mlx $(NAME)

%.o: %.c $(HEADER)
	$(GCC) -Imlx -c $< -o $@

$(NAME): $(OBJ)
#	@echo "\033[0;35mКомпилю cub3d...\033[0;32m"
#	@echo "\033[0;35mСоздаю исполняемый файл...\033[0;32m"
	$(GCC) -o $(NAME) $(OBJ) libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit
#	@echo "DONE! Запускаю..."
#	@./cub3d

libft:
#	@echo "\033[0;35mКомпилю libft... \033[0;32m"
	make -C $(DIR_LIBA)
	
mlx:
#	@echo "\033[0;35mКомпилю minilibx... \033[0;32m"
	make -C $(DIR_MINILIBX)

clean:
#	@echo "\033[0;35mУдаляю объектные файлы...\033[0;31m"
	make clean -C $(DIR_LIBA)
#	@echo "\033[0;35mcub3d: ЧИСТКА ОБЪЕКТНИКОВ...\033[0;31m"
	rm -f $(OBJ)

fclean: clean
#	@echo "\033[0;35mУдаляю исполняемый файл...\033[0;31m"
	rm -f $(NAME)
	make fclean -C $(DIR_LIBA)

re: fclean all

.PHONY: all libft clean fclean re

