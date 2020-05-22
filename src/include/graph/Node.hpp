#pragma once
#include"Edge.hpp"
#include"common.h"
#include<algorithm>
#include<vector>
using namespace std;
namespace wg {
template<typename _NodeLabelType, typename _EdgeType>
class Node {
public:
	typedef _NodeLabelType NodeLabelType;
	typedef _EdgeType EdgeType;
	typedef Node<NodeLabelType,EdgeType> NodeType;

private:
	NodeIDType _id;
	NodeLabelType _label;
	vector<EdgeType> _inEdges, _outEdges;

public:
	Node() = default;
	~Node() = default;
	Node(const NodeIDType _i, const NodeLabelType _l = NodeLabelType()) :_id(_i), _label(_l) {}
	Node(const NodeIDType _i, const vector<EdgeType>& _iE, const vector<EdgeType>& _oE, const NodeLabelType _l = NodeLabelType()) :Node(_i, _l) {
		_inEdges = _iE;
		_outEdges = _oE;
	}
	const NodeIDType id()const {
		return _id;
	}
	const NodeLabelType& label()const {
		return _label;
	}
	void setLabel(const NodeLabelType _l) {
		this->_label = _l;
	}
	bool isSameType(const NodeType& n)const {
		return _label == n.label();
	}

	const vector<EdgeType>& outEdges() const { return _outEdges; }
	const vector<EdgeType>& inEdges() const { return _inEdges; }
	size_t outEdgesNum() const { return _outEdges.size(); }
	size_t inEdgesNum() const { return _inEdges.size(); }
	void addInEdge(const EdgeType& e) {
		_inEdges.push_back(e);
	}
	void addOutEdge(const EdgeType& e) {
		_outEdges.push_back(e);
	}
	void NodeBuildFinish() {
		sort(_inEdges.begin(), _inEdges.end());
		sort(_outEdges.begin(), _outEdges.end());
	}
};
}