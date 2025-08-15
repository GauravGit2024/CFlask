#!/bin/bash

if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <server_ip> <server_port> <thread_num> <route_index>"
    exit 1
fi

URLS=("/" "/square?num=100" "/cube?num=100" "/helloworld?str=cs744" "/pingpong?str=DECS" "/arithematic/prime?num=100003"  "/arithematic/fibonacci?num=100000")

SERVER_IP=$1
SERVER_PORT=$2
THREAD_NUM=$3
ROUTE=$4

touch results_route${ROUTE}_thread${THREAD_NUM}.txt

CONCURRENT_CLIENTS=(1 4 8 12 16 20 24 28 36 40)

for CLIENTS in ${CONCURRENT_CLIENTS[@]}; do
    echo -n "${CLIENTS}  " >> results_route${ROUTE}_thread${THREAD_NUM}.txt
    THROUGHPUT=$(ab -n 100000 -c $CLIENTS  $SERVER_IP:$SERVER_PORT${URLS[$ROUTE]} | grep -E 'Requests per second' | cut -d: -f 2 | cut -d "[" -f 1)
    wait
    echo "completed ${CLIENTS} CONC. Clients"
    echo "$THROUGHPUT" >> results_route${ROUTE}_thread${THREAD_NUM}.txt
done

# cat results_route${ROUTE}_thread${THREAD_NUM}.txt | graph -T png --bitmap-size "1400x1400" -g 3 -L "Thoughput vs Concurrent Requests" -X "Concurrent Requests" -r 0.1 -Y "Throughput" -r 0.25>./plot_$ROUTE.png
echo "All clients have finished."
