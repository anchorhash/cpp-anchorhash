#include "AnchorHashQre.hpp"
#include "./misc/crc32c_sse42_u64.h"

using namespace std;

/** Constructor */
AnchorHashQre::AnchorHashQre (uint32_t a, uint32_t w) {
	
	// Allocate the anchor array	
	A = new uint32_t [a]();
		
	// Allocate the working array
	W = new uint32_t [a]();

	// Allocate the last apperance array
	L = new uint32_t [a]();	

	// Allocate the "map diagonal"	
	K = new uint32_t [a]();
	
	// Initialize "swap" arrays 
	for(uint32_t i = 0; i < a; ++i) {
		L[i] = i;
		W[i] = i;
		K[i] = i;
	}
				
	// We treat initial removals as ordered removals
	for(uint32_t i = a - 1; i >= w; --i) {				
		A[i] = i;	
		r.push(i);			
	}
			
	// Set initial set sizes
	M = a;
	N = w;
			
}

/** Destructor */
AnchorHashQre::~AnchorHashQre () {
	
	delete [] A;		    
	delete [] W;	
	delete [] L;	
	delete [] K;	

}

uint32_t AnchorHashQre::ComputeTranslation(uint32_t i , uint32_t j) {
	
	if (i == j) return K[i];
	
	uint32_t b = j;
	
	while (A[i] <= A[b]) {
		b = K[b];
	}
	
	return b;

}

uint32_t AnchorHashQre::ComputeBucket(uint64_t key1 , uint64_t key2) {
								
	// First hash is uniform on the anchor set
	uint32_t bs = crc32c_sse42_u64(key1, key2);
	uint32_t b = bs % M;
						
	// Loop until hitting a working bucket
	while (A[b] != 0) {	
			
		// New candidate (bs - for better balance - avoid patterns)			
		bs = crc32c_sse42_u64(key1 - bs, key2 + bs);
		uint32_t h = bs % A[b];
				
		//  h is working or observed by bucket
		if ((A[h] == 0) || (A[h] < A[b])) {
			b = h;
		}
						
		// need translation for (bucket, h)
		else {
			b = ComputeTranslation(b,h);				
		}
										
	}
		
	return b;
										
}

uint32_t AnchorHashQre::UpdateRemoval(uint32_t b) {

	// update reserved stack
	r.push(b);
				
	// update live set size
	N--;
		
	// who is the replacement
	W[L[b]] = W[N];
	L[W[N]] = L[b];
		
	// Update map diagonal
	K[b] = W[N];

	// Update removal
	A[b] = N;
		
	return 0;	
															
}

uint32_t AnchorHashQre::UpdateNewBucket() {

	// Who was removed last?	
	uint32_t b = r.top();							
	r.pop();
	
	// Restore in observed_set
	L[W[N]] = N;	
	W[L[b]] = b;
	
	// update live set size
	N++;
		
	// Ressurect
	A[b] = 0;
	
	// Restore in diagonal
	K[b] = b;
	
	return b;
									
}
