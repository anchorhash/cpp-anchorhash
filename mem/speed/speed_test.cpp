#include <iostream>
#include <fstream>

#include "../AnchorHash.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 6) {
        cout << "Usage Error:\n";
        cout << "argv[1]: int AcnhorSet\n";
        cout << "argv[2]: int WorkingSet\n";
        cout << "argv[3]: int NumRemovals\n";
        cout << "argv[4]: int NumKeys\n";
        cout << "argv[5]: int ResFileName\n";
        return 1;
    }

    uint32_t anchor_set = atoi(argv[1]);
    uint32_t working_set = atoi(argv[2]);
    uint32_t num_removals = atoi(argv[3]);
    uint32_t num_keys = atoi(argv[4]);

    string filename = argv[5];

    srand(time(NULL));

    AnchorHash anchorhash(anchor_set, working_set);

    // random removals
    uint32_t* bucket_status = new uint32_t [anchor_set]();

    // test keys
    uint32_t* keys = new uint32_t [2*num_keys]();

    for (uint32_t i=0;i<working_set;i++) {
        bucket_status[i] = 1;
    }

    uint32_t i = 0;
    while (i < num_removals) {
        uint32_t removed = rand()%working_set;
        if (bucket_status[removed] == 1) {
            anchorhash.UpdateRemoval(removed);
            bucket_status[removed] = 0;
            i++;
        }
    }

    ofstream results_file;
    results_file.open(filename, ofstream::out | ofstream::app);

    double norm_keys_rate = (double)num_keys/1000000.0;

    ////////////////////////////////////////////////////////////////////
    for (uint32_t i=0;i<2*num_keys;++i) {
        keys[i] = rand();
    }
    clock_t  t3 = clock();
    for (uint32_t i=0;i<2*num_keys;i+=2) {
        anchorhash.ComputeBucket(keys[i], keys[i+1]);
    }
    clock_t  t4 = clock();

    // compute and print the elapsed time in sec.
    double anchor_time = (double) (t4-t3) / CLOCKS_PER_SEC;
    printf("AnchorHash: Elapsed time is %lf seconds\n", anchor_time);

    results_file << "AnchorHash:\tAnchor\t" << anchor_set << "\tWorking\t" << working_set << "\tRemovals\t" << num_removals << "\tRate\t" << norm_keys_rate/anchor_time << "\n";
    ////////////////////////////////////////////////////////////////////

    results_file.close();

    delete [] bucket_status;
    delete [] keys;

    return 0;

}
