# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/08 10:45:53 by ntrancha          #+#    #+#              #
#    Updated: 2016/03/18 13:05:55 by ntrancha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTEUR	=	ntrancha

PROJECT	=	Wifi

NAME	=	Wifi_database

FLAG	=	-Wall -Wextra -Werror -g
   
HEADER	=	includes/macros.h

GIT		=	https://github.com/$(AUTEUR)/

SCRIPT	= 	$(GIT)Script.git 

DEPOT	= 	$(GIT)$(PROJECT).git

all: fclean $(NAME)

update:
	@echo "Update ..."
	@echo "5"
	@sleep 1
	@echo "4"
	@sleep 1
	@echo "3"
	@sleep 1
	@echo "2"
	@sleep 1
	@echo "1"
	@sleep 1
	@git clone $(DEPOT) tmp > /dev/null 2> /dev/null
	@cd tmp/; cp -R * ..; cd ..; rm -rf tmp/
	@echo "Done"

$(NAME):
	@gcc *.c libft/libft.a $(FLAG) -o $(NAME)

.PHONY: verbose quiet clean fclean re install proto reset binaire fichier	\
timestamp test dynamique make maker tools clean_tools reboot finstall help	\
update all libso

clean:
	@rm -rf *.o
 
fclean: clean
	@rm -rf $(NAME)
			 
re: fclean $(NAME)
