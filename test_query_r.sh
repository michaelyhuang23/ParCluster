s=60
d=0.05
n=0


for((t=1; t<=3; t+=1)); do
    for r in {0.008,0.012,0.018,0.027,0.0405,0.081}; do
	echo ${r}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/query.pbbs > results/query_local$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/query.pbbs > results/query_local$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/query.pbbs > results/query_local$t/static_${n}_${r}_${s}.txt
    done
done

