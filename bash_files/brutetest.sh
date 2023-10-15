for((i = 1; ; ++i)); do
    echo $i
    ./tests/ptr_gen $i > int
    ./build/tests/density_query int > int_dense

    diff -w <(./build/tests/static_dep_ptr_v1 int_dense) <(./build/tests/dep_ptr_brute int_dense) || break
done
