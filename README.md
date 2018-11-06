# Submission to Travelling Salesman Challenge 2.0

We solved the problem by simulated annealing, which variously permutated an order of clusters. Initialization is done by a simple greedy algorithm. We used simulated annealing because it can be executed very quickly, without any memory allocations (as opposed to more complex genetic algorithms), so it's ideal for the short time limit -- 15 seconds for 300 clusters.
