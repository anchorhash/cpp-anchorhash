#!/usr/bin/env python

import matplotlib.pyplot as plt
import math
	
def read_anchor_res(fn):	

	with open(fn) as fp:  
	   anchor_lines = fp.readlines()
	  
	achor_res = [x.split() for x in anchor_lines]
	
	achor_num_buckets = [float(i[4]) for i in achor_res]
	achor_rates = [float(i[8]) for i in achor_res]	

	return (achor_num_buckets, achor_rates)
			
buckets1, rates1 = read_anchor_res("anchor_0.txt")
buckets2, rates2 = read_anchor_res("anchor_10.txt")
buckets3, rates3 = read_anchor_res("anchor_100.txt")
buckets4, rates4 = read_anchor_res("anchor_1000.txt")
buckets5, rates5 = read_anchor_res("anchor_10000.txt")

plt.semilogx(buckets1, rates1, label= 'AnchorHash 0%')
plt.semilogx(buckets2, rates2, label= 'AnchorHash 10%')
plt.semilogx(buckets3, rates3, label= 'AnchorHash 100%')
plt.semilogx(buckets4, rates4, label= 'AnchorHash 1000%')
plt.semilogx(buckets5, rates5, label= 'AnchorHash 10000%')

plt.xlabel('Number of buckets')
plt.ylabel('Rate [Mkps]')
plt.legend()
plt.show()
