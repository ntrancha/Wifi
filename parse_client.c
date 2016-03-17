/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:08:48 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 22:21:05 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"

static void     add_probe(char *probe, t_database *data)
{
    t_station   *station;

    station = new_station();
    station->bssid = ft_strdup("xx:xx:xx:xx:xx:xx");
    station->first = ft_strdup("XXXX-XX-XX XX:XX:XX");
    station->last = ft_strdup("XXXX-XX-XX XX:XX:XX");
    station->chan = ft_strdup("0");
    station->cipher = ft_strdup("0");
    station->auth = ft_strdup("XXX");
    station->power = ft_strdup("X");
    station->beacons = ft_strdup("X");
    station->iv = ft_strdup("X");
    station->ip = ft_strdup("X.X.X.X");
    station->id_len = ft_strdup("X");
    station->next = NULL;
    station->essid = ft_strdup(probe);
    add_station(data, station);
}

static void new_probe(char *line, t_database *data)
{
    char    **split;
    char    *probe;
    int     index;

    if (ft_strcchr(line, ",") != 0)
    {
        index = -1;
        split = ft_strsplit(line, ',');
        while (split[++index])
            new_probe(split[index], data);
        ft_tabstrdel(&split);
    }
    else
    {
        probe = ft_strdup(line);
        ft_strclearfront(&probe, ' ');
        ft_strclearfront(&probe, '\t');
        ft_strclearback(&probe, ' ');
        ft_strclearback(&probe, '\t');
        add_probe(probe, data);
        ft_strdel(&probe);
    }
}
void        parse_clients(char *line, t_database *data)
{
    char        **split;
    char        *bssid;
    char        *probes;
    t_client    *client;

    client = new_client();
    split = ft_strsplit(line, ',');
    if (split[0] && ft_strlen(split[0]) == 17)
    {
        client->mac = ft_strdup(split[0]);
        if (split[1] && ft_strlen(split[1]) == 20)
            client->first = ft_strcleanfront(split[1], ' ');
        if (split[2] && ft_strlen(split[2]) == 20)
            client->last = ft_strcleanfront(split[2], ' ');
        if (split[3])
            client->power = ft_strcleanfront(split[3], ' ');
        else
            client->power = NULL;
        if (split[4])
            client->packets = ft_strcleanfront(split[4], ' ');
        else
            client->packets = NULL;
        if (split[5])
        {
            bssid = ft_strcleanfront(split[5], ' ');
            client->bssid = ft_strcleanback(bssid, ' ');
            ft_strdel(&bssid);
        }
        else
            client->bssid = NULL;
        if (ft_strlen(line) > 95)
        {
            probes = ft_strsub(line, 93, ft_strlen(line) - 94);
            new_probe(probes, data);
            ft_strdel(&probes);
            probes = ft_strsub(line, 94, ft_strlen(line) - 95);
            client->probes = ft_strcleanfront(probes, ' ');
            ft_strdel(&probes);
        }
        else
            client->probes = NULL;
        add_client(data, client);
    }
    ft_tabstrdel(&split);
}
