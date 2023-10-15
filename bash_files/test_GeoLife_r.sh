s=60
d=10
n=1000


for((t=1; t<=3; t+=1)); do
    for r in {0.01,0.02,0.04,0.08,0.16,0.32,0.64,1.28,2.56,5.12,10.24,20.48}; do
	echo ${r}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/static_${n}_${r}_${s}.txt
    done
done

