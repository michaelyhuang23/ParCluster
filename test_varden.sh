for((i=1000; i<=100000; i*=10)); do
    echo $i
    ./build/tests/seedspread_generator -s 1 -d 2 $i dataset/varden/${i}.txt
done


for((i=1000; i<=100000; i*=10)); do
    r=10
    echo $i
    ./build/tests/density_query -r $r -i dataset/varden/${i}.txt -o dataset/varden/${i}_dense.txt
    ./build/tests/dep_ptr_brute -i dataset/varden/${i}_dense.txt > results/varden/brute_${r}_${i}.txt
    ./build/tests/dep_ptr_dyn -i dataset/varden/${i}_dense.txt > results/varden/dyn_${r}_${i}.txt
    ./build/tests/dep_ptr_static -i dataset/varden/${i}_dense.txt > results/varden/static_${r}_${i}.txt
done

for((i=1000; i<=100000; i*=10)); do
    r=40
    echo $i
    ./build/tests/density_query -r $r -i dataset/varden/${i}.txt -o dataset/varden/${i}_dense.txt
    ./build/tests/dep_ptr_brute -i dataset/varden/${i}_dense.txt > results/varden/brute_${r}_${i}.txt
    ./build/tests/dep_ptr_dyn -i dataset/varden/${i}_dense.txt > results/varden/dyn_${r}_${i}.txt
    ./build/tests/dep_ptr_static -i dataset/varden/${i}_dense.txt > results/varden/static_${r}_${i}.txt
done

for((i=1000; i<=100000; i*=10)); do
    r=160
    echo $i
    ./build/tests/density_query -r $r -i dataset/varden/${i}.txt -o dataset/varden/${i}_dense.txt
    ./build/tests/dep_ptr_brute -i dataset/varden/${i}_dense.txt > results/varden/brute_${r}_${i}.txt
    ./build/tests/dep_ptr_dyn -i dataset/varden/${i}_dense.txt > results/varden/dyn_${r}_${i}.txt
    ./build/tests/dep_ptr_static -i dataset/varden/${i}_dense.txt > results/varden/static_${r}_${i}.txt
done
