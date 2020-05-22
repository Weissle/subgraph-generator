# subgraph-generator
This tool can generator random graph and subgraph.
## How to Build

```
mkdir build
cmake ../src
make
```

## Simple Tutorial
Randomly generate graph and subgraph
```
./sg -big-node 100 -small-node 20 -bg big.graph -sg small.graph -mg map.txt
```
Generator a subgraph for your graph
```
./sg -graph your.graph -small-node 5 -sg small.graph -mg map.txt
```
If you do not need the map, you could remove "-mg <file>".
When generate graph,you can choose node label types number,out edges for each node in average and so on.You can see the choices in sg.cpp.
```
./sg -big-node 100 -labelTypes 2 -edge-avg 2 -variance 0.5 -small-node 10 -bg big.graph -sg small.graph
```
	
## Other
Randomly graph and subgraph is a weakly connected at least. So if you use your graph and it is not a weakly connected graph,nodes number of subgraph may less than you need.
