/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_station.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:59:04 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/19 02:10:57 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "parse.h"

void            parse_stations(char *line, t_database *data)
{
    char        **split;
    char        *tmp;
    t_station   *station;

    station = new_station();
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
        {
            tmp = ft_strcleanfront(split[8], ' ');
            if (ft_strcmp(tmp, "-1") == 0)
            {
                station->power = ft_strdup("-100");
                ft_strdel(&tmp);
            }
            else
                station->power = tmp;
        }
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
        add_station(data, station);
    }
    ft_tabstrdel(&split);
}
