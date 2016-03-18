#!/bin/sh

if [ -z $1 ]
then
    echo "Arguement manquant";
    echo "./Mac_vendor.sh XX:XX:XX"
    exit
fi

wget http://macaddress.webwat.ch/hwaddr/$1 -O result 2> /dev/null
cat result|grep "vendor name:"|cut -d ">" -f3|cut -d "<" -f1
rm result
