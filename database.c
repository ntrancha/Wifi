/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:13:25 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/19 01:20:32 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"
#include "vendor.h"

t_database      *database_init(void)
{
    t_database  *database;

    database = ft_memalloc(sizeof(t_database));
    if (!database)
        return (NULL);
    database->stations = NULL;
    database->clients = NULL;
    database->vendors = data_vendor();
    return (database);
}

t_client        *client_new(t_database *data)
{
    t_client    *new;
    t_client    *old;

    new = ft_memalloc(sizeof(t_client));
    new->next = NULL;
    if (!data->clients)
    {
        data->clients = new;
    }
    else
    {
        old = data->clients;
        while (old && old->next)
            old = old->next;
        old->next = new;
    }
    return (new);
}

t_station       *station_new(t_database *data)
{
    t_station   *new;
    t_station   *old;

    new = ft_memalloc(sizeof(t_station));
    new->next = NULL;
    if (!data->stations)
    {
        data->stations = new;
    }
    else
    {
        old = data->stations;
        while (old && old->next)
            old = old->next;
        old->next = new;
    }
    return (new);
}
