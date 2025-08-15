#!/bin/gnuplot

set title "Throughput vs Concurrent Requests"
set xlabel "Concurrent requests"
set ylabel "Throughput (Requests/sec)"

# threads=(1 2 4)
array routes[3]=[4,5,6]

do for [i=4:6]{
          plot "results_route".i."_thread1.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Threadpool size=1", \
               "results_route".i."_thread2.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Threadpool size=2", \
               "results_route".i."_thread4.txt" using 1:2 with linespoints lw 2 pt 7 ps 1.5 title "Threadpool size=4"
               set terminal png
               set output "route".i.".png"
               replot
               set output
}