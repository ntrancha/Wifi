/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 07:29:18 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/19 02:18:04 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "vendor.h"
#include "libft/includes/libft.h"

void    ft_putnchar(char *c, int n)
{
    while (n-- > 0)
        ft_putstr(c);
}

void    update_power(t_database *database)
{
    char    *date;
    char    *tmp;
    t_station   *station;
    t_client    *client;

    station = database->stations;
    client = database->clients;
    tmp = get_date(database);
    date = ft_strsub(tmp, 0, 11);
    while (station)
    {
        if (ft_strcchr(station->last, date) == 0)
            station->power = ft_strdup("-1000");
        station = station->next;
    }
    while (client)
    {
        if (ft_strcchr(client->last, date) == 0)
            client->power = ft_strdup("0");
        client = client->next;
    }
}

void    clean_database(t_database *database)
{
    clean_doublon_station_unknow(database);
    clean_hotspot(database);
    clean_doublon_client(database);
    update_power(database);
}

void    show_power(char *power);

void    show_client(t_database *data, t_client *client)
{
    char    *file;
    char    *tmp;

    ft_putstr("  ║ ");
    show_power(client->power);
    ft_putspace(3);
    if (client->mac)
        ft_putstr(client->mac);
    ft_putspace(3);
    ft_putstr(client->packets);
    ft_putspace(8 - ft_strlen(client->packets));
    if (client->mac)
    {
        file = vendor_get(data->vendors, client->mac);
        if (file && ft_strlen(file) > 2)
        {
            tmp = ft_strdup(file);
            ft_putspace(11);
            ft_putstr("\033[35m");
            ft_putstr(tmp);
            ft_putstr("\033[0m");
            ft_putspace(35 - ft_strlen(file));
            ft_strdelt(&tmp, &file);
        }
        else
            ft_putspace(47);
    }
    else
        ft_putspace(47);
    if (client->probes && ft_strlen(client->probes) > 2)
    {
        ft_putstr("    ");
        ft_putstr(client->probes);
        ft_putspace(105 - ft_strlen(client->probes));
    }
    else
        ft_putspace(109);
    ft_putendl("║");
}

void    show_clients(t_database *data, char *essid, char *bssid)
{
    t_client    *client;
    int         max;

    max = 10;
    client = data->clients;
    while (client && max)
    {
        if (ft_strcmp(client->bssid, bssid) == 0 && max--)
            show_client(data, client);
        else if (client->probes && ft_strcchr(client->probes, ",") == 0)
        {
            if (ft_strcmp(client->probes, essid) == 0 && max--)
                show_client(data, client);
        }
        else if (client->probes && ft_strcchr(client->probes, ",") == 1)
        {
            if (ft_strcchr(client->probes, essid) != 0 && max--)
                show_client(data, client);
        }
        client = client->next;
    }
}

int     have_clients(t_database *data, char *essid, char *bssid)
{
    t_client    *client;

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
    else if (po > 49 && po < 55)
        ft_putstr("\033[1;32m███████▓\033[0m");
    else if (po > 54 && po < 60)
        ft_putstr("\033[1;32m██████▓▒\033[0m");
    else if (po > 59 && po < 65)
        ft_putstr("\033[1;32m█████▓▒░\033[0m");
    else if (po > 64 && po < 70)
        ft_putstr("\033[1;32m████▓▒░░\033[0m");
    else if (po > 69 && po < 75)
        ft_putstr("\033[1;32m███▓▒░░░\033[0m");
    else if (po > 74 && po < 80)
        ft_putstr("\033[1;32m██▓▒░░░░\033[0m");
    else if (po > 79 && po < 85)
        ft_putstr("\033[1;32m█▓▒░░░░░\033[0m");
    else if (po > 84 && po < 90)
        ft_putstr("\033[1;32m▓▒░░░░░░\033[0m");
    else if (po > 89 && po < 101)
        ft_putstr("\033[1;33m░░░░░░░░\033[0m");
    else
        ft_putstr("\033[1;31m░░░░░░░░\033[0m");
}

void    show_station(t_database *data, t_station *station)
{
    char    *file;
    char    *tmp;

    ft_putstr("╔");
    ft_putnchar("═", 100 - (ft_strlen(station->essid) / 2));
    ft_putstr("╣ ");
    ft_putstr("\033[1;34m");
    ft_putstr(station->essid);
    ft_putstr("\033[0m");
    ft_putstr(" ╠");
    ft_putnchar("═", 100 - (ft_strlen(station->essid) / 2));
    if (ft_strlen(station->essid) % 2 == 0)
        ft_putstr("═");
    ft_putendl("╗");
    ft_putstr("║   ");
    show_power(station->power);
    ft_putstr(station->power);
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
    file = vendor_get(data->vendors, station->bssid);
    if (file)
    {
        tmp = ft_strdup(file);
        ft_putstr("   \033[35m");
        ft_putstr(tmp);
        ft_putstr("\033[0m");
        ft_putspace(146 - ft_strlen(file));
        ft_strdelt(&tmp, &file);
    }
    else
        ft_putspace(149);
    ft_putendl("\033[0m ║");
    if (have_clients(data, station->essid, station->bssid) == 0)
    {
        ft_putstr("╚");
        ft_putnchar("═", 205);
        ft_putendl("╝");
    }
    else
    {
        ft_putstr("╚═╦");
        ft_putnchar("═", 201);
        ft_putendl("╦═╝");
        show_clients(data, station->essid, station->bssid);
        ft_putstr("  ╚═");
        ft_putnchar("═", 199);
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

void    show_infos(t_database *data, char *search)
{
    t_station   *station;
    t_client    *client;

    station = data->stations;
    while (station)
    {
        if (!search)
            show_station(data, station);
        else
        {
            if (ft_strcchr(station->essid, search) != 0)
                show_station(data, station);
            if (ft_strlen(search) > 7 && ft_strcchr(station->bssid, search) != 0)
                show_station(data, station);
            if (ft_strcchr(station->auth, search) != 0)
                show_station(data, station);
        }
        station = station->next;
    }
    client = data->clients;
    while (client)
    {
        if (search)
            if (ft_strlen(search) > 7 && ft_strcchr(client->mac, search) != 0)
                show_infos(data, client->bssid);
        client = client->next;
    }
}

void    show_last(t_database *data, char *search)
{
    t_station   *station;
    t_client    *client;
    char        *tmp;
    char        *date;

    tmp = get_date(data);
    sort_station_power(data, -1);
    sort_client_power(data, -1);
    station = data->stations;
    date = ft_strsub(tmp, 0, 11);
    while (station)
    {
        if (ft_strcchr(station->last, date) != 0)
        {
            if (ft_strcchr(station->essid, search) != 0)
                show_station(data, station);
            if (ft_strlen(search) > 7 && ft_strcchr(station->bssid, search) != 0)
                show_station(data, station);
            if (ft_strcchr(station->auth, search) != 0)
                show_station(data, station);
        }
        station = station->next;
    }
    client = data->clients;
    while (client)
    {
        if (ft_strcchr(client->last, date) != 0)
            if (ft_strlen(search) > 7 && ft_strcchr(client->mac, search) != 0)
                show_infos(data, client->bssid);
        client = client->next;
    }

}

int     main(void)
{
    t_database  *database;

    database = parse_wifi("cap");
    clean_database(database);
    //sort_station_power(database, 1);
    //show_database(database);
    sort_station_power(database, 1);
    sort_client_power(database, -1);
    show_infos(database, NULL);
    /*show_infos(database, "NK");*/
    /*show_last(database, "WPA");*/
    /*display_data(database);*/
    /*ft_putendl(get_date(database));*/
    delete_database(database);
    return (0);
}
