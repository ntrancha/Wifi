/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 21:15:38 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/18 21:51:59 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

void        decoupe(char *line)
{
    int     index;
    int     status;

    index = -1;
    status = 0;
    while (line[++index])
    {
        if (status == 0)
        {
            if (line[index] == ' ' || line[index] == '\t')
                status = 1;
            else
                ft_putchar(line[index]);
        }
        else if (status == 1)
        {
            if (line[index] != ' ' && line[index] != '\t')
            {
                ft_putstr("   ");
                status = 2;
            }
        }
        if (status == 2)
        {
            if (line[index] == ' ' || line[index] == '\t' || line[index] == '\0')
                status = 3;
            else
                ft_putchar(line[index]);
        }
    }
    ft_putendl("");
}

int         main(void)
{
    char    *file;
    char    **line;
    int     num;

    system("./script.sh 2> /dev/null");
    file = ft_get_file(".result");
    if (file && ft_strlen(file) > 100)
    {
        num = -1;
        line = ft_strsplit(file, '\n');
        while (line[++num])
            if ((line[num])[0] != '#'  && (line[num])[0] != ' ')
                if ((line[num])[0] != '\t' && ft_strlen(line[num]) > 10)
                    decoupe(line[num]);
        ft_tabstrdel(&line);
    }
    ft_strdel(&file);
    return (0);
}
