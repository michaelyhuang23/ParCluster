R=100000

for((i=1000; i<=$R; i*=10)); do
    echo $i
    ./build/tests/uniform_generator -d 2 $i dataset/uniform/${i}.txt
done

for((s=40; s<=60; s+=1)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=10
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt > results/uniform/density_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}_${s}.txt
<<<<<<< HEAD
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/uniform/${i}_dense.txt > results/uniform/par_${r}_${i}_${s}.txt
=======
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/uniform/${i}_dense.txt > results/uniform/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/uniform/${i}_dense.txt > results/uniform/priority_${r}_${i}_${s}.txt
>>>>>>> 46e4a75c079e602e4448810bbe6517c52815972e
	done

	for((i=1000; i<=$R; i*=10)); do
		r=40
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt > results/uniform/density_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}_${s}.txt
<<<<<<< HEAD
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/uniform/${i}_dense.txt > results/uniform/par_${r}_${i}_${s}.txt
=======
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/uniform/${i}_dense.txt > results/uniform/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/uniform/${i}_dense.txt > results/uniform/priority_${r}_${i}_${s}.txt
>>>>>>> 46e4a75c079e602e4448810bbe6517c52815972e
	done

	for((i=1000; i<=$R; i*=10)); do
		r=160
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt > results/uniform/density_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}_${s}.txt
<<<<<<< HEAD
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/uniform/${i}_dense.txt > results/uniform/par_${r}_${i}_${s}.txt
=======
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/uniform/${i}_dense.txt > results/uniform/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/uniform/${i}_dense.txt > results/uniform/priority_${r}_${i}_${s}.txt
>>>>>>> 46e4a75c079e602e4448810bbe6517c52815972e
	done
done

