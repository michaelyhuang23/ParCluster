s=60


for r in {0.008,0.012,0.018,0.027,0.0405,0.081}; do
    echo ${r}
    PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/query.pbbs -o out1 > results/densities/query_local_density_$r.txt
done

