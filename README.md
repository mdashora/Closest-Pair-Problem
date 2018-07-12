# Closest-Pair-Problem
This project is based on the algorithm proposed by M. Golin, R. Raman, C. Schwarz, M. Smid [4]. Authors presented a simple randomized algorithm for finding closest pair in dimensional space D greater than and equal to 2, for a given set of n points. Two approaches of implementing this algorithm are Binary search tree and Dynamic perfect hashing which run in O(n log n) and O(n) expected time respectively. We present the experimental results of these approaches comparing it with naïve implementation of Brute-force technique. Author also extends the algorithm to fully dynamic closest pair problem and to k-closest pair problem.

# Motivation
Closest pair problem is one of the basic problems in computation geometry. It is building block for various geometry algorithms and data structures. Solution to this problem is a main step in problem solving procedures like Nearest Neighbor, Minimal Spanning Trees etc. Commonly, it is well known that a practical way of solving closest pair problem for two dimension is to apply O(n log n) implementation of Divide-and-Conquer technique by Bentley and Shamos [1].

# Real Life Applications:
This problem has many applications in many different domains. For example, a sea or air traffic control system may have to identity two closest vehicles for detecting possibility of potential collisions. It can also be extended to usage in self driving vehicles and project like “Waymo” by Google are evident of that. In the geographical field this problem has implementation in Geographical information systems which even extends to missile detection system. All these examples show that it is very interesting area of research as the solution to this problem directly affects the efficiency of real time systems. In next sections, we will see the work done in this area. Other applications from various domains are listed below:
•	Molecular modeling
•	Graphics and Computer vision
•	Imaging technologies
•	Pattern recognition etc.

# Problem Description:
In a layman terminology, closest pair problem is to find two points closest to each other when given a set S of n points on a multidimensional plane. For understanding the problem, we will continue with the problem in 2 dimensions. Let the Euclidean Distance between two points is given by d(p,q) then,
d(p,q) = √((𝑝𝑥 − 𝑞𝑥)2 + (py - qy) 2)
The closest pair distance is given by δ(S) where set S is the set of points {p1, p2 … , pn}.
δ(S) := min{d(p,q) : p,q ∈ S, pǂq

Mathematically, the problem can be defined as to find two closest points p,q ∈ S such that distance between two points equals the minimum distance.
d(p,q) = δ(S)

# Proposed Solution:
Authors proposes a solution to solve this problem in logarithmic O(n log n) and linear O(n) time. They propose a Simple Randomized incremental algorithm and we will see the algorithm details and implementations in next sections. Also, the high probability bounds have been explored, The linear expected time algorithm run in O(n logn / log log n) time with high probability and the logarithmic expected time algorithm runs in O(n log n) time with high probability. The solution to this problem also extends to fully dynamic algorithm and k-closest pair algorithm and also to algorithm which does not consider non-algebraic functions.
It is worth mentioning that floor functions used in above algorithm assumes to be calculated at unit cost.

To read more about project and experimental results. Please refer to Project_Details.pdf