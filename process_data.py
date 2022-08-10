import pandas as pd
import os

# process random datasets

for dataset_name in os.listdir('results/'):
	if 'simden' not in dataset_name and 'uniform' not in dataset_name and 'varden' not in dataset_name:
		continue
	print(f'reading: {dataset_name}')
	for file_name in os.listdir(f'results/{dataset_name}'):
		alg_name = file_name.split('_')[0]
		


