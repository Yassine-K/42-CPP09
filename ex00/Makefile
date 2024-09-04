NAME = btc

SRC = BitcoinExchange.cpp	main.cpp

OBJ = ${SRC:.cpp=.o}

INC = BitcoinExchange.hpp

WWW = -Wall -Wextra -Werror

SUP = -std=c++98

%.o: %.cpp ${INC}
	@c++ ${WWW} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ}
	@c++ $^ -o $@ ${SUP}

clean:
	@rm -rf ${OBJ}

fclean:
	@rm -rf ${OBJ} ${NAME}

re: fclean all

.PHONY: all clean fclean re