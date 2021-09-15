#include "AnchorHash.hpp"
#include "../misc/crc32c_sse42_u64.h"

using namespace std;

/** Constructor */
AnchorHash::AnchorHash (uint32_t a, uint32_t w) {

    // Allocate the anchor array
    A = new uint32_t [a]();

    // Allocate the "replaced by"
    K = new uint32_t [a]();

    // Initialize "swap" arrays
    for(uint32_t i = 0; i < a; ++i) {
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
AnchorHash::~AnchorHash () {

    delete [] A;
    delete [] K;

}

inline uint32_t AnchorHash::ComputeTranslation(uint32_t h, uint32_t view_size) {
    while (A[h] >= view_size) {
        h = K[h];
    }
    return h;
}

uint32_t AnchorHash::ComputeBucket(uint64_t key1 , uint64_t key2) {

    // First hash is uniform on the anchor set
    uint32_t bs = crc32c_sse42_u64(key1, key2);
    uint32_t b = bs % M;

    // Loop until hitting a working bucket
    while (A[b] != 0) {
        bs = crc32c_sse42_u64(key1 - bs, key2 + bs);
        uint32_t h = bs % A[b];

        // update h to reflect b's view
        b = ComputeTranslation(h, A[b]);
    }

    return b;

}

uint32_t AnchorHash::UpdateRemoval(uint32_t b) {

    // update reserved stack
    r.push(b);

    // find replacement for b at slot N-1
    uint32_t h = ComputeTranslation(N-1, N);

    // Update "replaced by" map
    K[b] = h;

    // update live set size
    N--;

    // Update removal
    A[b] = N;

    return 0;

}

uint32_t AnchorHash::UpdateNewBucket() {

    // Who was removed last?
    uint32_t b = r.top();
    r.pop();

    // update live set size
    N++;

    // Ressurect
    A[b] = 0;

    // Restore in "replaced by" map
    K[b] = b;

    return b;

}
