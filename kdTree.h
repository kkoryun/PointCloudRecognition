#pragma once

#include <vector>

#include "pc_struct.h"


template<class Key, class Value>
class node {
public:
	Key k;
	Value v;
	char id;
};


class kdTreeNode : public node<int, std::pair<kdTreeNode,kdTreeNode>>
{
public:
	kdTreeNode();
	~kdTreeNode();

private:
	
};

class kdTreeLeaf : public node<int, std::vector<BasePoint>>
{
public:
	kdTreeLeaf();

private:

};


class kdTree
{
public:
	kdTree();

	void create(std::vector<BasePoint> p) {

	}

private:
	kdTreeNode* root;
};
