SRCS =	main.cpp \
		BitcoinExchange.cpp

NAME = btc
OBJS = $(SRCS:.cpp=.o)
CC = c++ -g -std=c++98 -Wall -Wextra -Werror

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
