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

up = 6

workingset = [np.ceil(1.0*(10**i)) for i in range(1,up)]

acnhorset_0 = [np.ceil(1.0*(10**i)) for i in range(1,up)]
acnhorset_10 = [np.ceil(1.1*(10**i)) for i in range(1,up)]
acnhorset_100 = [np.ceil(2.0*(10**i)) for i in range(1,up)]
acnhorset_1000 = [np.ceil(10.0*(10**i)) for i in range(1,up)]
acnhorset_10000 = [np.ceil(100.0*(10**i)) for i in range(1,up)]



numkeys = 100000000
numremovals = 0

for i in range(len(workingset)):

    call(["./speed_test", str(acnhorset_0[i]), str(acnhorset_0[i]), str(acnhorset_0[i]-workingset[i]), str(numkeys), 'anchor_0.txt'])
    call(["./speed_test", str(acnhorset_10[i]), str(acnhorset_10[i]), str(acnhorset_10[i]-workingset[i]), str(numkeys), 'anchor_10.txt'])
    call(["./speed_test", str(acnhorset_100[i]), str(acnhorset_100[i]), str(acnhorset_100[i]-workingset[i]), str(numkeys), 'anchor_100.txt'])
    call(["./speed_test", str(acnhorset_1000[i]), str(acnhorset_1000[i]), str(acnhorset_1000[i]-workingset[i]), str(numkeys), 'anchor_1000.txt'])
    call(["./speed_test", str(acnhorset_10000[i]), str(acnhorset_10000[i]), str(acnhorset_10000[i]-workingset[i]), str(numkeys), 'anchor_10000.txt'])








