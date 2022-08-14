import pandas as pd
import os

# process random datasets

ds = {'data':[], 'name':[], 'range':[], 'n': [], 'thread': [], 'time': [], 'dim': []}

def read_dir(ds, folder_path, dim):
	for file_name in os.listdir(folder_path):
		alg_name = file_name.split('_')[0]
		
		if alg_name=='dyn': continue
		if len(file_name.split('_'))!=4: continue
		with open(os.path.join(folder_path, file_name)) as f:
			if alg_name == 'density':
				s = '\n'.join(f.readlines())
				time = float(s.split('density time: ')[-1])
			else:
				s = f.readlines()
				time1 = float(s[0].split(': ')[-1])
				if len(s)>1:
					time2 = float(s[1].split(': ')[-1])
				else:
					print(file_name, s)
					time2 = 0 # this is temporary
				time = time1+time2
		r = int(file_name.split('_')[1])
		n = int(file_name.split('_')[2])
		thread = int(file_name.split('.')[0].split('_')[-1])
		#print(f'{alg_name}: {r}, {n}, {thread}, {time}')
		ds['data'].append(folder_path.split('/')[-1])
		ds['name'].append(alg_name)
		ds['range'].append(r)
		ds['n'].append(n)
		ds['thread'].append(thread)
		ds['time'].append(time)
		ds['dim'].append(dim)

for dataset_name in os.listdir('results/'):
	if 'simden' not in dataset_name and 'uniform' not in dataset_name and 'varden' not in dataset_name:
		continue
	print(f'reading: {dataset_name}')
	read_dir(ds, os.path.join('results',dataset_name),2)


read_dir(ds, os.path.join('results','reallife','geolife'), 3)


df = pd.DataFrame(data=ds)

df.to_csv('data.csv')
