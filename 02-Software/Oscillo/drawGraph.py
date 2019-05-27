import os
os.chdir(os.path.dirname(__file__))
print('Current directory',os.getcwd())

import numpy as np
import matplotlib.pyplot as plt
from collections import deque
import time
def get_sin_value(i):
	return (np.sin(2*np.pi*i/100.0-np.pi),(i+1)%100)

def update_line(hl, new_data):
    hl.set_ydata(new_data)
    plt.draw()

i = 0
q = deque()
q.append(1)

plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111)
line1, = ax.plot(range(1,len(q)+1),list(q),'b-')


while True:
	v,i=get_sin_value(i)
	q.append(v)
	if len(q)>100:
		q.popleft()
	line1.set_ydata(list(q))
	line1.set_xdata(range(1,len(q)+1))
	fig.canvas.draw()
	time.sleep(0.3)
	print(len(q))
