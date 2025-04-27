NAME = BinaryTree
CXX = g++
CXXFLAGS = -g -MMD -MP -I../shared
# CXXFLAGS = -g -MMD -MP #-Wall -Wextra -Werror
# CXXFLAGS = -g -Wall -Wextra -Werror
RM = rm -f

SRCS = BinaryTree.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d) # 추가!

# %.o : %.cpp
# 	$(CXX) $(CXXFLAGS) -c $^ -o $@
# 의존성 파일 처리하지 않도록 변경
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

all : $(NAME)

clean :
	$(RM) $(OBJS) $(DEPS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

-include $(DEPS) # 추가! .d 파일을 포함해서 의존성 자동 반영

.PHONY: all clean fclean re