/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 21:50:43 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/17 20:47:50 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_client t_client;
typedef struct s_station t_station;

struct          s_client
{
    char        *mac;
    char        *first;
    char        *last;
    char        *power;
    char        *packets;
    char        *bssid;
    char        *probes;
    t_client    *next;
};

struct          s_station
{
    char        *bssid;
    char        *first;
    char        *last;
    char        *chan;
    char        *cipher;
    char        *auth;
    char        *power;
    char        *beacons;
    char        *iv;
    char        *ip;
    char        *id_len;
    char        *essid;
    char        *key;
    t_station   *next;
};

typedef struct  s_database
{
    t_station   *stations;
    t_client    *clients;
}               t_database;

////////////////////////////////////////////////////////////////
void            delete_database(t_database *data);
void            delete_stations(t_database *data);
void            delete_station(t_station *station);
void            delete_clients(t_database *data);
void            delete_client(t_client *client);
////////////////////////////////////////////////////////////////
t_database      *database_init(void);
t_client        *client_new(t_database *data);
t_station       *station_new(t_database *data);
////////////////////////////////////////////////////////////////
t_client        *new_client(t_database *data);
void            add_client(t_database *data, t_client *new);
////////////////////////////////////////////////////////////////
void            add_station(t_database *data, t_station *new);
t_station       *new_station(void);
////////////////////////////////////////////////////////////////
void            delete_database(t_database *data);
void            delete_stations(t_database *data);
void            delete_clients(t_database *data);
void            delete_station(t_station *station);
void            delete_client(t_client *client);
////////////////////////////////////////////////////////////////
int             point_csv(char *file);
void            get_csv(char *file, t_database *data);
void            parse_csv(char **file_content, t_database *data);
t_database      *parse_wifi(char *str);
////////////////////////////////////////////////////////////////
void            clean_string(char **str);
void            clean_data(t_database *data);
void            add_probes(char *probe, t_database *data);
void            new_probes(char *line, t_database *data);
void            parse_client(char *line, t_database *data);
void            parse_station(char *line, t_database *data);
void            display_data(t_database *data);
void            sort_station_bssid(t_database *database, int sort);
void            sort_station_essid(t_database *database, int sort);
void            sort_station_last(t_database *database, int sort);
void            sort_station_first(t_database *database, int sort);
void            sort_station_power(t_database *database, int sort);
void            sort_client_mac(t_database *database, int sort);
void            sort_client_first(t_database *database, int sort);
void            sort_client_last(t_database *database, int sort);
void            sort_client_power(t_database *database, int sort);
void            sort_client_bssid(t_database *database, int sort);

char            *get_date(t_database *data);
void            show_essid(t_database *data);
void            add_essid(t_database *data, char *bssid, char *essid);
void            clean_hotspot(t_database *database);
void            clean_doublon_station_unknow(t_database *database);
void            clean_doublon_station(t_database *database);
void            clean_doublon_client(t_database *database);
#endif
