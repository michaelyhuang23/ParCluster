import pandas as pd
import os

ds = {'data':[], 'name':[], 'range':[], 'n': [], 'thread': [], 'time': [], 'dim': []}

def read_dir(ds, folder_path, dim):
	for file_name in os.listdir(folder_path):
		alg_name = file_name.split('_')[0]
		if len(file_name.split('_'))!=4: continue
		print(file_name)
		with open(os.path.join(folder_path, file_name)) as f:
			s = '\n'.join(f.readlines())
			if s=='': continue
			time = float(s.split('query computation time: ')[-1].split('[sec]')[0])
		r = int(file_name.split('_')[1])
		n = int(file_name.split('_')[2])
		print(file_name)
		thread = int(file_name.split('.')[0].split('_')[-1])
		print(f'{alg_name}: {r}, {n}, {thread}, {time}')
		ds['data'].append(folder_path.split('/')[-1])
		ds['name'].append(alg_name)
		ds['range'].append(r)
		ds['n'].append(n)
		ds['thread'].append(thread)
		ds['time'].append(time)
		ds['dim'].append(dim)

read_dir(ds, '../DPC/linux/Ex-DPC/results/simden', 2)
read_dir(ds, '../DPC/linux/Ex-DPC/results/varden', 2)
read_dir(ds, '../DPC/linux/Ex-DPC/results/uniform', 2)
read_dir(ds, '../DPC/linux/Ex-DPC/results/reallife/geolife', 3)

df = pd.read_csv('data.csv')
df2 = pd.DataFrame(data=ds)

df = pd.concat([df, df2])

df.to_csv('data.csv')