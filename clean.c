/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 02:57:40 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 03:02:46 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft/includes/libft.h"

void    inverse_client(t_database *data, t_client *one, t_client *two, t_client *prev)
{
    one->last = two->last;
    if (two->next == one)
    {
        if (!prev)
            data->clients = one;
        else
            prev->next = one;
    }
    else
        one->next = two->next;
}

void    clean_doublon_client(t_database *database)
{
    t_client   *station;
    t_client   *prev;

    sort_client_mac(database, 1);
    station = database->clients;
    prev = NULL;
    while (station && station->next)
    {
        if (ft_strcmp(station->mac, station->next->mac) == 0)
        {
            if (ft_strcmp(station->first, station->next->first) < 0)
                inverse_client(database, station, station->next, prev);
            else
                inverse_client(database, station->next, station, prev);
        }
        prev = station;
        station = station->next;
    }
}

void    inverse_station(t_database *data, t_station *one, t_station *two, t_station *prev)
{
    one->last = two->last;
    if (two->next == one)
    {
        if (!prev)
            data->stations = one;
        else
            prev->next = one;
    }
    else
        one->next = two->next;
}

void    clean_doublon_station(t_database *database)
{
    t_station   *station;
    t_station   *prev;

    sort_station_bssid(database, 1);
    station = database->stations;
    prev = NULL;
    while (station && station->next)
    {
        if (ft_strcmp(station->bssid, station->next->bssid) == 0)
        {
            if (ft_strcmp(station->first, station->next->first) < 0)
                inverse_station(database, station, station->next, prev);
            else
                inverse_station(database, station->next, station, prev);
        }
        prev = station;
        station = station->next;
    }
}

int    del_station(t_database *database, t_station *del, t_station *prev)
{
    if (!prev)
        database->stations = del->next;
    else
        prev->next = del->next;
    return (1);
}

void    clean_doublon_station_unknow(t_database *database)
{
    t_station   *station;
    t_station   *prev;
    int         status;

    sort_station_essid(database, 1);
    station = database->stations;
    prev = NULL;
    status = 0;
    while (station && station->next)
    {
        if (ft_strcmp(station->essid, station->next->essid) == 0)
        {
            if (ft_strcmp(station->bssid, "xx:xx:xx:xx:xx:xx") == 0)
                if (ft_strcmp(station->next->bssid, "xx:xx:xx:xx:xx:xx") != 0)
                    status = del_station(database, station, prev);
            if (ft_strcmp(station->next->bssid, "xx:xx:xx:xx:xx:xx") == 0)
                if (ft_strcmp(station->bssid, "xx:xx:xx:xx:xx:xx") != 0)
                    status = del_station(database, station->next, prev);
            if (ft_strcmp(station->next->bssid, "xx:xx:xx:xx:xx:xx") == 0)
                if (ft_strcmp(station->bssid, "xx:xx:xx:xx:xx:xx") == 0)
                    status = del_station(database, station->next, prev);
        }
        prev = station;
        station = station->next;
    }
    if (status)
        clean_doublon_station_unknow(database);
}
 
void    clean_hotspot(t_database *database)
{
    t_station   *station;
    t_station   *prev;
    int         status;

    sort_station_bssid(database, 1);
    station = database->stations;
    prev = NULL;
    status = 0;
    while (station && station->next && !status)
    {
        if (ft_strcmp(station->bssid, "xx:xx:xx:xx:xx:xx") != 0)
            if (ft_strncmp(station->bssid, station->next->bssid, 15) == 0)
            {
                if (ft_strcmp(station->essid, "Freewifi") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->essid, "Freewifi_secure") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->essid, "FreeWifi") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->essid, "FreeWifi_secure") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->essid, "SFR WiFi Mobile") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->essid, "SFR WiFi FON") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->essid, "orange") == 0)
                    status = del_station(database, station, prev);
                else if (ft_strcmp(station->next->essid, "Freewifi") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "Freewifi_secure") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "FreeWifi") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "FreeWifi_secure") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "SFR WiFi Mobile") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "SFR WiFi FON") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "orange") == 0)
                    status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->next->essid, "???") == 0 && ft_strcmp(station->essid, "???") != 0)
                        status = del_station(database, station->next, prev);
                else if (ft_strcmp(station->essid, "???") == 0 && ft_strcmp(station->next->essid, "???") != 0)
                        status = del_station(database, station, prev);
            }
        prev = station;
        station = station->next;
    }
    if (status)
        clean_hotspot(database);
}
         
void    add_essid(t_database *data, char *bssid, char *essid)
{
    t_station   *station;

    station = data->stations;
    while (station)
    {
        if (ft_strcmp(station->bssid, bssid) == 0)
        {
            if (ft_strcmp(station->essid, "???") == 0)
                station->essid = essid;
        }
        station = station->next;
    }

}

void    show_essid(t_database *data)
{
    t_client   *client;

    client = data->clients;
    while (client)
    {
        if (client->probes && ft_strcchr(client->probes, ",") == 0 && ft_strcmp(client->bssid, "(not associated)") != 0)
            add_essid(data, client->bssid, client->probes);
        client = client->next;
    }
}

char    *get_date(t_database *data)
{
    t_station   *station;

    sort_station_last(data, 1);
    station = data->stations;
    while (station)
    {
        if (ft_strcmp(station->last, "XXXX-XX-XX XX:XX:XX") != 0)
            return (ft_strdup(station->last));
        station = station->next;
    }
}
