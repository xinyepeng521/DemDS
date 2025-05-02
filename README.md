# A Dual-evaluation-mode Local-search for The Minimum Dominating Set Problem on Ultra-large Sparse Graphs
This project is the experiment codes for the paper A Dual-evaluation-mode Local-search for TheMinimum Dominating Set Problem on Ultra-large
Sparse Graphs

## Environment Requirements
- **Compiler**: `g++ 11` or higher
## How to run the code

You can compile using the following command:
```
g++ -std=c++11 -O3 -o DemDS DemDS.cpp
```

Please use the following command to execute DemDS: *ds ${graph} ${seed} ${time} ${alpha}*

- ${graph}: The file must be an undirected, unweighted graph with no self-loops.
- ${seed}: An integer.
- ${time}: Time limit (s).
- ${alpha}: A parameter in the range 0--100, recommended to be set to 90.

## The instance format
```
<number of vertices> <number of edges>
...
```

The two numbers in the first line represent the number of vertices and the number of edges; The vertices of the graph are numbered from 1 to the number of vertices.

Each of the following lines represents one edge. If a vertex is not included in any edge, it is an isolated vertex.

Take the instance hugetrace-00010 as an example. The following are the first ten lines of this instance.

```
12057441 18082179
1 2582511
1 322
1 53
2 8138735
2 2582869
2 321
3 2582518
3 60
3 59

...
```

The first line indicates that there are 12057441 vertices and 18082179 edges.
The following lines represent the edges.

### Contact Information  
If you have any questions or suggestions, feel free to reach out to me via:  
- **Email**: 778845121@qq.com
