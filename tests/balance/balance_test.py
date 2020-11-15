#!/usr/bin/env python

import os
import numpy as np
from subprocess import call

'''
	AnchoHash:
    if (argc < 6) {
		cout << "Usage Error:\n";
		cout << "argv[1]: int AcnhorSet\n";
		cout << "argv[2]: int WorkingSet\n";
		cout << "argv[3]: int NumRemovals\n";
		cout << "argv[4]: int NumKeys\n";
		cout << "argv[5]: int ResFileName\n";
		return 1;
	}
	
'''

try:
	
	dir_name = "./"
	test = os.listdir(dir_name)

	for item in test:
		if item.endswith(".txt"):
			os.remove(os.path.join(dir_name, item))
	
	
except OSError:
    pass
   
numkeys = [10**i for i in range(3,10)]
numremovals = 100

for i in numkeys:

	call(["./balance", str(1000), str(1000), str(numremovals), str(i), 'anchor_balance.txt'])



	
	
	
	
	

