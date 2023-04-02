# r=0.5
d=10
n=30
s=60


for((t=1; t<=3; t+=1)); do
    for r in {0.3,0.6,1.2,2.4,4.8}; do
	echo ${r}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/HT.pbbs > results/HT$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/HT.pbbs > results/HT$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/HT.pbbs > results/HT$t/static_${n}_${r}_${s}.txt
    done
done

