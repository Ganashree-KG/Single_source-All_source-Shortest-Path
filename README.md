# Single_source-All_source-Shortest-Path
To find the Single Source Shortest Path (SSSP) and All Pairs Shortest Path (APSP) on graphs with multi-dimensional edge weights, shortest path algorithms like Bellman-Ford and Floyd-Warshall can be adapted

OBJECTIVES 
>> Extend Bellman-Ford and Floyd-Warshall algorithms to handle multi-dimensional edge weights.
>> Implement graph parsing from CSV files that contain multi-dimensional data for each edge.
>> Detect negative weight cycles in the graph, which are crucial for ensuring valid shortest paths in the presence of negative weights.
>> Optimize memory usage by dynamically allocating memory based on the graph size and the number of weight dimensions.
>> Visualize shortest path calculations, allowing users to analyse the results for each vertex.

PROBLEM DEFINATION
Multi-dimensional Edge Weights: Each edge in the graph has multiple weight attributes (dimensions) representing different criteria (e.g., distance, time, cost, environmental impact). This adds complexity as each path has multiple criteria to evaluate, rather than a single scalar weight.
SSSP: Find the shortest path from a single source node to all other nodes in the graph.
APSP: Calculate the shortest paths between all pairs of nodes in the graph.
