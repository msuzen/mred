set yrange [0:70]
delta=0.01
set xrange [6.5:7]
set xlabel "Simulation Time"
set ylabel "Number of Packets"
set title "Network 2"
plot "ratio.dat" u ($1*delta):3 title "RED traffic" w lp, "ratio.dat" u ($1*delta):2  title "RED drop","ratio.dat" u ($1*delta):6  title "mRED traffic" w lp,"ratio.dat" u ($1*delta):5 title  "mRED drops " w lp, 15 title "Maximum Threshold"
set terminal postscript color "Helvetica" 27  eps enhanced
set out "traffic_compare.eps"
replot
exit
