################ PROGRAM ################

NAME	    =    raycaster

################ TERMINAL ###############

RMV        =        rm -f
MKD        =        mkdir
PRT        =        printf
MKE        =        make
CPY        =        cp

################# COLORS ################

--GRN    =        \033[32m
--RED    =        \033[31m
--WHT    =        \033[39m

################# DIRS ##################

_SRC    =        src/
_OBJ    =        obj/
_LIB    =        libs/
_BIN    =        ./

############### COMPILER ################

CC          =        c++
CFLAGS      =        -Wall -Werror -Wextra -std=c++17 -O2
LDFLAGS     =        
LIBS        =        -lm

############### SOURCE FILES ############

SRCS    =        $(wildcard $(_SRC)*.cpp)
OBJS    =        $(patsubst $(_SRC)%.cpp,$(_OBJ)%.o,$(SRCS))
DEPS    =        $(OBJS:.o=.d)

################ RULES ##################

all: $(NAME)

$(_OBJ)%.o: $(_SRC)%.cpp
	@$(MKD) -p $(@D)
	@$(PRT) "$(--GRN)Compiling $(--WHT)$<$(--WHT)\n"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJS)
	@$(PRT) "$(--GRN)Linking $(--WHT)$(NAME)$(--WHT)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@$(PRT) "$(--GRN)Build complete: $(--WHT)$(NAME)$(--WHT)\n"

############## STRUCTURE ################

clean:
	@$(PRT) "$(--RED)Cleaning object files$(--WHT)\n"
	@$(RMV) -r $(_OBJ)

fclean: clean
	@$(PRT) "$(--RED)Removing $(NAME)$(--WHT)\n"
	@$(RMV) $(NAME)

re: fclean all

run: $(NAME)
	@$(PRT) "$(--GRN)Running $(NAME)$(--WHT)\n"
	@./$(NAME)

debug: CFLAGS += -g -fsanitize=address
debug: re

valgrind: CFLAGS += -g
valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

############### CMAKE & TESTS ###########

cmake:
	@$(PRT) "$(--GRN)Configuring with CMake$(--WHT)\n"
	@cmake -B build -S .

build-cmake: cmake
	@$(PRT) "$(--GRN)Building with CMake$(--WHT)\n"
	@cmake --build build

tests: cmake
	@$(PRT) "$(--GRN)Building and running tests$(--WHT)\n"
	@cmake --build build
	@cd build && ctest --output-on-failure

tests-verbose: cmake
	@$(PRT) "$(--GRN)Building and running tests (verbose)$(--WHT)\n"
	@cmake --build build
	@cd build && ctest --verbose

.PHONY: all clean fclean re run debug valgrind cmake build-cmake tests tests-verbose

-include $(DEPS)
