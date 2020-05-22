#pragma once
#include<map>
#include<vector>
#include<unordered_map>
#include<map>
#include<typeinfo>
#include"common.h"
using namespace std;
/*

Main function is operator [] and () ,
operator[] is used in graph output, it can turn size_t to NameType
operator() is used in graph input, it can turn NameType to size_t

*/
namespace wg {
template<typename NameType>
class IndexTurner {
private:
	vector<NameType> BIndex;
	map<NameType,size_t> index;
	size_t _s = 0;
public:
	IndexTurner() = default;
	IndexTurner(const size_t  s) {
		BIndex.reserve(s);
	}
	~IndexTurner() = default;
	void clear() {
		_s = 0;
		index.clear();
	}
	size_t size() { return _s; }
	//from size_t to your type
	NameType operator[](const size_t id)const {
		if (id > _s) throw "id>size()";
		return BIndex[id];
	}
	NameType userID(const size_t id)const {
		this->operator[](id);
	}
	//from your type to size_t
	size_t operator()(const NameType& name) {
		auto temp = index.find(name);
		if (temp == index.end()) {
			index[name] = _s;
			BIndex.push_back(name);
			++_s;
			return _s - 1;

		}
		else {
			return temp->second;
		}
	}
	size_t graphID(const NameType& name) {
		return this->operator()(name);
	}
	auto begin() {
		return index.begin();
	}
	auto end() {
		return index.end();
	}
	bool exist(const NameType& name) {
		return index.count(name);
	}
};
}