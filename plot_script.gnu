set datafile separator "	"
set xlabel "FID"
set ylabel "Freq"
set xrange [2:4]
set xtics 2,0.5,4
set yrange [0:100]
set ytics 0,20,100
set key outside

file = "aa.dat"
#set style fill solid
#set multiplot layout 2,1
#set title "First" pt dianxing lp xiananxing
plot file  every ::0::4  using 2:3  w lp lt 0 pt 1 title "core0-time1"
replot file every ::10::15  using 2:3 w lp lt 1 pt 2 title "core1-time1"
replot file every ::20::25  using 2:3 w lp lt 2 pt 3 title "core2-time1"
replot file every ::30::34  using 2:3 w lp lt 3 pt 4 title "core3-time1"
replot file every ::40::44  using 2:3 w lp lt 4 pt 5 title "core7-time1"

#set title "Second"
#replot file every ::5::9  using 2:3 w lp lt 0 pt 7 title "core0-time2"
#replot file every ::16::19  using 2:3 w lp lt 1 pt 8 title "core1-time2"
#replot file every ::26::29  using 2:3 w lp lt 2 pt 9 title "core2-time2"
#replot file every ::35::39  using 2:3 w lp lt 3 pt 10 title "core3-time2"
#replot file every ::45::49  using 2:3 w lp lt 4 pt 11 title "core7-time2"

#unset multiplot
#set ouput 'FID.png'

