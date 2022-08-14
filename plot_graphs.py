import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('data.csv')[['data', 'name', 'n', 'range', 'thread', 'time', 'dim']]

sns.set(font_scale=2)
sns.set_style("whitegrid", {'axes.grid' : True})

# plot time vs n
def plot_time_n(data, thread, names):
	chosen_ns = [1000,10000,100000,1000000,10000000]
	df_uniform = df.loc[df['data']==data]
	urange = df_uniform['range'].median()
	print(data, urange)
	df_uniform = df_uniform.loc[df_uniform['range']==urange]
	df_uniform = df_uniform.loc[df_uniform['thread']==thread]
	df_uniform = pd.concat([df_uniform.loc[df_uniform['name']==name] for name in names])
	df_uniform = df_uniform.sort_values('n', ascending=True)
	result = sns.lineplot(data=df_uniform, x='n', y='time', style='name', linewidth = 3)
	[l.set_color('black') for l in result.get_lines()]
	result.set(yscale='log')
	result.set(xscale='log')
	result.set(xticks=chosen_ns)
	plt.savefig(f'{data}_{n}_timen.png',bbox_inches='tight')

#plot_time_n('geolife', 30, ['dpc', 'static', 'par'])

# plot time vs thread count
def plot_time_thread(data, n, names):
	chosen_threads = [1,2,4,8,16,30,60]
	df_uniform = df.loc[df['data']==data]
	urange = df_uniform['range'].median()
	print(data, urange)
	df_uniform = df_uniform.loc[df_uniform['range']==urange]
	df_uniform = df_uniform.loc[df_uniform['n']==n]
	df_uniform = pd.concat([df_uniform.loc[df_uniform['name']==name] for name in names])
	df_uniform = pd.concat([df_uniform.loc[df_uniform['thread']==thread] for thread in chosen_threads])
	df_uniform = df_uniform.sort_values('thread', ascending=True)
	result = sns.lineplot(data=df_uniform, x='thread', y='time', style='name', palette=('Greys'))
	[l.set_color('black') for l in result.get_lines()]
	result.set(yscale='log')
	result.set(xscale='log')
	result.set(xticks=chosen_threads)
	result.set(xticklabels=chosen_threads)
	plt.savefig(f'{data}_{n}_timethread.png',bbox_inches='tight')

#plot_time_thread('varden', 10000000, ['dpc', 'static', 'par'])

def plot_speedup_thread(data, n, names):
	chosen_threads = [1,2,4,8,16,30,60]
	df_uniform = df.loc[df['data']==data]
	urange = df_uniform['range'].median()
	print(data, urange)
	df_uniform = df_uniform.loc[df_uniform['range']==urange]
	df_uniform = df_uniform.loc[df_uniform['n']==n]
	df_uniform = pd.concat([df_uniform.loc[df_uniform['name']==name] for name in names])
	df_uniform = pd.concat([df_uniform.loc[df_uniform['thread']==thread] for thread in chosen_threads])
	df_uniform = df_uniform.sort_values('thread', ascending=True)

	for i, row in df_uniform.iterrows():
		df_ = df_uniform.loc[(df_uniform['data']==row['data']) & (df_uniform['name']==row['name']) & (df_uniform['range']==row['range']) & (df_uniform['n']==row['n']) & (df_uniform['thread']==1)]
		assert len(df_)==1
		df_uniform.at[i,'speedup']=df_['time'].values[0]/row['time']

	result = sns.lineplot(data=df_uniform, x='thread', y='speedup', style='name', linewidth=3)
	[l.set_color('black') for l in result.get_lines()]
	result.set(xscale='log')
	result.set(xticks=chosen_threads)
	result.set(xticklabels=chosen_threads)
	plt.savefig(f'{data}_{n}_speedup.png',bbox_inches='tight')

plot_speedup_thread('varden', 10000000, ['dpc', 'static', 'par'])
#plot_speedup_thread('geolife', 100000, ['dpc', 'static', 'par'])



# for i, row in df.iterrows():
# 	df_ = df.loc[df['data']==row['data'] and df['name']==row['name'] and df['range']==row['range'] and df['n']==row['n'] and df['thread']==1]
# 	assert len(df_)==1
# 	row['speedup']=row['time']/df_['time']

# # speedup vs thread count
# for data_name in df['data'].unique():
# 	df_ = df.loc[df['data'] == data_name]
# 	fig = px.line(df_, x="thread", y="speedup")
# 	fig.show()