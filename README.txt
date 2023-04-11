fibofuck is a follow up project to heapfuck . 

It's heapfuck but worse (better). Instead of manipulating a binary heap like a baby 
the environment is a weird amalgamate of a fibbo heap and a skew heap. 

(Essentially a set of skew heaps)

needless to say it'll reuse most of it's code from heapfuck (which reuses the (SIASL)² code )

the only part that'll be very different is the actual heap implementation 

to compile fibofuck you'll need gcc , flex, bison and make. 
If you have all of those , simply type "make fibofuck" in the command line
