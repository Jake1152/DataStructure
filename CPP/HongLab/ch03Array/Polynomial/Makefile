NAME = Polynomial

CXX = g++
CXXFLAGS = #-Wall -Wextra -Werror
RM = rm -f

SRCS = main.cpp \
		Polynomial.cpp

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