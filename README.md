

### Additional file
functionslist.h is also provided : This file contains a function pointer array which will place each function implemented in the file functions.c at the index specified in the file functions.h 

#### How to run 
- Place the directory CFlask in libhttp-1.8/examples directory

open terminal in the CFlask directory and run the following commands

```
make
```

```
./flask <PORT_NUM> <NUM_THREADS>
```

To test the urls examples are given :

0. `/`
    - e.g usage :  http://127.0.0.1:8080/
 
1. `/square` 
    - e.g usage : http://127.0.0.1:8080/square?num=3

2. `/cube`
    - e.g usage : http://127.0.0.1:8080/cube?num=3

3. `/helloworld` 
`/square` 
    - e.g usage : http://127.0.0.1:8080/helloworld?str=DECS

4. `/pingpong`
    - e.g usage : http://127.0.0.1:8080/pingpong?str=cs744

5. `/arithmetic/prime`
    - e.g usage : http://127.0.0.1:8080/arithmetic/prime?num=3

6. `/arithmetic/fibonacci`
    - e.g usage : http://127.0.0.1:8080/arithmetic/fibonacci?num=3


#### How to run

- firstly make and run the flask server
```
make
```
```
./flask <PORT_NUM> <THREAD_NUM>
```
- then run the load.sh
```
chmod +x load.sh
chmod +x loadtest.sh 
```
```
./load.sh 127.0.0.1 <PORT_NUM> <NUM_THREADS> 
```
loadtest.sh is taken from part 4a and modified

The <NUM_THREADS> in ./load.sh command should be same as <THREAD_NUM> in ./flask command
- do the step one and then step two for threads = 1,2,4
- ```./flask 8080 1``` then ```./load.sh 127.0.0.1 8080 1```
- ```./flask 8080 2``` then ```./load.sh 127.0.0.1 8080 2```
- ```./flask 8080 4``` then ```./load.sh 127.0.0.1 8080 4```

- After running the above commands .txt files will be formed in the current directory.
    - e.g. results_route6_thread2.txt -- this specifies the results for route no. 6 with server currently running on 2 threads.

- After all three thread nums (1 2 4), in the terminal type the following command to generate plots

```
sudo apt install gnuplot
``` 
```
gnuplot -c plots.gp
```
Plots will be formed as:
- route4.png, route5.png and route6.png

In my testing the server was run 1, 2 and 4 threads and results were recorded and the plots were made for routes 4, 5 and 6 i.e. `/pingpong`, `/arithmetic/prime` and `/arithmetic/fibonacci` respectively.

##  load test of the server+function(s).

## Experiment no. 1 

### Aim : To determine the server throughput for the route `http://127.0.0.1:8080/pingpong?str=DECS` as the number of concurrent client increases, and with increasing number of threads for the server to service the requests

### Setup and execution details
    - server was run on 2 cores
    
    - 3.2 GHz processor
    
    - the number of threads for the server to service requests was kept 1. The server was tested by varying the number of concurrent requests as (1 4 8 12 16 20 24 28 36 40), while keeping the number of clients 100000.
    
    - The above procedure was repeated with number of threads = 2, and then 4.
    
    - The client sending requests were ran on the remaining 14 cores. 
    
    - Throughput : Requests/sec

### Hypothesis/expectation
    - The server does not have to do any compute, it just has to return a string. So the bottleneck expected is the number of concurrent requests it gets. As the number of concurrent requests increase the throughput should increase and then stabilize, because it can only service 'x' number of requests per sec.
    
    - As we increase the number of threads the throughput should increase, because we have 2 cores so we should utilize multithreading to increase throughput.

### Observations 
![plot](plots/loadtest1.jpg)

    - The throughput increased with increasing concurrent requests and then stabilized, i.e. it did not increase for last few concurrent requests.

    - The throughput increased with increasing threads.

    - For low number of concurrent requests the throughput was ver similar, but as the number of concurrent clients increased, throughput increased.

### Explaination
    - The throughput shot up when the concurrent requests were increased from 1 to further because the server had to reply with just a message, so the throughput depended on the rate at which requests were coming in.
    
    - From 8 concurrent requests onwards the throughput did not move much for threadpool size = 1, as now it seems the server can process these many concurent requests. For threadpool size=2 and 4, this behaviour was similar except the number of concurrent requests at which they stabilized was around 16.
    
    - The server is run on two cores so there is not much difference between threadpool size = 2, and 4, again the server just has to reply with a string.

## Experiment no. 2 

### Aim : To determine the server throughput for the route `/arithematic/prime?num=100003` as the number of concurrent client increases, and with increasing number of threads for the server to service the requests

### Setup and execution details
    - server was run on 2 cores
    
    - 3.2 GHz processor
    
    - the number of threads for the server to service requests was kept 1. The server was tested by varying the number of concurrent requests as (1 4 8 12 16 20 24 28 36 40), while keeping the number of clients 100000.
    
    - The above procedure was repeated with number of threads = 2, and then 4.
    
    - The client sending requests were ran on the remaining 14 cores. 
    
    - Throughput : Requests/sec

### Hypothesis/expectation
    - The server has to do some compute, it has to check that the given number(100003) is prime or not, it has to iterate from 2 to 100003, because the given number is prime, so that the server remains busy for some time. So the bottleneck expected is the server's compute power. As the number of concurrent requests increase the throughput should not increase much , becauase now the requests will seem to come in relatively faster as it has to do significant compute. The number of requests the server can service is limited by its compute power, so the throughput should not shoot up much as we increase number of concurrent requests and stabilize faster.
    
    - As we increase the number of threads the throughput should increase, because now more number of threads can parallely compute. So theoretically the throughput should double as we increase number of threads from 1 to 2, and then from 2 to 4.
    
    - The throughput should seem to stabilize after a certain number of concurrent requests.

### Observations
![plot](./plots/loadtest2.jpg)
    
    - The throughput increased slightly with increasing number of concurrent requests. 
    
    - The throughput increased with increasing threads.
    
    - The increase in throughput with number of concurrent requests 1 to 4 was higher as compared to the increase further.
    
    - For number of concurrent requests = 1 the throughput was very similar for all the threadpools, but as the number of concurrent clients increased, throughput increased with increasing threadpool size. For individual threadpools, it did not increase much with increasing number of concurrent requests and stabilized early.
    
    - There were slight ups and downs.

### Explaination
    - The throughput increase with increasing number of threads was significant. It almost doubled by doubling threadpool size from 1 to 2(what we expected), but there was a slight increase when increasing threadpool size from 2 to 4, because the number of cores is only 2, so increasing number of threads beyond 2 would not increase the throughput much, infact it would start decrease if we increase the number of threads further because most of time would be spent context switching.

    - From 4 concurrent requests onwards the throughput did not move much for all the threadpool sizes, because the compute capacity of the server peaked here.

    - The slight ups and downs could be attributed to scheduling as there were background processes also being run on these cores.


## Experiment no. 3 

### Aim : To determine the server throughput for the route `/arithematic/fibonacci?num=100000` as the number of concurrent client increases, and with increasing number of threads for the server to service the requests

### Setup and execution details
    - server was run on 2 cores
    
    - 3.2 GHz processor
    
    - the number of threads for the server to service requests was kept 1. 
    The server was tested by varying the number of concurrent requests as (1 4 8 12 16 20 24 28 36 40), while keeping the number of clients 100000.
    
    - The above procedure was repeated with number of threads = 2, and then 4.
    
    - The client sending requests were ran on the remaining 14 cores. 
    
    - Throughput : Requests/sec

### Hypothesis/expectation
    - The server has to do some compute, it has to compute the 100000th fibonacci number, it has to iterate from 1 to 100000. So the bottleneck expected is the server's compute power. As the number of concurrent requests increase the throughput should not increase much , becauase now the requests will seem to come in relatively faster as it has to do significant compute. The number of requests the server can service is limited by its compute power, so the throughput should not shoot up much as we increase number of concurrent requests and stabilize faster.
    
    - As we increase the number of threads the throughput should increase, because now more number of threads can parallely compute. So theoretically the throughput should double as we increase number of threads from 1 to 2, and then from 2 to 4.
    
    - The throughput should seem to stabilize after a certain number of concurrent requests.

### Observations
![plot](./plots/loadtest3.jpg)
   
    - The throughput increased slightly with increasing number of concurrent requests.
    
    - The throughput increased with increasing threads.
    
    - The increase in throughput with number of concurrent requests 1 to 4 was higher as compared to the increase further.
    
    - For number of concurrent requests = 1 the throughput was very similar for all the threadpools, but as the number of concurrent clients increased, throughput increased with increasing threadpool size. For individual threadpools, it did not increase much with increasing number of concurrent requests and stabilized early.
    
    - The throughput almost doubled from threadpool size = 1 to 2, and there was significant increase in throughput from threadpool size = 2 to 4.
    
    - There were slight ups and downs.

### Explaination
    - The throughput increase with increasing number of threads can attributed to the fact that now more number of threads are doing compute parallely, so requests will be served faster.

    - Ideally when the number of threads is kept upto 2 times the number of cores performance is good, which can be observed here.Number of cores = 2, number of threads = 1,2,4. 
    
    - When only 1 thread is there the server is underutilized, but with increasing threads performance increased.
    
    - From 4 concurrent requests onwards the throughput did not move much for all the threadpool sizes, because the compute capacity of the server peaked here.

    - The slight ups and downs could be attributed to scheduling as there were background processes also being run on these cores.
