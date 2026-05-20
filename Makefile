
NAME = project_generator
SRCS = main.cpp src/utils.cpp src/ProjectGenerator.cpp src/FileManager.cpp src/TemplateManager.cpp
OBJ_DIR = build
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
CXX = c++
CXXFLAGS = -g -Wall -Wextra -Werror -std=c++98
INCLUDE = -Ilib

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $(NAME)
	@echo "Executable created!"

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "Build directory deleted!"; \
	else \
		echo "No build directory to delete!"; \
	fi

fclean: clean
	@rm -f $(NAME)
	@echo "Executable deleted!"

re: fclean
	@echo "Recreating build directory..."
	@echo "Remaking executables..."
	@make --no-print-directory

run: re
	@./$(NAME)

val: re
	@valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re run val