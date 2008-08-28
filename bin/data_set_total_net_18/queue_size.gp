set xrange [6:7]
# plot "queues.ntw" u 1:2 title "average Queue" w l,  "queues.ntw" u 1:3 title "queue size" w l,"queues_master.ntw" u 1:2 title "Master: average Queue" w l,  "queues_master.ntw" u 1:3 title "Master: queue size" w l
plot "queues.ntw" u 1:2 title "RED average Queue" w p,  "queues_master.ntw" u 1:2 title "mRED average Queue" w p  
set pointsize 3
set title "Network 1"
set yrange [0:35]
set xlabel "Simulation Time"
set ylabel "Number of Packets"
set terminal postscript color "Helvetica" 27 eps enhanced
set out "queue_size.eps"
replot
exit
