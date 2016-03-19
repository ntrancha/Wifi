/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vendor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 23:03:59 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/18 23:56:41 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VENDOR_H
# define VENDOR_H

typedef struct  s_vendors   t_vendors;
typedef struct  s_vendor    t_vendor;

struct          s_vendor
{
    char        *mac;
    char        *vendor;
    t_vendor    *next;
};

struct          s_vendors
{
    t_vendor    *mac_0;
    t_vendor    *mac_1;
    t_vendor    *mac_2;
    t_vendor    *mac_3;
    t_vendor    *mac_4;
    t_vendor    *mac_5;
    t_vendor    *mac_6;
    t_vendor    *mac_7;
    t_vendor    *mac_8;
    t_vendor    *mac_9;
    t_vendor    *mac_A;
    t_vendor    *mac_B;
    t_vendor    *mac_C;
    t_vendor    *mac_D;
    t_vendor    *mac_E;
    t_vendor    *mac_F;
};

t_vendors       *data_vendor(void);
t_vendors       *data_vendor_init(void);
t_vendor        *vendor_new(t_vendors *vendors, char *mac, char *vendor);
t_vendor        *vendor_add(t_vendors *vendors, t_vendor *vendor);
void            add_vendor(t_vendor *vendors, t_vendor *new);
void            vendor_free(t_vendor *vendor);
void            vendors_free(t_vendors **vendors);
char            *vendor_get(t_vendors *vendors, char *mac);

#endif
