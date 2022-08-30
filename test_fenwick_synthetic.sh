R=10000000

for((i=1000; i<=$R; i*=10)); do
    echo $i
    ./build/tests/seedspread_generator -s 0 -d 2 $i dataset/simden/${i}.txt
	./build/tests/seedspread_generator -s 1 -d 2 $i dataset/varden/${i}.txt
	./build/tests/uniform_generator -d 2 $i dataset/uniform/${i}.txt
done

for((s=30; s<=60; s*=2)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=100
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/simden/${i}.txt > results/simden1/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/varden/${i}.txt > results/varden1/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/uniform/${i}.txt > results/uniform1/fenwick_${r}_${i}_${s}.txt
	done
done

for((s=1; s<=16; s*=2)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=100
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/simden/${i}.txt > results/simden1/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/varden/${i}.txt > results/varden1/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/uniform/${i}.txt > results/uniform1/fenwick_${r}_${i}_${s}.txt
	done
done





for((s=30; s<=60; s*=2)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=100
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/simden/${i}.txt > results/simden2/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/varden/${i}.txt > results/varden2/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/uniform/${i}.txt > results/uniform2/fenwick_${r}_${i}_${s}.txt
	done
done

for((s=1; s<=16; s*=2)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=100
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/simden/${i}.txt > results/simden2/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/varden/${i}.txt > results/varden2/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/uniform/${i}.txt > results/uniform2/fenwick_${r}_${i}_${s}.txt
	done
done




for((s=30; s<=60; s*=2)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=100
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/simden/${i}.txt > results/simden3/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/varden/${i}.txt > results/varden3/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/uniform/${i}.txt > results/uniform3/fenwick_${r}_${i}_${s}.txt
	done
done

for((s=1; s<=16; s*=2)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=100
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/simden/${i}.txt > results/simden3/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/varden/${i}.txt > results/varden3/fenwick_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dpc_fenwick -r $r -n 0 -d 20 -i dataset/uniform/${i}.txt > results/uniform3/fenwick_${r}_${i}_${s}.txt
	done
done
