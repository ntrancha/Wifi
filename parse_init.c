/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:39:03 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 20:54:01 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"

int     point_csv(char *file)
{
    int size;

    size = ft_strlen(file);
    if (size < 4)
        return (0);
    if (file[size - 1] == 'v' && file[size - 2] == 's')
        if (file[size - 3] == 'c' && file[size - 4] == '.')
            return (1);
    return (0);
}

void    parse_csv(char **file_content, t_database *data)
{
    int         line;
    int         status;

    line = -1;
    status = 0;
    while (file_content[++line])
    {
        if (status == 1 && ft_strlen(file_content[line]) > 50)
            if (ft_strcchr(file_content[line], "Station MAC, First time seen,") == 0)
                parse_station(file_content[line], data);
        if (status == 2 && ft_strlen(file_content[line]) > 50)
            parse_client(file_content[line], data);
        if (ft_strcchr(file_content[line], "BSSID, First time seen") == 1)
            status = 1;
        if (ft_strcchr(file_content[line], "Station MAC, First time seen,") == 1)
            status = 2;
    }
}

void    get_csv(char *file, t_database *data)
{
    char    *content;
    char    *pathfile;
    char    **tab;

    pathfile = ft_strjoin("cap/", file);
    content = ft_get_file(pathfile);
    tab = ft_strsplit(content, '\n');
    parse_csv(tab, data);    
    ft_tabstrdel(&tab);
    ft_strdelt(&content, &pathfile);
}


t_database      *parse_wifi(char *str)
{
    char    **tab;
    int     index;
    t_database  *data;
    
    data = database_init();
    index = -1;
    tab = ft_getdirtab(str, NULL);
    while (tab[++index])
        if (point_csv(tab[index]))
            get_csv(tab[index], data);
    ft_tabstrdel(&tab);
    return (data);
}
