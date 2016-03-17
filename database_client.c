/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:27:40 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 20:31:39 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"

t_client        *find_client_mac(t_database *data, char *mac)
{
    t_client    *clients;

    clients = data->clients;
    while (clients)
    {
        if (ft_strcmp(clients->mac, mac) == 0)
            return (clients);
        clients = clients->next;
    }
    return (NULL);
}

void            update_client(t_client *new, t_client *old)
{
    char        *tmp;

    if (ft_strcmp(new->mac, old->mac) == 0)
    {
        if (ft_strcmp(new->first, old->first) < 0)
        {
            ft_strdel(&old->first);
            old->first = ft_strdup(new->first);
        }
        if (ft_strcmp(new->last, old->last) > 0)
        {
            ft_strdel(&old->last);
            old->last = ft_strdup(new->last);
        }
        if (!old->power && new->power && ft_atoi(new->power) < ft_atoi(old->power))
        {
            ft_strdel(&old->power);
            old->power = ft_strdup(new->power);
        }
        if (!old->bssid && new->bssid)
        {
            ft_strdel(&old->bssid);
            old->bssid = ft_strdup(new->bssid);
        }
        if (!old->probes || (new->probes && ft_strlen(new->probes) > ft_strlen(old->probes)))
        {
            ft_strdel(&old->probes);
            old->probes = ft_strdup(new->probes);
        }
        if (!old->packets)
            old->packets = ft_strdup(new->packets);
        else
        {
            tmp = ft_itoa(ft_atoi(new->packets) + ft_atoi(old->packets));
            ft_strdel(&new->packets);
            old->packets = tmp;
        }
    }
}

void            add_client_end(t_database *data, t_client *new)
{
    t_client    *clients;

    clients = data->clients;
    while (clients && clients->next)
        clients = clients->next;
    clients->next = new;
}

void            add_client(t_database *data, t_client *new)
{
    t_client    *clients;

    clients = data->clients;
    if (!clients)
        data->clients = new;
    else
    {
        if (!(clients = find_client_mac(data, new->mac)))
            add_client_end(data, new);
        else
            update_client(new, clients);
    }
}

t_client        *new_client(t_database *data)
{
    t_client    *new;

    new = ft_memalloc(sizeof(t_client));
    new->mac = NULL;
    new->first = NULL;
    new->last = NULL;
    new->power = NULL;
    new->packets = NULL;
    new->bssid = NULL;
    new->probes = NULL;
    return (new);
}
