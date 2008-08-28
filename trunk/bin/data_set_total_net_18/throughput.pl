#!/usr/bin/perl -w
# Read RED drops /traffic
$max_th=15;
@red_drops=read_line("total_drop.dat");
@red_traffic=read_line("total_traffic.dat");

@mred_drops=read_line("total_drop_master.dat");
@mred_traffic=read_line("total_traffic_master.dat");

print "#   max_th $max_th\n";
print "# time red_drops red_traffic red_ratio mred_drops mred_traffic  mred_ratio\n";
print "# \n";
print "# \n";

# compute relative utilization drops/traffic
  $total_red_drop=0;
  $total_mred_drop=0;
  $total_red_traffic=0;
  $total_mred_traffic=0;
 for($i=1;$i<$#red_drops;$i++) {
    #  print "i $i red $red_drops[$i] $red_traffic[$i] mred $mred_drops[$i] $mred_traffic[$i]\n";
   if($red_traffic[$i] > 0) { $red_ratio=abs($red_traffic[$i]-$red_drops[$i])/$red_traffic[$i]; }
   if($red_traffic[$i] < 1e-7) { $red_ratio=0;}
   if($mred_traffic[$i] > 0) { $mred_ratio=abs($mred_traffic[$i]-$mred_drops[$i])/$mred_traffic[$i]; }
   if($mred_traffic[$i] < 1e-7) { $mred_ratio=0;}
    print "$i  $red_drops[$i] $red_traffic[$i] $red_ratio $mred_drops[$i] $mred_traffic[$i] $mred_ratio\n";
    $total_red_drop=$red_drops[$i]+$total_red_drop;
    $total_mred_drop=$mred_drops[$i]+$total_mred_drop;
    $total_red_traffic=$total_red_traffic+$red_traffic[$i];
    $total_mred_traffic=$total_mred_traffic+$mred_traffic[$i];
 }
   $red_throughput=1.0-$total_red_drop/$total_red_traffic;
   $mred_throughput=1.0-$total_mred_drop/$total_mred_traffic;
    print "# \n";
    print "# \n";
    print "#   relative traffic utilization  = $red_throughput  \n";
    print "#   relative traffic utilization  = $mred_throughput \n";
    print "# \n";

sub read_line () {

 $file_name=$_[0];
open(FH,"< $file_name");
$i=0;
while(<FH>){
  chop($_);
  $line=$_;
  # print "file= $file_name line $_ \n";
  $data[$i]=$line; 
  $i++;
}

 return @data;
}
