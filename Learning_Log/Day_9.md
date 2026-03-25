## Day 9 — 24 March, 2026

**Done:**
Deriverd the complexity of each of the following problems and wrote the closed forms and theri summation:
- for(i=0; i<n; i++) for(j=0; j<i; j++) → O(?)
- for(i=1; i<=n; i*=2) → O(?)
- for(i=n; i>0; i/=2) → O(?)
- Recursive: T(n) = T(n/2) + O(1) → O(?) [Master theorem]
- Recursive: T(n) = 2T(n/2) + O(n) → O(?) [Master theorem]
- Dynamic array push_back amortized — explain why O(1) amortized despite occasional O(n)


**Key concept:** 

1. *Master Theorem*: This theorem is used to solve recurrence relation of the given form in very few steps:
    T(n) = aT(n/b) + f(n)   <- form of recurrence relation to apply master theorem on.

2. *Amortized complexity:* It is a measure of average cost per operation over a sequence of operation where some individual operations are expensive and where some are not.

**Exit Q:** What is amortized O(1)? Why is dynamic array push_back O(1) amortized even though it occasionally copies the entire array?

`Amortized O(1)` is the average complexity of a given algotithm or operation calculated over a sdequence of operations performed, the average complexity comes out to be O(1) even after few individual expensive operations because the complexity of the most of the operation is O(1) and the effect of one individual expensive operation gets distributed over.

Dynamic array pushback is O(1) amortized because the resize and copying operation happens when the array gets full and one expensive operation of complexity of O(n) is performed to allocate and copy into new array.

**Confusion:** 
How master theorem works, nodes and branches and few basic terminology is still not clear!
- What exactly n^logb_a represents and f(n) too.
- How to calculate work on each level.
Only minor confusions left and will be resolve in a day!

