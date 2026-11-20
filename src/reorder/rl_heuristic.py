import numpy as np
import pickle
from pathlib import Path

def relu(x):
	return np.maximum(x,0)

def me_to_id_all(me, adj,children_to_ctx):
	n = len(me)
	ids = np.concatenate([me, np.zeros((n, 11))], axis=1)
	for i in range(n - 1, -1, -1):
		w = adj[i]; mask = w > 0
		if mask.any():
			agg = (w[mask] @ ids[mask]) / w[mask].sum()      # edge-weighted mean
			ids[i, 65:] = np.tanh(children_to_ctx @ agg)
	return ids

raw_data=np.fromfile("/tmp/rl_run/input_adj.bin",dtype=np.int32)
num_instructions=int(raw_data[0])
adjmatrix=raw_data[1:].reshape((num_instructions,num_instructions)).astype(np.float32) # weighted edges
me=np.fromfile("/tmp/rl_run/input_me.bin",dtype=np.int32)
data = me.reshape((num_instructions,4)).astype(np.float32) # rs1, rs2, rd, num_of_children without normalization
#print(adjmatrix)

rows = np.arange(num_instructions)

# Extract columns and cast indices to integers
r1 = data[:, 0].astype(int)
r2 = data[:, 1].astype(int)
r3 = data[:, 2].astype(int)
val = data[:, 3]

# 1. First 32 cols: Logical OR of one-hot(r1) and one-hot(r2)
oh_r1_r2 = np.zeros((num_instructions, 32), dtype=np.float32)
oh_r1_r2[rows, r1] = 1.0
oh_r1_r2[rows, r2] = 1.0  # Setting 1.0 twice acts as a logical OR (even if r1 == r2)

# 2. Next 32 cols: One-hot(r3)
oh_r3 = np.zeros((num_instructions, 32), dtype=np.float32)
oh_r3[rows, r3] = 1.0

# 3. Final col (1 col): Softmax over all n values (numerically stable)
exp_val = np.exp(val - np.max(val))
softmax_val = (exp_val / np.sum(exp_val)).reshape(num_instructions, 1)

# Combine into n x 65 matrix
me_vector = np.hstack([oh_r1_r2, oh_r3, softmax_val])

if(num_instructions<=50):
	with open("./src/reorder/Weights_25.pkl", "rb") as f:
		save_data = pickle.load(f)
else :
	with open("./src/reorder/Weights_50.pkl", "rb") as f:
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
print(ids)
print("worked")





