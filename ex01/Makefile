SRCS =	main.cpp \
		RPN.cpp

NAME = RPN
OBJS = $(SRCS:.cpp=.o)
CC = c++ -std=c++98 -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS) 
	 $(CC) -o $(NAME) $(OBJS)

$(OBJS) : $(SRCS)
	$(CC) -c $(@:.o=.cpp) -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
