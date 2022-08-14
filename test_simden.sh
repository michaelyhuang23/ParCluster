R=100000

for((i=1000; i<=$R; i*=10)); do
    echo $i
    ./build/tests/seedspread_generator -s 0 -d 2 $i dataset/simden/${i}.txt
done

for((s=40; s<=60; s+=1)); do
	echo ${s}
	for((i=1000; i<=$R; i*=10)); do
		r=10
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/simden/${i}.txt -o dataset/simden/${i}_dense.txt > results/simden/density_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/simden/${i}_dense.txt > results/simden/brute_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/simden/${i}_dense.txt > results/simden/dyn_${r}_${i}_${s}.txt
<<<<<<< HEAD
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}_${s}.txt
=======
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/simden/${i}_dense.txt > results/simden/priority_${r}_${i}_${s}.txt
>>>>>>> 46e4a75c079e602e4448810bbe6517c52815972e
	done

	for((i=1000; i<=$R; i*=10)); do
		r=40
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/simden/${i}.txt -o dataset/simden/${i}_dense.txt > results/simden/density_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/simden/${i}_dense.txt > results/simden/brute_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/simden/${i}_dense.txt > results/simden/dyn_${r}_${i}_${s}.txt
<<<<<<< HEAD
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}_${s}.txt
=======
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/simden/${i}_dense.txt > results/simden/priority_${r}_${i}_${s}.txt
>>>>>>> 46e4a75c079e602e4448810bbe6517c52815972e
	done

	for((i=1000; i<=$R; i*=10)); do
		r=160
		echo $i
		PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/simden/${i}.txt -o dataset/simden/${i}_dense.txt > results/simden/density_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/simden/${i}_dense.txt > results/simden/brute_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/simden/${i}_dense.txt > results/simden/dyn_${r}_${i}_${s}.txt
<<<<<<< HEAD
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}_${s}.txt
#		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}_${s}.txt
=======
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}_${s}.txt
		PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/simden/${i}_dense.txt > results/simden/priority_${r}_${i}_${s}.txt
>>>>>>> 46e4a75c079e602e4448810bbe6517c52815972e
	done
done

