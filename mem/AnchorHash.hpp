#include <iostream>
#include <stack>
#include <stdint.h>

/** Class declaration */
class AnchorHash {

  private:

    // Anchor
    uint32_t *A;

    // "Map diagonal"
    uint32_t *K;

    // Size of the anchor
    uint32_t M;

    // Size of the working
    uint32_t N;

    // Removed buckets
    std::stack<uint32_t> r;


  public:

    AnchorHash (uint32_t, uint32_t);

    ~AnchorHash();

    uint32_t ComputeBucket(uint64_t, uint64_t);

    uint32_t UpdateRemoval(uint32_t);

    uint32_t UpdateNewBucket();

  private:
    uint32_t ComputeTranslation(uint32_t, uint32_t);


};
