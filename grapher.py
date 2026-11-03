import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file = pd.read_csv("/tmp/comp_arch/data.csv")
total=len(file['cycle1'])
X=np.linspace(0,total,total)
# plt.plot(X,file["cycle1"], color='blue')
# plt.plot(X,file["cycle2"], color='red')
diff=file['cycle1']-file['cycle2']
print(diff.mean(),diff.std())
plt.plot(X,diff)
plt.show()
# plt.plot(file["ipc1"],file["ipc2"], color='red')


plt.show()