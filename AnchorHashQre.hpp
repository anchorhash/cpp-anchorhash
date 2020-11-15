#include <iostream>
#include <stack>
#include <stdint.h>

/** Class declaration */
class AnchorHashQre {
	
  private:
	
	// Anchor		
	uint32_t *A;

	// Working
	uint32_t *W;

	// Last appearance 
	uint32_t *L;

	// "Map diagonal"	
	uint32_t *K;
	       			
	// Size of the anchor
	uint32_t M;
		
	// Size of the working
	uint32_t N;
	
	// Removed buckets
	std::stack<uint32_t> r;
            
	// Translation oracle
	uint32_t ComputeTranslation(uint32_t i , uint32_t j);
					
  public:
  
	AnchorHashQre (uint32_t, uint32_t);
	
	~AnchorHashQre();
		
	uint32_t ComputeBucket(uint64_t, uint64_t);
        
	uint32_t UpdateRemoval(uint32_t);
    
	uint32_t UpdateNewBucket();
           
};
