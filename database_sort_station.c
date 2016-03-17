/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database_sort_station.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:49:21 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 20:49:43 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft/includes/libft.h"

void            change_station(t_database *base, t_station *one, t_station *two)
{
    t_station   *tmp_two;
    
    tmp_two = two->next;
    base->stations = two;
    two->next = one;
    one->next = tmp_two;
}

void            exchange_station(t_station *prev, t_station *one, t_station *two)
{
    t_station   *tmp_two;
    
    tmp_two = two->next;
    prev->next = two;
    two->next = one;
    one->next = tmp_two;
}

void            reverse_station(t_database *base, t_station *one, t_station *two)
{
    t_station   *parcours;
    t_station   *prev;

    parcours = base->stations;
    prev = NULL;
    while (parcours && parcours->next)
    {
        if (parcours == one && parcours->next == two)
        {
            if (!prev)
                change_station(base, one, two);
            else
                exchange_station(prev, one, two);
        }
        prev = parcours;
        parcours = parcours->next;
    }
}

void            sort_station_essid(t_database *database, int sort)
{
    t_station   *station;
    t_station   *tmp;
    int         test;

    station = database->stations;
    test = 0;
    while (station && station->next)
    {
        if (station->essid && station->next->essid)
        {
            if (sort == 1 && ft_strcmp(station->essid, station->next->essid) < 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
            if (sort == -1 && ft_strcmp(station->essid, station->next->essid) > 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
        }
        station = station->next;
    }
    if (test)
        sort_station_essid(database, sort);
}

void            sort_station_last(t_database *database, int sort)
{
    t_station   *station;
    t_station   *tmp;
    int         test;

    station = database->stations;
    test = 0;
    while (station && station->next)
    {
        if (station->last && station->next->last)
        {
            if (sort == 1 && ft_strcmp(station->last, station->next->last) < 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
            if (sort == -1 && ft_strcmp(station->last, station->next->last) > 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
        }
        station = station->next;
    }
    if (test)
        sort_station_last(database, sort);
}

void            sort_station_first(t_database *database, int sort)
{
    t_station   *station;
    t_station   *tmp;
    int         test;

    station = database->stations;
    test = 0;
    while (station && station->next)
    {
        if (station->first && station->next->first)
        {
            if (sort == 1 && ft_strcmp(station->first, station->next->first) < 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
            if (sort == -1 && ft_strcmp(station->first, station->next->first) > 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
        }
        station = station->next;
    }
    if (test)
        sort_station_first(database, sort);
}

void            sort_station_power(t_database *database, int sort)
{
    t_station   *station;
    t_station   *tmp;
    int         test;

    station = database->stations;
    test = 0;
    while (station && station->next)
    {
        if (station->power && station->next->power)
        {
            if (sort == 1 && ft_atoi(station->power) < ft_atoi(station->next->power))
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
            if (sort == -1 && ft_atoi(station->power) > ft_atoi(station->next->power))
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
        }
        station = station->next;
    }
    if (test)
        sort_station_power(database, sort);
}

void            sort_station_bssid(t_database *database, int sort)
{
    t_station   *station;
    t_station   *tmp;
    int         test;

    station = database->stations;
    test = 0;
    while (station && station->next)
    {
        if (station->bssid && station->next->bssid)
        {
            if (sort == 1 && ft_strcmp(station->bssid, station->next->bssid) < 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
            if (sort == -1 && ft_strcmp(station->bssid, station->next->bssid) > 0)
            {
                reverse_station(database, station, station->next);
                test = 1;
            }
        }
        station = station->next;
    }
    if (test)
        sort_station_bssid(database, sort);
}
