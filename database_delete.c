/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:26:08 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 20:26:33 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"

void        delete_client(t_client *client)
{
    ft_strdel(&client->mac);
    ft_strdel(&client->first);
    ft_strdel(&client->last);
    ft_strdel(&client->power);
    ft_strdel(&client->packets);
    ft_strdel(&client->bssid);
    ft_strdel(&client->probes);
    ft_memdel((void**)&client);
}

void        delete_station(t_station *station)
{
    ft_strdel(&station->bssid);
    ft_strdel(&station->first);
    ft_strdel(&station->last);
    ft_strdel(&station->chan);
    ft_strdel(&station->power);
    ft_strdel(&station->cipher);
    ft_strdel(&station->auth);
    ft_strdel(&station->ip);
    ft_strdel(&station->iv);
    ft_strdel(&station->beacons);
    ft_strdel(&station->essid);
    ft_strdel(&station->id_len);
    ft_strdel(&station->key);
    ft_memdel((void**)&station);
}

void        delete_clients(t_database *data)
{
    t_client    *clients;
    t_client    *tmp;

    clients = data->clients;
    while (clients)
    {
        tmp = clients->next;
        delete_client(clients);
        clients = tmp;
    }
}

void        delete_stations(t_database *data)
{
    t_station  *stations;
    t_station  *next;

    stations = data->stations;
    while (stations)
    {
        next = stations->next;
        delete_station(stations);
        stations = next;
    }
    data->stations = NULL;
}

void        delete_database(t_database *data)
{
    delete_stations(data);
    delete_clients(data);
    ft_memdel((void**)&data);
}
