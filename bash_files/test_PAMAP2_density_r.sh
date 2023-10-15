s=60


for r in {0.5,0.75,1.125,1.6875,2.53,3.80,5.70}; do
    echo ${r}
    PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/PAMAP2.dat -o out1 > results/densities/PAMAP2_density_$r.txt
done

