#pragma once
#include<assert.h>
#include<iostream>
#include"common.h"
namespace wg {

template<typename _EdgeLabelType>
class Edge {
public:
	typedef _EdgeLabelType EdgeLabelType;
	typedef Edge<EdgeLabelType> EdgeType;
private:
	NodeIDType _source, _target;
	EdgeLabelType _label;
public:
	Edge() = default;
	~Edge() = default;
	Edge(const NodeIDType _s, const NodeIDType _t, const EdgeLabelType _l = EdgeLabelType()) :_source(_s), _target(_t), _label(_l) {}
	inline const NodeIDType& source() const { return _source; }
	inline const NodeIDType& target()const { return _target; }
	inline const EdgeLabelType& label()const { return _label; }
	inline bool isSameTypeEdge(const EdgeType& n) const {return _label == n.label();}

	bool operator<(const EdgeType& e)const {
		if (_source == e.source()) {
			if (_target == e.target()) {
				return _label < e.label();
			}
			else return _target < e.target();
		}
		else return _source < e.source();
	};
	bool operator==(const EdgeType& e)const {
		if (this->_label != e._label) return false;
		if (this->_source != e._source || this->_target != e._target)return false;
		return true;
	}
};


}