d=2
n=5
s=60


for((t=1; t<=3; t+=1)); do
    for r in {0.003,0.006,0.012,0.024,0.048,0.096,0.192,0.384,0.768}; do
	echo ${r}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/sensor5.dat > results/sensor5$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/sensor5.dat > results/sensor5$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/sensor5.dat > results/sensor5$t/static_${n}_${r}_${s}.txt
    done
done

