#define _CRT_SECURE_NO_WARNING
#include"graph/Graph.hpp"
#include<string>
#include<fstream>
#include<iostream>
#include<typeinfo>
#include<unordered_set>
#include<utility>
using namespace std;

template<class GraphType,class NodeLabelType=size_t>
class GRFGraphLabel {
/*
Below is a GRFGraph.
-------------------
3
0 1
1 0
2 1
1
0 2
1
1 2
0
-------------------
GRF Graph Format 
Every File only contain one graph.
The First number N means the node number.(3)
Then N lines tell the label of each node.(node 0 has label 1)
For each node's out edge(successor),it will first tell us how many out edges it has (OE),Then next OE lines is the edges. (Like " 1 2 "  is From node 1 to node 2)
*/
public:
	static GraphType* readGraph(string graphPath) {
		fstream f;
		f.open(graphPath.c_str(), ios_base::in);
		if (f.is_open() == false) {
			cout << graphPath << " open fail" << endl;
			exit(0);
		}

		int nodeNum = 0;
		f >> nodeNum;

		GraphType* graph = new GraphType(nodeNum);

		for (auto i = 0; i < nodeNum; ++i) {
			size_t id;
			int label;
			f >> id >> label;
			graph->setNodeLabel(id,label);
		}

		bool* pp = new bool[nodeNum]();
		while (f.eof() == false) {
			int edges = 0;
			f >> edges;
			unordered_set< pair<size_t, size_t>,hash_pair > s;
			s.reserve(edges);
			for (auto i = 0; i < edges; ++i) {
				//Below first and third sentenses are important ! If you write your GraphReader,don't forget it.
				size_t source = UINT32_MAX, target = UINT32_MAX;
				f >> source >> target;
				if (source == UINT32_MAX || target == UINT32_MAX) continue; 

				pair<size_t, size_t> p(source, target);
				if (s.find(p)!=s.end())continue;
				if (pp[source] == false) {
					pp[source] = true;
				}

				s.insert(p);
				graph->addEdge(source, target);
			}
		}

		f.close();
		return graph;
	}
};
