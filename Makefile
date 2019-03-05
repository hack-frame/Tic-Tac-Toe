
NAME = tic_tac

SRCS 	:=	$(wildcard ./src/*.cpp)

#	project object files
OBJS    :=	$(SRCS:.cpp=.o)

INCLUDES	=	-I ./inc\
				-I ./frameworks/SDL2.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I ./frameworks/SDL2_mixer.framework/Headers \
				-I ./frameworks/SDL2_net.framework/Headers \
				-F ./frameworks 
				
FRAMEWORKS	=	-F ./frameworks \
				-rpath ./frameworks \
				-framework OpenGL -framework AppKit -framework OpenCl \
				-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
				-framework SDL2_mixer -framework SDL2_net

CXX      := clang++
CXXFLAGS := -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $@ -lncurses $(INCLUDES) $(FRAMEWORKS) #-fsanitize=address

%.o: %.cpp
	$(CXX) -o $@ -c $< $(INCLUDES)

clean:
	@rm -f $(OBJS)
	@echo "[INFO] Objects removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] $(NAME) removed!"

re:     fclean all

.PHONY: all clean fclean format re
