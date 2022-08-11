R=10000000

for((i=1000; i<=$R; i*=10)); do
    echo $i
    ./build/tests/seedspread_generator -s 1 -d 2 $i dataset/varden/${i}.txt
done


for((s=1; s<=60; s+=1)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=10
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/varden/${i}.txt -o dataset/varden/${i}_dense.txt > results/varden/density_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/varden/${i}_dense.txt > results/varden/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/varden/${i}_dense.txt > results/varden/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/varden/${i}_dense.txt > results/varden/priority_${r}_${i}_${s}.txt
	done

	for((i=1000; i<=$R; i*=10)); do
		r=40
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/varden/${i}.txt -o dataset/varden/${i}_dense.txt > results/varden/density_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/varden/${i}_dense.txt > results/varden/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/varden/${i}_dense.txt > results/varden/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/varden/${i}_dense.txt > results/varden/priority_${r}_${i}_${s}.txt
	done

	for((i=1000; i<=$R; i*=10)); do
		r=160
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/varden/${i}.txt -o dataset/varden/${i}_dense.txt > results/varden/density_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/varden/${i}_dense.txt > results/varden/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/varden/${i}_dense.txt > results/varden/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/varden/${i}_dense.txt > results/varden/priority_${r}_${i}_${s}.txt
	done
done
