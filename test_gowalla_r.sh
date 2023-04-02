# r=0.03
d=40
n=0
s=60


for((t=1; t<=3; t+=1)); do
    for r in {0.05,0.1,0.2,0.4,0.8,1.6,3.2,6.4,12.8,25.6}; do
	echo ${r}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/gowalla.pbbs > results/gowalla$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/gowalla.pbbs > results/gowalla$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/gowalla.pbbs > results/gowalla$t/static_${n}_${r}_${s}.txt
    done
done
