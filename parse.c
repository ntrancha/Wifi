/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 21:48:20 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 20:13:58 by ntrancha         ###   ########.fr       */
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

void            clean_string(char **str)
{
    ft_strclearfront(str, ' ');
    ft_strclearfront(str, '\t');
    ft_strclearback(str, ' ');
    ft_strclearback(str , '\t');
}

void            clean_data(t_database *data)
{
    t_station   *station;
    t_client    *client;

    station = data->stations;
    while (station)
    {
        if (station->bssid)
            clean_string(&(station->bssid));
        if (station->first)
            clean_string(&(station->first));
        if (station->last)
            clean_string(&(station->last));
        if (station->chan)
            clean_string(&(station->chan));
        if (station->cipher)
            clean_string(&(station->cipher));
        if (station->auth)
            clean_string(&(station->auth));
        if (station->power)
            clean_string(&(station->power));
        if (station->beacons)
            clean_string(&(station->beacons));
        if (station->iv)
            clean_string(&(station->iv));
        if (station->ip)
            clean_string(&(station->ip));
        if (station->id_len)
            clean_string(&(station->id_len));
        if (station->essid)
            clean_string(&(station->essid));
    }
}

void        add_probes(char *probe, t_database *data)
{
    t_station   *station;

    station = station_new(data);
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
}

void        new_probes(char *line, t_database *data)
{
    char    **split;
    char    *probe;
    int     index;

    if (ft_strcchr(line, ",") != 0)
    {
        index = -1;
        split = ft_strsplit(line, ',');
        while (split[++index])
            new_probes(split[index], data);
        ft_tabstrdel(&split);
    }
    else
    {
        probe = ft_strdup(line);
        ft_strclearfront(&probe, ' ');
        ft_strclearfront(&probe, '\t');
        ft_strclearback(&probe, ' ');
        ft_strclearback(&probe, '\t');
        add_probes(probe, data);
        ft_strdel(&probe);
    }
}

void        parse_client(char *line, t_database *data)
{
    char        **split;
    char        *bssid;
    char        *probes;
    t_client    *client;

    client = client_new(data);
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
            new_probes(probes, data);
            ft_strdel(&probes);
            probes = ft_strsub(line, 94, ft_strlen(line) - 95);
            client->probes = ft_strcleanfront(probes, ' ');
            ft_strdel(&probes);
        }
        else
            client->probes = NULL;
    }
}


void            parse_station(char *line, t_database *data)
{
    char        **split;
    t_station   *station;

    station = station_new(data);
    split = ft_strsplit(line, ',');
    if (split[0] && ft_strlen(split[0]) == 17)      // BSSID
    {
        station->bssid = ft_strdup(split[0]);
        if (split[1] && ft_strlen(split[1]) == 20)       // First Time
            station->first = ft_strcleanfront(split[1], ' ');
        if (split[2] && ft_strlen(split[2]) == 20)       // Last Time
            station->last = ft_strcleanfront(split[2], ' ');
        if (split[3])                                    // Channel
            station->chan = ft_strcleanfront(split[3], ' ');
        else
            station->chan = ft_strdup("");
        if (split[4])                                    // Cipher
            station->cipher = ft_strcleanfront(split[4], ' ');
        else
            station->cipher = ft_strdup("");
        if (split[5])                                    // Auth
            station->auth = ft_strcleanfront(split[5], ' ');
        else
            station->auth = ft_strdup("XXX");
        if (split[6])                                    // Power
            station->power = ft_strcleanfront(split[8], ' ');
        else
            station->power = ft_strdup("");
        if (split[9])                                    // beacons
            station->beacons = ft_strcleanfront(split[9], ' ');
        else
            station->beacons = ft_strdup("");
        if (split[10])                                   // IV
            station->iv = ft_strcleanfront(split[10], ' ');
        else
            station->iv = ft_strdup("");
        if (split[11])                                   // IP
            station->ip = ft_strcleanfront(split[11], ' ');
        else
            station->ip = ft_strdup("");
        if (split[12])                                   // ID len
            station->id_len = ft_strcleanfront(split[12], ' ');
        else
            station->id_len = ft_strdup("");
        if (split[13] && ft_strlen(split[13]) > 1)       // ESSID
            station->essid = ft_strcleanfront(split[13], ' ');
        else
            station->essid = ft_strdup("???");
        if (split[14])                                   // KEY
            station->key = ft_strcleanfront(split[14], ' ');
        else
            station->key = ft_strdup("");
    }
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
    ft_strdel(&content);
}

void        display_data(t_database *data)
{
    t_station   *station;
    t_client    *client;

    station = data->stations;
    client = data->clients;
    while (station)
    {
        ft_putstr(station->essid);
        ft_putstr("|");
        ft_putstr(station->bssid);
        ft_putstr("|");
        ft_putstr(station->first);
        ft_putstr("|");
        ft_putstr(station->last);
        ft_putstr("|");
        ft_putstr(station->chan);
        ft_putstr("|");
        ft_putstr(station->cipher);
        ft_putstr("|");
        ft_putstr(station->auth);
        ft_putstr("|");
        ft_putstr(station->power);
        ft_putstr("|");
        ft_putstr(station->beacons);
        ft_putstr("|");
        ft_putstr(station->iv);
        ft_putstr("|");
        ft_putstr(station->ip);
        ft_putendl("");
        station = station->next;
    }
    while (client)
    {
        ft_putstr(client->mac);
        ft_putstr("|");
        ft_putstr(client->first);
        ft_putstr("|");
        ft_putstr(client->last);
        ft_putstr("|");
        ft_putstr(client->power);
        ft_putstr("|");
        ft_putstr(client->packets);
        ft_putstr("|");
        ft_putstr(client->bssid);
        ft_putstr("|");
        ft_putstr(client->probes);
        ft_putendl("");
        client = client->next;
    }
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
