# AnchorHash - A Scalable Consistent Hash

AnchorHash is described in our paper [AnchorHash: A Scalable Consistent Hash](https://arxiv.org/abs/1812.09674)

Consistent hashing (CH) is a central building block in many networking applications, from datacenter load-balancing to distributed storage. Unfortunately, state-of-the-art CH solutions cannot ensure full consistency under arbitrary changes and/or cannot scale while maintaining reasonable memory footprints and update times. We present AnchorHash, a scalable and fully-consistent hashing algorithm. AnchorHash achieves high key lookup rates, a low memory footprint, and low update times. We formally establish its strong theoretical guarantees, and present advanced implementations with a memory footprint of only a few bytes per resource. Moreover, extensive evaluations indicate that it outperforms state-of-the-art algorithms, and that it can scale on a single core to 100 million resources while still achieving a key lookup rate of more than 15 million keys per second.

## Code
This repository contains the code used to create the figures for the evaluation section

### Try it
Go into the `tests\speed` and `tests\balance` directories, run make, run the python script, and plot

### System Requirements
This implementation makes use of the `CRC32` CPU instruction of the *Streaming SIMD Extensions 4 (SSE4)*. You can replace it in `misc/crc32c_sse42_u64.h`. 

## Other implementations

### Go

- https://github.com/anchorhash/go-anchorhash
- https://github.com/OmerBenHayun/go-anchorhash
- https://github.com/wdamron/go-anchorhash

### Python
- https://github.com/anchorhash/py-anchorhash

# Notes

* In a distributed system, must maintain consensus on the ordering of changes to the working set and on the seed for key hashing (digest)

* Hash functions must be independent for differenet values of k and b


# Algorithm

```hs
INITWRAPPER(a,S)                // a anchor capacity, S list of resources, a>=|S|
  M←∅
  for i∈(0,1,...,|S|−1) do 
    M←M∪{(i,S[i])}              // mapping from bucket to resource
  INITANCHOR(a,|S|)

GETRESOURCE(k)                  // compute resource for key k 
  b←GETBUCKET(hash(k))          // convert key to int (e.g., rand(seed=k)) and call anchorHash
  ξ←M(b)
  return ξ
  
ADDRESOURCE(ξ)
  b←ADDBUCKET( )
  M←M∪{(b,ξ)}
  
REMOVERESOURCE(ξ)
  b←INV_M(ξ)
  M←M\{(b,ξ)}
  REMOVEBUCKET(b)
```

```hs
INITANCHOR(a,w)                 // a anchor size (capacity), w number of workers (size) 
  A[b]←0 for b=0,1,...,a−1      // W_b←0 for b∈A
  R←∅                           // empty stack
  N←w                           // mumber of initially working buckets
  K[b]←L[b]←W[b]←b for b=0,1,...,a−1
  for b=a−1 downtow do          // remove initially unused buckets
    R.push(b)
    A[b]←b
    
GETBUCKET(k)
  b←hash(k) mod a               // can use k if calling through wrapper as it is already hash(key)
  while A[b]>0 do               // b is removed
    h←h_b(k)                    // h←hash(b,k) mod A[b] OR k←rand(seed=k), h←k mod A[b]
    while A[h]≥A[b] do          // W_b[h] != h, b removed prior to h
      h←K[h]                    // search for W_b[h]
      b←h                       // b←H_W_b(k)
  return b

ADDBUCKET( )
  b←R.pop()
  A[b]←0                        // W←W ∪ {b}, delete W_b
  L[W[N]]←N
  W[L[b]]←K[b]←b
  N←N+ 1
  return b
  
REMOVEBUCKET(b)
  R.push(b)
  N←N−1
  A[b]←N                        // W_b←W\b, A[b]←|W_b|
  W[L[b]]←K[b]←W[N]
  L[W[N]]←L[b]
```
