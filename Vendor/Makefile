# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/08 10:45:53 by ntrancha          #+#    #+#              #
#    Updated: 2016/03/18 21:57:16 by ntrancha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	UPDATE

FLAG	=	-Wall -Wextra -Werror -g
   
$(NAME):
	@echo "#!/bin/sh\nwget \"https://code.wireshark.org/review/gitweb?p=wireshark.git;a=blob_plain;f=manuf;hb=HEAD\" -O .result 2> /dev/null" > script.sh
	@chmod +x script.sh
	@gcc main.c ../libft/libft.a $(FLAG) -o $(NAME)
	@./UPDATE > List_vendor
	@echo "Base de données MAC_VENDOR mise à jour (`wc -l List_vendor|cut -d " " -f1` entrées)."
	@rm -rf UPDATE .result script.sh
