#!/usr/bin/python
import numpy as np
import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt

# plot energy, and output error bars

N = 6
Dapper10 = (0.00014671601128, 0.00012346319461, 0.000079921462753, 0.00011148739683, 0.000010601405152, 0.00016576383292)
Dapper15 = (0.00014661079495, 0.00012346319461, 0.00008195680559, 0.00011146507513, 0.000010602890364, 0.00016575720886)
Dapper20 = (0.00014637552065, 0.00012346319461, 0.000081954459058, 0.00011146507513, 0.000010602890364, 0.00016575715628)
fig, ax = plt.subplots()

ind = np.arange(N)    # the x locations for the groups
width = 0.25         # the width of the bars
p1 = ax.bar(ind, Dapper10, width, color='r')


p2 = ax.bar(ind + width, Dapper15, width,
            color='y')

p3 = ax.bar(ind + 2*width, Dapper20, width,
            color='g')


#ax.set_title('Comparison of Dapper architectures')
ax.set_xticks(ind + width / 2)
ax.set_xticklabels(('DCT', 'Black', 'Hist', 'FWT', 'ConvTex', 'DXTC'))

ax.legend((p1[0], p2[0], p3[0]), ('Dapper10', 'Dapper15', 'Dapper20'))
ax.yaxis.set_units('Energy consumption (J)')
#ax.autoscale_view()

plt.show()
