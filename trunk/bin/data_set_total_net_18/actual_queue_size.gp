set xrange [6:7]
plot  "queues.ntw" u 1:3 title "RED queue size" w p lw 4,  "queues_master.ntw" u 1:3 title "mRED queue size" w p lw 4
set title "Network 1"
set yrange [0:35]
set pointsize 3 
set xlabel "Simulation Time" 
set ylabel "Number of Packets" 
set terminal postscript color  "Helvetica" 27  eps enhanced
set out "actual_queue_size.eps"
replot
exit
