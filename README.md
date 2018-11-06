# Submission to Travelling Salesman Challenge 2.0

We have solved the problem by simulated annealing, which variously permutates the order of clusters. Initialization is done by a simple greedy algorithm. 

We used simulated annealing because it can be executed very quickly, without any memory allocations (as opposed to more complex genetic algorithms), so it's ideal considering the rather short time limit -- 15 seconds for 300 clusters.
