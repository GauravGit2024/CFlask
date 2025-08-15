#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <server_ip> <server_port> <thread_num>"
    exit 1
fi

# ./loadtest.sh $1 $2 $3 6
for(( i=0; i<7; i++)); do
    ./loadtest.sh $1 $2 $3 $i
done
