NAME			=	cub3d

HEADER			=	cub3d.h

GCC				=	gcc -g3#-Wall -Wextra -Werror

DIR_LIBA		=	libft/
DIR_MINILIBX	=	mlx/
DIR_UTILS		=	utils/
DIR_MAP			=	analysis_cub_file/
DIR_GNL			=	get_next_line/

DIR_BONUS		=	bonus/

SRC				=	main.c draw_screen.c draw_minimap.c texture.c motion.c sprites.c hook.c
SRC_UTILS		=	utils0.c utils1.c utils2.c utils3.c
SRC_MAP			=	read_cub_file.c read_map_param.c checking_map_for_closure.c
SRC_GNL			=	get_next_line.c get_next_line_utils.c

SRC_BONUS		=	fog.c screenshot.c

UTILS			=	$(addprefix $(DIR_UTILS), $(SRC_UTILS))
MAP				=	$(addprefix $(DIR_MAP), $(SRC_MAP))
GNL				=	$(addprefix $(DIR_GNL), $(SRC_GNL))
BONUS			=	$(addprefix $(DIR_BONUS), $(SRC_BONUS))

OBJ				=	$(SRC:.c=.o) $(UTILS:.c=.o) $(MAP:.c=.o) $(GNL:.c=.o) $(BONUS:.c=.o)

MAP_OBJ			=	$(UTILS:.c=.o) $(MAP:.c=.o) $(GNL:.c=.o)

all				:	mlx libft $(NAME) 

%.o				:	%.c $(HEADER)
					$(GCC) -Imlx -c $< -o $@

$(NAME)			:	$(OBJ)
					make -C mlx/
#					@echo "\033[0;35mКомпилю cub3d...\033[0;32m"
#					@echo "\033[0;35mСоздаю исполняемый файл...\033[0;32m"
					$(GCC) -o $(NAME) $(OBJ) libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit
#					@echo "DONE! Запускаю..."
#					@./cub3d

xpm				: mlx
				$(GCC) xpm_viewer.c -o xpm_viewer -Lmlx -lmlx -framework OpenGL -framework AppKit

map				:	clean $(MAP_OBJ)
					$(GCC) -o $(NAME) $(MAP_OBJ) libft/libft.a

mlx				:
#					@echo "\033[0;35mКомпилю minilibx... \033[0;32m"
					make -C mlx/
libft			:
#					@echo "\033[0;35mКомпилю libft... \033[0;32m"
					make -C $(DIR_LIBA)


clean			:
#					@echo "\033[0;35mУдаляю объектные файлы...\033[0;31m"
					make clean -C $(DIR_LIBA)
					make clean -C $(DIR_MINILIBX)
#					@echo "\033[0;35mcub3d: ЧИСТКА ОБЪЕКТНИКОВ...\033[0;31m"
					rm -f $(OBJ)

fclean			:	clean
#					@echo "\033[0;35mУдаляю исполняемый файл...\033[0;31m"
					rm -f $(NAME)
#					make fclean -C $(DIR_LIBA)
#					make clean -C $(DIR_MINILIBX)

re				:	fclean all

.PHONY			:	all libft clean fclean re
