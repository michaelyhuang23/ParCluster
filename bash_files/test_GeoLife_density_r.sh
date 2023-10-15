s=60

for r in {0.01,0.02,0.04,0.08,0.16,0.32,0.64,1.28,2.56,5.12,10.24,20.48}; do
    echo ${r}
    PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_24M.pbbs -o out1 > results/densities/GeoLife_density_$r.txt
done

