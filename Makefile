NAME = openGL

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./include
LIB_DIR = ./lib
LIBS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

SRC_FILES = $(shell ls $(SRC_DIR))

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

GCC = g++ -Wall -Werror -Wextra -std=c++11

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(OBJ) -o $(NAME) -I $(INC_DIR) -L $(LIB_DIR) $(LIBS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	$(GCC) -I $(INC_DIR) -L $(LIB_DIR) $(LIBS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
