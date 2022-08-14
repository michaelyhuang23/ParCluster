	
r=5
PARLAY_NUM_THREADS=60 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_10M.pbbs -o dataset/reallife/3D_GeoLife_10M_dense > results/reallife/geolife/density_${r}_10000000_60.txt

PARLAY_NUM_THREADS=60 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_60.txt
PARLAY_NUM_THREADS=30 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_30.txt
PARLAY_NUM_THREADS=16 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_16.txt
PARLAY_NUM_THREADS=8 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_8.txt
PARLAY_NUM_THREADS=4 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_4.txt
PARLAY_NUM_THREADS=2 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_2.txt
PARLAY_NUM_THREADS=1 ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1M.pbbs -o dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/density_${r}_1000000_1.txt

for((s=1; s<=60; s+=1)); do
	echo ${s}
	
	PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_1K.pbbs -o dataset/reallife/3D_GeoLife_1K_dense > results/reallife/geolife/density_${r}_1000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/reallife/3D_GeoLife_1K_dense > results/reallife/geolife/brute_${r}_1000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/reallife/3D_GeoLife_1K_dense > results/reallife/geolife/dyn_${r}_1000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/reallife/3D_GeoLife_1K_dense > results/reallife/geolife/static_${r}_1000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/reallife/3D_GeoLife_1K_dense > results/reallife/geolife/par_${r}_1000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/reallife/3D_GeoLife_1K_dense > results/reallife/geolife/priority_${r}_1000_${s}.txt

	PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_10K.pbbs -o dataset/reallife/3D_GeoLife_10K_dense > results/reallife/geolife/density_${r}_10000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/reallife/3D_GeoLife_10K_dense > results/reallife/geolife/brute_${r}_10000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/reallife/3D_GeoLife_10K_dense > results/reallife/geolife/dyn_${r}_10000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/reallife/3D_GeoLife_10K_dense > results/reallife/geolife/static_${r}_10000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/reallife/3D_GeoLife_10K_dense > results/reallife/geolife/par_${r}_10000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/reallife/3D_GeoLife_10K_dense > results/reallife/geolife/priority_${r}_10000_${s}.txt

	PARLAY_NUM_THREADS=${s} ./build/tests/density_query -r $r -i dataset/reallife/3D_GeoLife_100K.pbbs -o dataset/reallife/3D_GeoLife_100K_dense > results/reallife/geolife/density_${r}_100000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/reallife/3D_GeoLife_100K_dense > results/reallife/geolife/brute_${r}_100000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/reallife/3D_GeoLife_100K_dense > results/reallife/geolife/dyn_${r}_100000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/reallife/3D_GeoLife_100K_dense > results/reallife/geolife/static_${r}_100000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/reallife/3D_GeoLife_100K_dense > results/reallife/geolife/par_${r}_100000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/reallife/3D_GeoLife_100K_dense > results/reallife/geolife/priority_${r}_100000_${s}.txt

	
	#PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/brute_${r}_1000000_${s}.txt
	#PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/dyn_${r}_1000000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/static_${r}_1000000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/par_${r}_1000000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/reallife/3D_GeoLife_1M_dense > results/reallife/geolife/priority_${r}_1000000_${s}.txt

		#PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_brute -i dataset/reallife/3D_GeoLife_10M_dense > results/reallife/geolife/brute_${r}_10000000_${s}.txt
	#PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_dyn -i dataset/reallife/3D_GeoLife_10M_dense > results/reallife/geolife/dyn_${r}_10000000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_static -i dataset/reallife/3D_GeoLife_10M_dense > results/reallife/geolife/static_${r}_10000000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_par -i dataset/reallife/3D_GeoLife_10M_dense > results/reallife/geolife/par_${r}_10000000_${s}.txt
	PARLAY_NUM_THREADS=${s} ./build/tests/dep_ptr_priority -i dataset/reallife/3D_GeoLife_10M_dense > results/reallife/geolife/priority_${r}_10000000_${s}.txt

done

