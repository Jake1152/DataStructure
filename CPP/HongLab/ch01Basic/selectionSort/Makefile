NAME = selectionSort

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = selectionSort.cpp
OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
# PHONY source => https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html