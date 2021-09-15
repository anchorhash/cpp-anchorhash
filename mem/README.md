# AnchorHash - using less memory

This is a version that uses only half the memory for storing state, as compared to the version in the [paper](https://doi.org/10.1109/TNET.2020.3039547). It makes exactly the same hashing decisions and has exactly the same key lookup speed. The only difference is that each bucket remove takes slightly longer (order of a key lookup operation vs. O(1)). Bucket addition time is unchanged.

## Code
This code is a direct replacement to `AnchorHashQre.cpp` and `AnchorHashQre.hpp`.

### Try it
Go into the `speed` directory, run make, run the python script, and plot

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
  K[b]←b for b=0,1,...,a−1
  for b=a−1 downtow do          // remove initially unused buckets
    R.push(b)
    A[b]←b

BUCKETATVIEW(b,v)
  while A[b]>=v do              // b is removed for view size v
    b←K(b)                      // search for W_v[b]
  return b

GETBUCKET(k)
  b←hash(k) mod a               // can use k if calling through wrapper as it is already hash(key)
  while A[b]>0 do               // b is removed
    h←h_b(k)                    // h←hash(b,k) mod A[b] OR k←rand(seed=k), h←k mod A[b]
    b←BUCKETATVIEW(h,A[b])
  return b

ADDBUCKET( )
  b←R.pop()
  N←N+ 1
  A[b]←0                        // W←W ∪ {b}, delete W_b
  K[b]←b
  return b

REMOVEBUCKET(b)
  R.push(b)
  h←BUCKETATVIEW(N-1,N)
  K[b]←h
  N←N−1
  A[b]←N                        // W_b←W\b, A[b]←|W_b|
```
