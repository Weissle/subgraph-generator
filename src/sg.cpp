#include"tools/GraphReader.hpp"
#include"tools/SubgraphGenerator.hpp"
#include<tools/RandomGenerator.hpp>
#include<tools/IndexTurner.hpp>
#include"tools/argh.h"
#include"common.h"
#include<string>
#include<thread>
using namespace std;
using namespace wg;

template<class GraphType>
void writeToFile(const string& fileName, const GraphType& graph);

void writeMapping(const string& fileName, const vector<NodeIDType>& nodes);

template<class Graph>
Graph* generatorGraph(size_t graph_node, size_t labelTypes, size_t edgeavg, double variance);

int main(int argc, char* argv[]) {

	argh::parser cmdl({ "-graph","-small-node" ,"-mg","-sg","big-node","-edge-avg","-labels","-bg","-variance","-labelTypes" });
	cmdl.parse(argc, argv);
	string graph_path, midGraphPath, smallGraphPath, bigGraphPath;
	int subgraph_node = 0, graph_node = 0, labelTypes = 5;
	double variance = 1;
	double edgeavg = 1;
	//big graph part , If you want use yourself's graph ,please use -graph.
	cmdl({ "-graph" }) >> graph_path;				//big graph path
	//randomly generate big graph
	cmdl({ "-big-node" }) >> graph_node;			//big graph node		
	cmdl({ "-labelTypes" }) >> labelTypes;			//big graph label type
	cmdl({ "-edge-avg" }) >> edgeavg;				//how many nodes have out edges in average (default 1)
	cmdl({ "-variance" }) >> variance;				//variance of nodes' out edges number
	cmdl({ "-bg" }) >> bigGraphPath;				//big graph path
	assert((graph_path.empty() ^ graph_node == 0));
	//subgraph part
	cmdl({ "-small-node" }) >> subgraph_node;		//subgraph node number
	cmdl({ "-mg" }) >> midGraphPath;				//the mapping path
	cmdl({ "-sg" }) >> smallGraphPath;				//subgraph path

	typedef Edge<int> EdgeType;
	typedef Node<int, EdgeType> NodeType;
	typedef Graph<NodeType, EdgeType> GraphType;

	auto time1 = clock();

	srand(uint32_t(time(NULL)));

	

	//big graph part
	GraphType* graph = nullptr;
	if (graph_path.empty()) {
		graph = generatorGraph<GraphType>(graph_node, labelTypes, edgeavg, variance);
		writeToFile(bigGraphPath, *graph);

	}
	else {
		graph = GRFGraphLabel<GraphType, size_t>::readGraph(graph_path.c_str());
	}
	if (subgraph_node) {
		sg::SubgraphGenerator<GraphType> subgraphG(*graph, subgraph_node);
		subgraphG.run();
	//	cout << "subgraph generation is finished" << endl;
		const auto midGraph = subgraphG.getMid();
		writeMapping(midGraphPath, midGraph);
		auto queryGraph = subgraphG.getSmallGraph();

		queryGraph->graphBuildFinish();
		writeToFile(smallGraphPath, *queryGraph);
	}


	delete graph;

	PRINT_TIME_COST_S("time cost : ", clock() - time1);
	return 0;
}

template<class GraphType>
void writeToFile(const string& fileName, const GraphType& graph) {
	ofstream f;
	f.flush();
	f.open(fileName.c_str(), ios::out);
	if (f.is_open() == false) {
		cout << fileName << " : open fail" << endl;
		return;
	}
	f << graph.size() << endl;
	for (auto& node : graph.nodes()) f << node.id() << " " << node.label() + 1 << endl;
	for (auto& node : graph.nodes()) {
		f << node.outEdgesNum() << endl;
		for (auto edge : node.outEdges()) {
			f << node.id() << " " << edge.target() << endl;
		}
	}
	f.close();
}
void writeMapping(const string& fileName, const vector<NodeIDType>& nodes) {
	if (fileName.empty())return;
	ofstream f;
	f.flush();
	f.open(fileName.c_str(), ios::out);
	if (f.is_open() == false) {
		cout << fileName << " : open fail" << endl;
		return;
	}
	for (int i = 0; i < nodes.size(); ++i) {
		f << i << " " << nodes[i] << endl;
	}
	f.close();
}

template<class Graph>
Graph* generatorGraph(size_t graph_node, size_t labelTypes, size_t edgeavg, double variance) {

	using NodeType = typename Graph::NodeType;
	vector<NodeType> nodes(graph_node);
	rg::RandomGenerator* randomer = new rg::NormalRandomGenerator(edgeavg, variance);
	Graph *graph = new Graph(graph_node);
	//Set label
	LOOP(i, 0, graph_node) {
		graph->setNodeLabel(i, rand() % labelTypes);
	}
	//connect all nodes
	vector<NodeIDType> in(graph_node);
	rg::NoRepeatIntRandomGenerator fnp(graph_node - 1);
	int inP = 1, noP = graph_node - 1;
	in[0] = graph_node - 1;
	LOOP(i, 0, graph_node - 1) {
		auto one = rand() % inP;
		auto to = fnp.getOne();
		if (rand() % 2) graph->addEdge(in[one], to);
		else graph->addEdge(to, in[one]);
		in[inP++] = to;
	}
	//insert edge
	LOOP(i, 0, graph_node) {
		int edgeNum = min(max(0, (int)randomer->getOne()), max(0,int(graph_node - 2)));
		rg::NoRepeatIntRandomGenerator irg(graph_node);

		auto outEdges = graph->node(i).outEdges();
		unordered_set<NodeIDType> exclude;
		exclude.reserve(graph_node);
		for (const auto& edge : outEdges) exclude.insert(edge.target());
		LOOP(j, 0, edgeNum) {
			NodeIDType to = irg.getOne();
			if (exclude.find(to) != exclude.end()) {
				--j;
				continue;
			}
			if (to == -1) break;
			graph->addEdge(i, to);
		}
	}

	graph->graphBuildFinish();
	return graph;
}