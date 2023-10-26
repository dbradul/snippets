//////////////////////////////////////////////////////////////////////////////////////////////////
// Generate files
//////////////////////////////////////////////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////////////////////////////////////////
// Remote compilation
//////////////////////////////////////////////////////////////////////////////////////////////////
#!/bin/bash
set -x
# copy to
rsync -arvzhe ssh /opt/projects/<prj> <name>@<remote_ip>:<remote_path>

# run
ssh <name>@<remote_ip> '<remote_path>/1.0-r0/temp/run.do_compile'

# copy from
sudo scp -i ~/.ssh/<key> <name>@<remote_ip>:<remote_path>  <local_path>

# start remotely
echo "starting..."
ssh root@<target_ip> '<target_path> -with -whatever -args'
ssh root@<target_ip> 'killall <bin>'

# We need to go deeper
watch -n 0.5 'docker exec -it kafka-postgres-1 su - postgres -c "psql -d scraper -c \"select sum(last_message_id) from producer_channel;\""'

#################################################################################################
# Unzip files is a folder
#!/usr/bin/env bash

# Folder with zip files
ZIP_FOLDER="/home/user/Downloads/"
DEST_FOLDER="/home/user/Downloads/unzipped/"

# Iterate over all zip files in the folder that ends with aaa.zip
for file in $ZIP_FOLDER/*.zip; do
    # Print unzipping progress
    echo "Unzipping $file..."

    # Unzip the file
    unzip -o "$file" -d "$DEST_FOLDER"

    # Print the name of the file that was unzipped
    echo "Finished $file"
done
