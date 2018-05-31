//#include "../data_parser/Header/kitti_parser.h"
#include "kdTree.h"


class Point
{
public:
    Point(float x_ = 0, float y_ = 0)
    {
        x = x_;
        y = y_;
    }
    virtual ~Point() {}
    float operator[](int index) const
    {
        if (index >= 2)
        {
            //error
            int a = 9;
        }
        switch (index)
        {
        case 0: { return x; break; }
        case 1: { return y; break; }
        default:
            break;
        }
        return 0;
    }
public:
    float x;
    float y;
};

std::vector<Point>  points = {{1,2}, {2,4}, {0,5}, {4,3},{3,6},{3,8},{5,6},
{6,7},{8,6},{8,4},{8,2},{4,2},{11,6},{10,1}};
int cluster_size = 2;

std::vector<Point>::iterator findMedian(std::vector<Point>::iterator s, std::vector<Point>::iterator e, int level)
{
    if (level == 0)
        std::sort(s, e, [](Point p1, Point p2) { return p1.x < p2.x; });
    if (level == 1)
        std::sort(s, e, [](Point p1, Point p2) { return p1.y < p2.y; });


    for (auto it = s; it != e; it++)
    {
        std::cout << (*it).x << " ";
    }
    std::cout << std::endl;
    for (auto it = s; it != e; it++)
    {
        std::cout << (*it).y << " ";
    }
    std::cout << std::endl;

    auto d = e - s;
    return s + d / 2;

}


KdTree<Point> kdtree;
void makeTree(std::vector<Point>::iterator s, std::vector<Point>::iterator e, NodeLevelType<2>& depth)
{

    auto med = findMedian(s, e, depth);
    kdtree.insert(*med);
    depth++;
    if(e - s <= cluster_size)
    {
        return;
    }
    makeTree(s, med, depth);
    makeTree(med+1, e, depth);

}
void walk(Node* n)
{
    if(n->m_left == nullptr && n->m_right == nullptr)
    {
        n = dynamic_cast<KdTreeLeaf<Point>*>(n);
    }
    if(n->m_left != nullptr)
    {
        walk(n->m_left);
    }
    if(n->m_right != nullptr)
    {
        walk(n->m_right);
    }
 
}
void fillTree(std::vector<Point>::iterator s, std::vector<Point>::iterator e)
{
    Node* n = kdtree.getRoot();
    while(n!=nullptr)
    {
        if(n->m_left != nullptr);
    }
}
int main()
{

    NodeLevelType<2> depth;

    makeTree(points.begin(),points.end(),depth);



    ++depth;
    ++depth;
    ++depth;
    
    
    auto med = findMedian(points.begin(), points.end(), depth);
    kdtree.insert(*med);


    ++depth;
    kdtree.insert(*findMedian(points.begin(), med, depth));
    kdtree.insert(*findMedian(med + 1, points.end(), depth));

    int c = 0;
    while(c < points.size()/cluster_size)
    {

        c++;
    }
    //std::string KITTI_DATA_PATH = "C:/Project/2011_09_26_drive_0001_extract/2011_09_26/2011_09_26_drive_0001_extract";
    //Parsers::KittiParser kittiParser;
    //kittiParser.setFilePath(KITTI_DATA_PATH);
    ////auto data = kittiParser.readFiles(2);
    //data = kittiParser.readFiles(1);




    return 0;
}