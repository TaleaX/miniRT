AUTHORS	= dantonik, tdehne
DATE	= $$(date +%Y/%m/%d)
BUSER = ~/.brew/opt/glfw/lib/

CC			=	cc
CFLAGS		=	#-Werror -Wextra -Wall

NAME 		=	miniRT

OBJ_DIR		=	obj/
SRC_DIR		=	src/
INC_DIR		=	include/
LIBA = MLX42/build/libmlx42.a

GNL_DIR = ./get_next_line/
GNL = ./get_next_line/gnl.a

SRC_NAME	=	main init vector vector_2 vector_3 hit light color_utils color_room utils \
				create error_handling \
				parser/parser parser/string_utils parser/parse_float
INC_NAME	=	miniRT vector color calc structs parser

SRC_FILES	=	$(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_NAME)))
OBJ_FILES	=	$(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRC_NAME)))
INC_FILES	=	$(addsuffix .h, $(addprefix $(INC_DIR), $(INC_NAME)))

ifeq ($(shell uname -s),Linux)
	OS := Linux
	LIB	=	-ldl -lglfw -pthread -lm
else ifeq ($(shell uname -s),Darwin)
	ifeq ($(shell uname -p),arm)
		OS := MacOS silicone
		LIB		=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/
	else
		OS := MacOS intel
		LIB		=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L ~/.brew/opt/glfw/lib/
	endif
else
	OS := Unknown
	exit 1
endif

$(info Compiling for $(OS))

all : $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser

$(GNL):
	@make -C $(GNL_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR) -o $@ -IMLX42/include
#
$(NAME) : $(GNL) $(OBJ_DIR) $(OBJ_FILES) $(INC_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIBA) $(LIB) -I$(INC_DIR) $(GNL)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(GNL_DIR)

fclean: clean
	@rm -f $(NAME) .header
	@make fclean -C $(GNL_DIR)

re: fclean all

