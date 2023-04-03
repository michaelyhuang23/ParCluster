s=60


for r in {0.05,0.1,0.2,0.4,0.8,1.6,3.2,6.4,12.8,25.6}; do
    echo ${r}
    PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/gowalla.pbbs -o out1 > results/densities/gowalla_density_$r.txt
done
