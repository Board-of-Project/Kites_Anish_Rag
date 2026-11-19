import numpy as np
import pickle
from pathlib import Path

def relu(x):
	return np.maximum(x,0)

def me_to_id_all(me, adj, children_to_ctx):
	n = len(me)
	ids = np.concatenate([me, np.zeros((n, 11))], axis=1)
	for i in range(n - 1, -1, -1):
		w = adj[i]; mask = w > 0
		if mask.any():
			agg = (w[mask] @ ids[mask]) / w[mask].sum()      # edge-weighted mean
			ids[i, 5:] = np.tanh(children_to_ctx @ np.r_[w[mask].sum(), agg])
	return ids

raw_data=np.fromfile("/tmp/rl_run/input_adj.bin",dtype=np.int32)
num_instructions=int(raw_data[0])
adjmatrix=raw_data[1:].reshape((num_instructions,num_instructions)).astype(np.float32) # weighted edges
me=np.fromfile("/tmp/rl_run/input_me.bin",dtype=np.int32)
me_vector = me.reshape((num_instructions,5)).astype(np.float32) # num_inst x 5 in og order

with open("./src/reorder/Weights_short_latestgen.pkl", "rb") as f:
	save_data = pickle.load(f)
children_to_ctx = save_data["children_to_ctx"].copy()
W1 = save_data["W1"].copy()
b1 = save_data["b1"].copy()
W2 = save_data["W2"].copy()
b2 = save_data["b2"].copy()
W3 = save_data["W3"].copy()

ids = me_to_id_all(me_vector, adjmatrix, children_to_ctx)
ps = relu(relu(ids @ W1.T + b1) @ W2.T + b2) @ W3.T
ps.tofile("/tmp/rl_run/priority_out.bin")

print("worked")





