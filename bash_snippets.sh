#!/bin/sh

#set -x

rm -rf /opt/test/*

COUNTER=1   
p=0123456789
until [  $COUNTER -lt 0 ]; do
    echo COUNTER $COUNTER
    dd if=/dev/zero of=/opt/test/${COUNTER}_${p}${p}${p}${p}${p}${p}${p}${p}${p}${p}${p}.dmp bs=1024  count=500
    #touch /opt/test/${COUNTER}_${p}${p}${p}${p}${p}${p}${p}${p}${p}${p}${p}.dmp
    let COUNTER-=1
done

count=`ls /opt/test/* 2> /dev/null | wc -l`
echo count $count



//////////////////////////////////////////////////////////////////////////////////////////////////
// one-liners
//////////////////////////////////////////////////////////////////////////////////////////////////

# monitor number of files
while true; do find /opt/test3 -iname "*" -type f | wc -l; sleep 2; done

