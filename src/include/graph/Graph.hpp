#pragma once
#include<vector>
#include"Node.hpp"
#include"Edge.hpp"
#include"common.h"
#include<assert.h>
using namespace std;
namespace wg {
template<typename _NodeType, typename _EdgeType>
class Graph
{
public:
	enum GRAPH_TYPE { BIDIRECTION, DIRECTION };
	using NodeType = _NodeType;
	using EdgeType = _EdgeType;
	using NodeLabelType = typename NodeType::NodeLabelType;
	using EdgeLabelType = typename EdgeType::EdgeLabelType;

private:

	vector<NodeType> _nodes;
	GRAPH_TYPE graphType;
	size_t _size;

public:
	Graph() = default;
	Graph(const vector<NodeType>& __nodes) :_nodes(__nodes) {
		_size = _nodes.size();
	}
	~Graph() = default;

	Graph(const size_t s, GRAPH_TYPE _graphType = GRAPH_TYPE::DIRECTION) :_size(s), graphType(_graphType) {
		vector<NodeType> n;
		n.reserve(s + 1);
		for (auto i = 0; i < s; ++i) n.push_back(NodeType(i));
		swap(_nodes, n);

	}

	void setNodeLabel(const NodeIDType _id, const NodeLabelType _label) {
		assert((_id < _size) && "node ID overflow");
		_nodes[_id].setLabel(_label);
		return;
	}
	void addEdge(const NodeIDType source, const NodeIDType target, const EdgeLabelType edgeLabel = EdgeLabelType()) {

		//	assert(source != target && "not support self loop");
		assert(source < _size && target < _size && "node id should smaller than node number");
		auto& sourceNode = _nodes[source];
		auto& targetNode = _nodes[target];

		const EdgeType  sourceEdge = EdgeType(source, target, edgeLabel);
		const EdgeType  targetEdge = EdgeType(source, target, edgeLabel);
		sourceNode.addOutEdge(targetEdge);
		targetNode.addInEdge(sourceEdge);
		if (GRAPH_TYPE::BIDIRECTION == graphType) {
			const EdgeType sourceEdge1 = EdgeType(target, source, edgeLabel);
			const EdgeType targetEdge1 = EdgeType(target, source, edgeLabel);
			sourceNode.addInEdge(sourceEdge1);
			targetNode.addOutEdge(targetEdge1);
		}
	}

	size_t size() const {
		return _size;
	};
	const vector<NodeType>& nodes()const { return _nodes; }

	const NodeType& node(const NodeIDType& nodeID) const {
		assert((nodeID < _size) && "node ID overflow");
		return _nodes[nodeID];
	}

	void graphBuildFinish() {
		for (auto& node : _nodes) {
			node.NodeBuildFinish();
		}

	}
	const NodeType& operator[](const NodeIDType& nodeID)const {
		return node(nodeID);
	}

};

}