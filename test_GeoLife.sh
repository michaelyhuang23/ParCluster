r=1
d=10
n=1000


for((t=1; t<=3; t+=1)); do
    for((s=30; s<=60; s*=2)); do
	echo ${s}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/static_${n}_${r}_${s}.txt
    done

    for((s=1; s<=16; s*=2)); do
	echo ${s}
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/priority_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/fenwick_${n}_${r}_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dpc_static -r $r -n $n -d $d -i dataset/reallife/3D_GeoLife_24M.pbbs > results/GeoLife$t/static_${n}_${r}_${s}.txt
    done
done

