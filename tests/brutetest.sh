for((i = 1; ; ++i)); do
    echo $i
    ./ptr_gen $i > int
    ../build/tests/density_query int > int_dense
    # ./a < int > out1
    # ./brute < int > out2
    # diff -w out1 out2 || break
    diff -w <(../build/tests/static_dep_ptr int_dense) <(../build/tests/dep_ptr int_dense) || break
done
