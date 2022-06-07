R=10000000

for((i=1000; i<=$R; i*=10)); do
    echo $i
    ./build/tests/seedspread_generator -s 0 -d 2 $i dataset/simden/${i}.txt
done


for((i=1000; i<=$R; i*=10)); do
    r=10
    echo $i
    ./build/tests/density_query -r $r -i dataset/simden/${i}.txt -o dataset/simden/${i}_dense.txt
    ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}.txt
	./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}.txt
done

for((i=1000; i<=$R; i*=10)); do
    r=40
    echo $i
    ./build/tests/density_query -r $r -i dataset/simden/${i}.txt -o dataset/simden/${i}_dense.txt
    ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}.txt
	./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}.txt
done

for((i=1000; i<=$R; i*=10)); do
    r=160
    echo $i
    ./build/tests/density_query -r $r -i dataset/simden/${i}.txt -o dataset/simden/${i}_dense.txt
    ./build/tests/dep_ptr_static -i dataset/simden/${i}_dense.txt > results/simden/static_${r}_${i}.txt
	./build/tests/dep_ptr_par -i dataset/simden/${i}_dense.txt > results/simden/par_${r}_${i}.txt
done

