/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vendor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntrancha <ntrancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 22:38:00 by ntrancha          #+#    #+#             */
/*   Updated: 2016/03/19 01:52:10 by ntrancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "vendor.h"

t_vendors           *data_vendor_init(void)
{
    t_vendors       *vendors;

    vendors = ft_memalloc(sizeof(t_vendors));
    if (!vendors)
        return (NULL);
    vendors->mac_0 = NULL;
    vendors->mac_1 = NULL;
    vendors->mac_2 = NULL;
    vendors->mac_3 = NULL;
    vendors->mac_4 = NULL;
    vendors->mac_5 = NULL;
    vendors->mac_6 = NULL;
    vendors->mac_7 = NULL;
    vendors->mac_8 = NULL;
    vendors->mac_9 = NULL;
    vendors->mac_A = NULL;
    vendors->mac_B = NULL;
    vendors->mac_C = NULL;
    vendors->mac_D = NULL;
    vendors->mac_E = NULL;
    vendors->mac_F = NULL;
    return (vendors);
}

void                add_vendor(t_vendor *vendors, t_vendor *new)
{
    if (vendors && new)
    {
        while (vendors && vendors->next)
            vendors = vendors->next;
        vendors->next = new;
    }
}

t_vendor            *vendor_add(t_vendors *vendors, t_vendor *new)
{
    if ((new->mac)[0] == '0')
    {
        if (vendors->mac_0 == NULL)
            vendors->mac_0 = new;
        else
            add_vendor(vendors->mac_0, new);
    }
    if ((new->mac)[0] == '1')
    {
        if (vendors->mac_1 == NULL)
            vendors->mac_1 = new;
        else
            add_vendor(vendors->mac_1, new);
    }
    if ((new->mac)[0] == '2')
    {
        if (vendors->mac_2 == NULL)
            vendors->mac_2 = new;
        else
            add_vendor(vendors->mac_2, new);
    }
    if ((new->mac)[0] == '3')
    {
        if (vendors->mac_3 == NULL)
            vendors->mac_3 = new;
        else
            add_vendor(vendors->mac_3, new);
    }
    if ((new->mac)[0] == '4')
    {
        if (vendors->mac_4 == NULL)
            vendors->mac_4 = new;
        else
            add_vendor(vendors->mac_4, new);
    }
    if ((new->mac)[0] == '5')
    {
        if (vendors->mac_5 == NULL)
            vendors->mac_5 = new;
        else
            add_vendor(vendors->mac_5, new);
    }
    if ((new->mac)[0] == '6')
    {
        if (vendors->mac_6 == NULL)
            vendors->mac_6 = new;
        else
            add_vendor(vendors->mac_6, new);
    }
    if ((new->mac)[0] == '7')
    {
        if (vendors->mac_7 == NULL)
            vendors->mac_7 = new;
        else
            add_vendor(vendors->mac_7, new);
    }
    if ((new->mac)[0] == '8')
    {
        if (vendors->mac_8 == NULL)
            vendors->mac_8 = new;
        else
            add_vendor(vendors->mac_8, new);
    }
    if ((new->mac)[0] == '9')
    {
        if (vendors->mac_9 == NULL)
            vendors->mac_9 = new;
        else
            add_vendor(vendors->mac_9, new);
    }
    if ((new->mac)[0] == 'A')
    {
        if (vendors->mac_A == NULL)
            vendors->mac_A = new;
        else
            add_vendor(vendors->mac_A, new);
    }
    if ((new->mac)[0] == 'B')
    {
        if (vendors->mac_B == NULL)
            vendors->mac_B = new;
        else
            add_vendor(vendors->mac_B, new);
    }
    if ((new->mac)[0] == 'C')
    {
        if (vendors->mac_C == NULL)
            vendors->mac_C = new;
        else
            add_vendor(vendors->mac_C, new);
    }
    if ((new->mac)[0] == 'D')
    {
        if (vendors->mac_D == NULL)
            vendors->mac_D = new;
        else
            add_vendor(vendors->mac_D, new);
    }
    if ((new->mac)[0] == 'E')
    {
        if (vendors->mac_E == NULL)
            vendors->mac_E = new;
        else
            add_vendor(vendors->mac_E, new);
    }
    if ((new->mac)[0] == 'F')
    {
        if (vendors->mac_F == NULL)
            vendors->mac_F = new;
        else
            add_vendor(vendors->mac_F, new);
    }
    return (new);
}

t_vendor            *vendor_new(t_vendors *vendors, char *mac, char *vendor)
{
    t_vendor        *new;

    if (!mac || !vendor)
        return (NULL);
    new = ft_memalloc(sizeof(t_vendor));
    if (!new)
        return (NULL);
    new->mac = ft_strdup(mac);
    new->vendor = ft_strdup(vendor);
    new->next = NULL;
    return (vendor_add(vendors, new));
}

void                vendor_free(t_vendor *vendor)
{
    t_vendor        *next;

    if (vendor)
    {
        next = vendor->next;
        ft_strdel(&(vendor->mac));
        ft_strdel(&(vendor->vendor));
        ft_memdel((void**)&vendor);
        vendor_free(next);
    }
}

void                vendors_free(t_vendors **vendor)
{
    vendor_free(((*vendor)->mac_0));
    vendor_free(((*vendor)->mac_1));
    vendor_free(((*vendor)->mac_2));
    vendor_free(((*vendor)->mac_3));
    vendor_free(((*vendor)->mac_4));
    vendor_free(((*vendor)->mac_5));
    vendor_free(((*vendor)->mac_6));
    vendor_free(((*vendor)->mac_7));
    vendor_free(((*vendor)->mac_8));
    vendor_free(((*vendor)->mac_9));
    vendor_free(((*vendor)->mac_A));
    vendor_free(((*vendor)->mac_B));
    vendor_free(((*vendor)->mac_C));
    vendor_free(((*vendor)->mac_D));
    vendor_free(((*vendor)->mac_E));
    vendor_free(((*vendor)->mac_F));
    ft_memdel((void**)vendor);
}

char                *vendors_get(t_vendor *vendor, char *mac)
{
    int             len;
    char            *new;
    char            *new2;

    new = ft_strremplace(mac, "-", ":");
    ft_strreplace(&new, "-", ":", -1);
    new2 = ft_strremplace(mac, ":", "-");
    ft_strreplace(&new2, ":", "-", -1);
    while (vendor)
    {
        len = ft_strlen(vendor->mac) - 1;
        if (len >  10)
            len = 10;
        if (ft_strncmp(new, vendor->mac, len) == 0)
        {
            ft_strdelt(&new, &new2);
            return (ft_strdup(vendor->vendor));
        }
        if (ft_strncmp(new2, vendor->mac, len) == 0)
        {
            ft_strdelt(&new, &new2);
            return (ft_strdup(vendor->vendor));
        }
        vendor = vendor->next;
    }
    ft_strdelt(&new, &new2);
    return (NULL);
}

char                *vendor_get(t_vendors *vendors, char *mac)
{
    t_vendor        *list;

    list = NULL;
    if (mac[0] == '0')
        list = vendors->mac_0;
    if (mac[0] == '1')
        list = vendors->mac_1;
    if (mac[0] == '2')
        list = vendors->mac_2;
    if (mac[0] == '3')
        list = vendors->mac_3;
    if (mac[0] == '4')
        list = vendors->mac_4;
    if (mac[0] == '5')
        list = vendors->mac_5;
    if (mac[0] == '6')
        list = vendors->mac_6;
    if (mac[0] == '7')
        list = vendors->mac_7;
    if (mac[0] == '8')
        list = vendors->mac_8;
    if (mac[0] == '9')
        list = vendors->mac_9;
    if (mac[0] == 'A')
        list = vendors->mac_A;
    if (mac[0] == 'B')
        list = vendors->mac_B;
    if (mac[0] == 'C')
        list = vendors->mac_C;
    if (mac[0] == 'D')
        list = vendors->mac_D;
    if (mac[0] == 'E')
        list = vendors->mac_E;
    if (mac[0] == 'F')
        list = vendors->mac_F;
    return (vendors_get(list, mac));
}

t_vendors           *data_vendor(void)
{
    char            *file;
    char            **line;
    char            **decoupe;
    int             count;
    t_vendors       *vendors;

    count = -1;
    vendors = data_vendor_init();
    file = ft_get_file("Vendor/List_vendor");
    if (vendors && file && ft_strlen(file) > 100)
    {
        line = ft_strsplit(file,'\n');
        while (line[++count])
        {
            decoupe = ft_strsplit(line[count], ' ');
            if (decoupe)
                vendor_new(vendors, decoupe[0], decoupe[1]);
            ft_tabstrdel(&decoupe);
        }
        ft_tabstrdel(&line);
    }
    ft_strdel(&file);
    return (vendors);
}
