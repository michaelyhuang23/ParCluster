s=60
d=0.2
n=20


for((t=1; t<=3; t+=1)); do
    for r in {0.5,0.75,1.125,1.6875,2.53,3.80,5.70}; do
	echo ${r}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/PAMAP2.dat > results/PAMAP2$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/PAMAP2.dat > results/PAMAP2$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/PAMAP2.dat > results/PAMAP2$t/static_${n}_${r}_${s}.txt
    done

    for((s=1; s<=16; s*=2)); do
	echo ${s}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/PAMAP2.dat > results/PAMAP2$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/PAMAP2.dat > results/PAMAP2$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/PAMAP2.dat > results/PAMAP2$t/static_${n}_${r}_${s}.txt
    done
done

