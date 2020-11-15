#include <iostream>
#include <fstream>

#include "../../AnchorHashQre.hpp"

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
	        
    AnchorHashQre anchorhashqre(anchor_set, working_set);
    
    // for lb
    uint32_t* anchor_ansorbed_keys = new uint32_t [anchor_set]();
       
    // random removals
    uint32_t* bucket_status = new uint32_t [anchor_set]();

    for (uint32_t i=0;i<working_set;i++) {
		bucket_status[i] = 1;
	}
	
    uint32_t i = 0;
    while (i < num_removals) {
		uint32_t removed = rand()%working_set;
		if (bucket_status[removed] == 1) {
			anchorhashqre.UpdateRemoval(removed);	
			bucket_status[removed] = 0;
			i++;
		}
	}
		           	
	ofstream results_file;
	results_file.open(filename, ofstream::out | ofstream::app);
	
			
	////////////////////////////////////////////////////////////////////
	for (uint32_t i=0;i<num_keys;++i) {						
		anchor_ansorbed_keys[anchorhashqre.ComputeBucket(rand(), rand())] += 1;				
	}		

	// check load balancing
	double mean = (double)num_keys/(working_set - num_removals);
	
	double lb = 0;
	for (uint32_t i=0;i<anchor_set;i++) {
		
		if (bucket_status[i]) {
						
			if (anchor_ansorbed_keys[i]/mean > lb) {
				lb = anchor_ansorbed_keys[i]/mean;
			}
			
		}
		
		else {
			if (anchor_ansorbed_keys[i] > 0) {
				printf("Anchor: crazy bug!\n");
			}		
		}
		
	}
	
	// print lb res	
	printf("Anchor: LB is %lf\n", lb);
		
	results_file << "AnchorHashQre: " << "Balance: " << lb << "\n";	
	////////////////////////////////////////////////////////////////////	
		
	results_file.close();
	
	delete [] bucket_status;
	delete [] anchor_ansorbed_keys;
		
    return 0;
    
}
