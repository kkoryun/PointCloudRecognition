#pragma once


#include <vector>
#include <algorithm>

#include "pc_struct.h"

/*
template<class Key, class Value>
class node {
public:
    Key k;
    Value v;
    char id;
};

class kdTreeNode : public node<int, std::pair<kdTreeNode, kdTreeNode>>
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
*/

template<class Type, unsigned mod = 1>
class Crementor
{
public:
    Crementor():value(0)
    {}

    Crementor& operator++()
    {
        try
        {
            value++;
            value = value % mod;
        }
        catch(const std::exception& e)
        {

        }
        return *this;
    }

    /*   Crementor operator++(int)
       {

           return *this;
       }*/
protected:
    Type value;
};

//template<unsigned mod = 1>
//using NodeLevelType = Crementor<unsigned, mod>;

//NodeLevelType<3> level;
Crementor<unsigned, 3> level;

//level++;

class Node
{
public:
    Node()
    {
        m_left = nullptr;
        m_right = nullptr;
        m_level = -1;
    }
    virtual ~Node() = default;

    Node* m_left;
    Node* m_right;

    //TODO add cycle group with mod 
    int m_level;

};

template<class dataType>
class DataNode: public Node
{
public:
    DataNode(): Node() {};
    virtual ~DataNode() = default;
    dataType m_data;
};


template<class pointType>
class KdTreeNode: public DataNode<pointType>
{
public:
    KdTreeNode(pointType point, int level = -1):DataNode<pointType>()
    {
        m_data = point;
        m_level = level;
    };
private:
};

template<class pointType>
class KdTreeLeaf:public DataNode<std::vector<pointType>>
{
public:
    KdTreeLeaf(): DataNode<std::vector<pointType>>() {};
};

enum
{
    X = 0,
    Y = 1,
    Z = 2
};

template<class T>
class KdTree
{
public:
    KdTree()
    {
        X.reserve(100000);
        Y.reserve(100000);
        Z.reserve(100000);
        m_root = nullptr;
    }

    //using T = BasePoint;

    //std::vector<T>::iterator findMedian(std::vector<T>::iterator s , std::vector<T>::iterator e)
    //{
    //  //TODO real algorithm
    //	int size = (e._Ptr - s._Ptr) / sizeof(T);
    //	int median_index = size / 2;
    //	return s += median_index;
    //}

    int findMedian(const std::vector<T>& vector)
    {
        //...
    }

    Node* find(T point)
    {
        Node* node = m_root;
        while(node != nullptr)
        {
            KdTreeNode<T>* n = dynamic_cast<KdTreeNode<T>*>(node);
            if(node->m_left == nullptr && node->m_right == nullptr)
            {
                return node;
            }
            if(point[n->m_level] <= n->m_data[n->m_level])
            {
                if(n->m_left == nullptr) return node;
                node = n->m_left;
            }
            if(point[n->m_level] > n->m_data[n->m_level])
            {
                if(n->m_right == nullptr) return node;
                node = n->m_right;
            }
        }
        return node;
    }

    void insert(const T& point)
    {
        if(m_root == nullptr)
        {
            m_root = new KdTreeNode<T>(point, 0);
            return;
        }

        auto it = find(point);

        if(dynamic_cast<KdTreeLeaf<T>*>(it))
        {
            dynamic_cast<KdTreeLeaf<T>*>(it)->m_data.push_back(point);
        }

        if(dynamic_cast<KdTreeNode<T>*>(it))
        {
            auto node = dynamic_cast<KdTreeNode<T>*>(it);
            int d = node->m_level;
            inc(d);
            if(point[node->m_level] <= node->m_data[node->m_level])
            {
                node->m_left = new KdTreeNode<T>(point, d);
            }
            if(point[node->m_level] > node->m_data[node->m_level])
            {
                node->m_right = new KdTreeNode<T>(point, d);
            }
        }
    }


    void create(const std::vector<BasePoint>& points)
    {

        split_sort(points);

        //auto med = findMedian();
        //root->addLeftChild()

    }

    //TODO bad method need median search 
    void split_sort(const std::vector<BasePoint>& points)
    {
        for(size_t i = 0; i < points.size(); i++)
        {
            X.push_back(points[i].x);
            Y.push_back(points[i].y);
            Z.push_back(points[i].z);
        }

        std::sort(X.begin(), X.end());
        std::sort(Y.begin(), Y.end());
        std::sort(Z.begin(), Z.end());
    }

private:
    void inc(int & d)
    {
        d++;
        d = d % m_depth;
    }

    std::vector<int> X;
    std::vector<int> Y;
    std::vector<int> Z;
    int m_depth = 2;
    Node * m_root;
};
