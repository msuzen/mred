set xrange [6:7]
plot  "queues.ntw" u 1:3 title "RED queue size" w p,  "queues_master.ntw" u 1:3 title "mRED queue size" w p 
set title "Network 2"
set yrange [0:70]
set pointsize 2 
set xlabel "Simulation Time" 
set ylabel "Number of Packets" 
set terminal postscript color   "Helvetica" 27 eps enhanced
set out "actual_queue_size.eps"
replot
exit
