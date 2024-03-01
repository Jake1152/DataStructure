NAME = swap

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = swap.cpp
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


# (NAME): (dependency) \
	(mat)

# <NAME>: <prerequisites> \
 	<recipe>
# NAME : 일반적으로 프로그램에 의해 생성되는 파일의 이름이다. 혹은 'clean' 과 같이 수행할 작업의 이름이 되기도 한다(이에 대해서는 아래에서 설명)
# prerequisites : NAME을 생성하기 위해 사용되는 인풋(input) 파일들이다. 혹은 NAME이 의존(depends on)하는 파일들이다. 
# recipe : make 프로그램이 실행하는 명령이다. recipe 라인에는 꼭 tab 문자를 앞에 넣어줘야 한다.

# return: arguments \
	logic

# Ref: https://code-lab1.tistory.com/370