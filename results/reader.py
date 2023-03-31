import os

dataset = 'gowalla'

runtimes = {}
count = 3

for folder in os.listdir():
	if len(folder) == len(dataset)+1 and folder[:-1]==dataset:
		for file in os.listdir(folder):
			algo = file.split('_')[0]
			thread = int(file.split('.tx')[0].split('_')[-1])
			if algo not in runtimes.keys():
				runtimes[algo] = {}
			if thread not in runtimes[algo].keys():
				runtimes[algo][thread] = 0
			with open(os.path.join(folder, file)) as f:
				times = [float(s) for s in f.readlines()]
			runtimes[algo][thread]+=times[1]

print(f'{dataset} performance')
for key, value in runtimes.items():
	for key2 in sorted(list(value.keys())):
		runtimes[key][key2] /= count
		print(f'{key}, {key2}: {runtimes[key][key2]}')

