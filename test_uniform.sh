for((i=1000; i<=100000; i*=10)); do
    echo $i
    ./build/tests/uniform_generator -d 2 $i dataset/uniform/${i}.txt
done


for((i=1000; i<=100000; i*=10)); do
    r=5
    echo $i
    ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt
    ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}.txt
    ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}.txt
    ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}.txt
done

# for((i=1000; i<=100000; i*=10)); do
#     r=10
#     echo $i
#     ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt
#     ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}.txt
#     ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}.txt
#     ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}.txt
# done

# for((i=1000; i<=100000; i*=10)); do
#     r=20
#     echo $i
#     ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt
#     ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}.txt
#     ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}.txt
#     ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}.txt
# done

# for((i=1000; i<=100000; i*=10)); do
#     r=40
#     echo $i
#     ./build/tests/density_query -r $r -i dataset/uniform/${i}.txt -o dataset/uniform/${i}_dense.txt
#     ./build/tests/dep_ptr_brute -i dataset/uniform/${i}_dense.txt > results/uniform/brute_${r}_${i}.txt
#     ./build/tests/dep_ptr_dyn -i dataset/uniform/${i}_dense.txt > results/uniform/dyn_${r}_${i}.txt
#     ./build/tests/dep_ptr_static -i dataset/uniform/${i}_dense.txt > results/uniform/static_${r}_${i}.txt
# done
