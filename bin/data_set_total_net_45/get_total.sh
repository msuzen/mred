cat traffic.ntw | awk {'print $2+$3+$4+$5+$6+$7'} > total_traffic.dat
cat hostdrops.ntw | awk {'print $2+$3+$4+$5+$6+$7'} > total_drop.dat
cat traffic_master.ntw | awk {'print $2+$3+$4+$5+$6+$7'} > total_traffic_master.dat
cat hostdrops_master.ntw | awk {'print $2+$3+$4+$5+$6+$7'} > total_drop_master.dat
# generate total stats
perl throughput.pl > ratio.dat
# remove ps
rm -f *ps
# plot the shit
gnuplot actual_queue_size.gp
gnuplot queue_size.gp
gnuplot traffic_compare.gp
# remove png
rm -f *png
echo "converting actual_queue_size.ps"
convert -rotate 90 actual_queue_size.eps actual_queue_size_net_45.png
mv actual_queue_size.eps actual_queue_size_net_45.eps
echo "converting actual_size.ps"
convert -rotate 90  queue_size.eps queue_size_net_45.png
mv queue_size.eps queue_size_net_45.eps
echo "converting traffic_compare.ps"
convert -rotate 90 traffic_compare.eps traffic_compare_net_45.png
mv traffic_compare.eps traffic_compare_net_45.eps
