#include "data_parser/Header/kitti_parser.h"
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

std::vector<Point>  points = {{2,2}, {2,4}, {0,5}, {4,3},{3,5},{3,8},{5,6},
{6,7},{8,6},{8,4},{8,2},{5,2},{11,6}};
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

template<class T, unsigned mod = 1>
class Mod
{
public:
    Mod(const T& value)
    {
        m_mod = mod;
        m_value = value;
    };

    Mod operator++()
    {
        m_value++;
        m_value = m_value % m_mod;
        return *this;
    }

    operator int()
    {
        return m_value;
    }
private:
    unsigned m_mod;
    T m_value;
};


int main()
{
    Mod<int, 2> d = 0;


    KdTree<Point> kdtree;

    auto med = findMedian(points.begin(), points.end(), d);
    kdtree.insert(*med);


    ++d;
    kdtree.insert(*findMedian(points.begin(), med, d));
    kdtree.insert(*findMedian(med + 1, points.end(), d));


    //std::string KITTI_DATA_PATH = "C:/Project/2011_09_26_drive_0001_extract/2011_09_26/2011_09_26_drive_0001_extract";
    //Parsers::KittiParser kittiParser;
    //kittiParser.setFilePath(KITTI_DATA_PATH);
    ////auto data = kittiParser.readFiles(2);
    //data = kittiParser.readFiles(1);




    return 0;
}