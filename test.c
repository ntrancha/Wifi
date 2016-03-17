/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 07:29:18 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 04:37:45 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft/includes/libft.h"

void    ft_putnchar(char *c, int n)
{
    while (n-- > 0)
        ft_putstr(c);
}

void    clean_database(t_database *database)
{
    clean_doublon_station(database);
    clean_doublon_station_unknow(database);
    clean_doublon_client(database);
    clean_hotspot(database);
    show_essid(database);
    clean_hotspot(database);   
}

void    show_power(char *power);

void    show_client(t_client *client)
{
    ft_putstr("  ║ ");
    show_power(client->power);
    ft_putspace(3);
    if (client->mac)
        ft_putstr(client->mac);
    ft_putspace(3);
    ft_putstr(client->packets);
    ft_putspace(16 - ft_strlen(client->packets));
    ft_putendl("║");
}

void    show_clients(t_database *data, char *essid, char *bssid)
{
    t_client    *client;

    client = data->clients;
    while (client)
    {
        if (ft_strcmp(client->bssid, bssid) == 0)
            show_client(client);
        else if (client->probes && ft_strcchr(client->probes, ",") == 0)
        {
            if (ft_strcmp(client->probes, essid) == 0)
                show_client(client);
        }
        else if (client->probes && ft_strcchr(client->probes, ",") == 1)
        {
            if (ft_strcchr(client->probes, essid) != 0)
                show_client(client);
        }
        client = client->next;
    }
}

int     have_clients(t_database *data, char *essid, char *bssid)
{
    t_client    *client;
    int         ret;

    ret = 0;
    client = data->clients;
    while (client)
    {
        if (ft_strcmp(client->bssid, bssid) == 0)
            return (1);
        else if (client->probes && ft_strcchr(client->probes, ",") == 0)
        {
            if (ft_strcmp(client->probes, essid) == 0)
                return (1);
        }
        else if (client->probes && ft_strcchr(client->probes, ",") == 1)
        {
            if (ft_strcchr(client->probes, essid) != 0)
                return (1);
        }
        client = client->next;
    }
    return (0);
}



void    show_power(char *power)
{
    int po;

    po = ft_atoi(power) * -1;
    if (po > 9 && po < 50)
        ft_putstr("\033[1;32m████████\033[0m");
    if (po > 49 && po < 55)
        ft_putstr("\033[1;32m███████▓\033[0m");
    if (po > 54 && po < 60)
        ft_putstr("\033[1;32m██████▓▒\033[0m");
    if (po > 59 && po < 65)
        ft_putstr("\033[1;32m█████▓▒░\033[0m");
    if (po > 64 && po < 70)
        ft_putstr("\033[1;32m████▓▒░░\033[0m");
    if (po > 69 && po < 75)
        ft_putstr("\033[1;32m███▓▒░░░\033[0m");
    if (po > 74 && po < 80)
        ft_putstr("\033[1;32m██▓▒░░░░\033[0m");
    if (po > 79 && po < 85)
        ft_putstr("\033[1;32m█▓▒░░░░░\033[0m");
    if (po > 84 && po < 90)
        ft_putstr("\033[1;32m▓▒░░░░░░\033[0m");
    if (po < 10 && po > 0)
        ft_putstr("\033[1;33m░░░░░░░░\033[0m");
    if (po < 1)
        ft_putstr("\033[1;31m░░░░░░░░\033[0m");
}

void    show_station(t_database *data, t_station *station)
{
    ft_putstr("╔");
    ft_putnchar("═", 25 - (ft_strlen(station->essid) / 2));
    ft_putstr("╣ ");
    ft_putstr("\033[1;34m");
    ft_putstr(station->essid);
    ft_putstr("\033[0m");
    ft_putstr(" ╠");
    ft_putnchar("═", 25 - (ft_strlen(station->essid) / 2));
    if (ft_strlen(station->essid) % 2 == 0)
        ft_putstr("═");
    ft_putendl("╗");
    ft_putstr("║   ");
    show_power(station->power);
    ft_putstr("    \033[1;37m");
    ft_putstr(station->bssid);
    ft_putstr("\033[0m");
    ft_putstr("   ");
    if (ft_strcchr(station->auth, "WEP") == 1)
        ft_putstr("\033[32m");
    else if (ft_strcchr(station->auth, "OPN") == 1)
        ft_putstr("\033[33m");
    else if (ft_strcchr(station->auth, "WPA") != 0)
        ft_putstr("\033[33m");
    else
        ft_putstr("\033[30m");
    ft_putstr(station->auth);
    ft_putspace(7 - ft_strlen(station->auth));
    ft_putstr("\033[0m");
    ft_putstr("  chan:");
    ft_putspace(3 - ft_strlen(station->chan));
    ft_putstr(station->chan);
    ft_putendl("\033[0m ║");
    if (have_clients(data, station->essid, station->bssid) == 0)
    {
        ft_putstr("╚");
        ft_putnchar("═", 55);
        ft_putendl("╝");
    }
    else
    {
        ft_putstr("╚═╦");
        ft_putnchar("═", 51);
        ft_putendl("╦═╝");
        show_clients(data, station->essid, station->bssid);
        ft_putstr("  ╚═");
        ft_putnchar("═", 49);
        ft_putendl("═╝");
    }
    ft_putendl("");
}

void    show_database(t_database *database)
{
    t_station   *station;

    station = database->stations;
    while (station)
    {
        if (ft_strcmp(station->bssid, "xx:xx:xx:xx:xx:xx") != 0)
            if (ft_strcmp(station->power, "-1") != 0)
                show_station(database, station);
        station = station->next;
    }
    station = database->stations;
    while (station)
    {
        if (ft_strcmp(station->power, "-1") == 0)
            show_station(database, station);
        station = station->next;
    }
   
    station = database->stations;
    while (station)
    {
        if (ft_strcmp(station->bssid, "xx:xx:xx:xx:xx:xx") == 0)
            show_station(database, station);
        station = station->next;
    }
}

int     main(int argc, char **argv)
{
    t_database  *database;

    database = parse_wifi("cap");
    clean_database(database);
    ft_putendl(get_date(database));
    sort_client_power(database, 1);
    sort_station_power(database, 1);
    show_database(database);
    /*display_data(database);*/
    return (0);
}
