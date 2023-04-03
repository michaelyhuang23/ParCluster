s=60
R=10000000
d=100
for((i=1000; i<=$R; i*=10)); do
    echo $i
    ./build/tests/seedspread_generator -s 0 -d 2 $i dataset/simden/${i}.txt
    ./build/tests/seedspread_generator -s 1 -d 2 $i dataset/varden/${i}.txt
    ./build/tests/uniform_generator -d 2 $i dataset/uniform/${i}.txt
done

for t in {1,2,3}; do
for r in {2,3,4.5,6.75,10.125,15.1875}; do
	echo ${r}
	for((i=1000; i<=$R; i*=10)); do
	    echo $i
	    echo $r
	    PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n 0 -d $d -i dataset/simden/${i}.txt > results/simden${t}/priority_${r}_${i}_${s}.txt
	    PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n 0 -d $d -i dataset/varden/${i}.txt > results/varden${t}/priority_${r}_${i}_${s}.txt
	    PARLAY_NUM_THREADS=${s} ./build/tests/dpc_priority -r $r -n 0 -d $d -i dataset/uniform/${i}.txt > results/uniform${t}/priority_${r}_${i}_${s}.txt
	    r=$(echo 3.16*$r | bc)
	done
done
done




