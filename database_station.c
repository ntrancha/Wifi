/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database_station.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:29:30 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/19 02:18:05 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"

t_station        *find_station_essid(t_database *data, char *essid)
{
    t_station    *stations;

    stations = data->stations;
    while (stations)
    {
        if (ft_strcmp(stations->essid, essid) == 0)
            return (stations);
        stations = stations->next;
    }
    return (NULL);
}

t_station        *find_station_mac(t_database *data, char *bssid)
{
    t_station    *stations;

    stations = data->stations;
    while (stations)
    {
        if (ft_strcmp(stations->bssid, bssid) == 0)
            return (stations);
        stations = stations->next;
    }
    return (NULL);
}

void            add_station_end(t_database *data, t_station *new)
{
    t_station    *stations;

    stations = data->stations;
    while (stations && stations->next)
        stations = stations->next;
    stations->next = new;
}

void            update_station(t_station *new, t_station *old)
{
    char        *tmp;

    if (ft_strcmp(new->bssid, old->bssid) == 0 || ft_strcmp(new->essid, old->essid) == 0)
    {
        if (ft_strcmp(new->first, "XXXX-XX-XX XX:XX:XX") != 0 && ft_strcmp(new->first, old->first) < 0)
        {
            ft_strdel(&old->first);
            old->first = ft_strdup(new->first);
        }
        if (ft_strcmp(new->last, "XXXX-XX-XX XX:XX:XX") != 0 && ft_strcmp(new->last, old->last) > 0)
        {
            ft_strdel(&old->last);
            old->last = ft_strdup(new->last);
        }
        if (ft_strcmp(new->power, "X") != 0 && !old->power && new->power && ft_atoi(new->power) < ft_atoi(old->power))
        {
            ft_strdel(&old->power);
            old->power = ft_strdup(new->power);
        }
        if (!old->beacons || ft_strcmp(old->beacons, "???") == 0 || ft_strcmp(old->beacons, "") == 0)
            old->beacons = ft_strdup(new->beacons);
        else
        {
            tmp = ft_itoa(ft_atoi(new->beacons) + ft_atoi(old->beacons));
            ft_strdel(&new->beacons);
            old->beacons = tmp;
        }
        if (!old->iv || ft_strcmp(old->iv, "???") == 0 || ft_strcmp(old->iv, "") == 0)
            old->iv = ft_strdup(new->iv);
        else
        {
            tmp = ft_itoa(ft_atoi(new->iv) + ft_atoi(old->iv));
            ft_strdel(&new->iv);
            old->iv = tmp;
        }
        if ((ft_strcmp(new->chan, "0") != 0 && !(old->chan)) || (ft_strcmp(old->ip, "???") == 0 || ft_strcmp(old->ip, "") == 0))
        {
            ft_strdel(&old->chan);
            old->chan = ft_strdup(new->chan);
        }
        if ((ft_strcmp(new->cipher, "0") != 0 && !(old->cipher)) || (ft_strcmp(old->cipher, "???") == 0 || ft_strcmp(old->cipher, "") == 0))
        {
            ft_strdel(&old->cipher);
            old->cipher = ft_strdup(new->cipher);
        }
        if (!(old->essid) || ft_strcmp(old->essid, "???") == 0 || ft_strcmp(old->essid, "") == 0)
        {
            ft_strdel(&old->chan);
            old->chan = ft_strdup(new->chan);
        }
    }
}

void            add_station(t_database *data, t_station *new)
{
    t_station    *stations;

    stations = data->stations;
    if (!stations)
        data->stations = new;
    else
    {
        if (!(stations = find_station_mac(data, new->bssid)))
        {
            if (ft_strcchr(new->bssid, "xx:xx") != 0 && (stations = find_station_essid(data, new->essid)))
            {
                if (ft_strcchr(stations->essid, "???") != 0)
                    add_station_end(data, new);  
                else
                {
                    update_station(new, stations);  
                    delete_station(new);
                }
            }
            else 
                add_station_end(data, new);
        }
        else 
        {
            if (ft_strcmp(new->bssid, "xx:xx:xx:xx:xx:xx") == 0)
            {
                if ((stations = find_station_essid(data, new->essid)))
                {
                    update_station(new, stations);  
                    delete_station(new);
                }
                else
                    add_station_end(data, new);  
            }
            else
            {
                if (ft_strcmp(new->essid, "???") == 0 || ft_strcmp(new->essid, "XXX") == 0)
                {
                    update_station(new, stations);  
                    delete_station(new);
                }
                else
                {
                    if (ft_strcmp(new->essid, stations->essid) != 0)
                        add_station_end(data, new);  
                    else
                    {
                        update_station(new, stations);  
                        delete_station(new);
                    }
                }
            }
        }
    }
}

t_station       *new_station(void)
{
    t_station   *new;

    new = ft_memalloc(sizeof(t_station));
    if (!new)
        return (NULL);
    new->bssid = NULL;
    new->first = NULL;
    new->last = NULL;
    new->chan = NULL;
    new->cipher = NULL;
    new->auth = NULL;
    new->power = NULL;
    new->beacons = NULL;
    new->iv = NULL;
    new->ip = NULL;
    new->id_len = NULL;
    new->essid= NULL;
    new->key = NULL;
    new->next = NULL;
    return (new);
}
