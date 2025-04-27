NAME = BinaryTree
CXX = g++
CXXFLAGS = -g -MMD -MP -I../shared

# -MMD: 각 .o 파일 만들 때 .d 파일(의존성 목록)도 같이 만들어줌.
# -MP: 헤더 파일이 나중에 삭제되더라도 에러가 안 나게 dummy rule 추가.
# -include $(DEPS): .d 파일을 읽어와서 자동으로 의존성 추가.
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