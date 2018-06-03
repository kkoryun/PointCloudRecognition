#pragma once
#include <vector>
#include <limits>
using namespace std;
class BasePoint
{
public:
    BasePoint():
        x(0),
        y(0),
        z(0)
    {}
    virtual ~BasePoint() = default;
    float operator[](int index)
    {
        if (index >= 3)
        {
            //error

        }

        switch (index)
        {
        case 0: { return x; break; }
        case 1: { return y; break; }
        case 2: { return z; break; }
        default:
            break;
        }
        return 0;
    }

    bool operator==(BasePoint point)
    {
        return (x == point.x
            && y == point.y
            && z == point.z);
    }

    bool operator!=(BasePoint point)
    {
        return !(*this == point);
    }

public:
    float x;
    float y;
    float z;
};

class KittiPoint: public BasePoint
{
public:
    KittiPoint(): BasePoint() {}

public:
    float intensity;
};

std::pair<BasePoint, BasePoint> getDataBound(const std::vector<KittiPoint>& points)
{
    BasePoint min, max;
    BasePoint point = *points.begin();
    min.x = max.x = point.x;
    min.y = max.y = point.y;
    min.z = max.z = point.z;
    for (auto it = points.begin(); it != points.end(); it++)
    {
        if (it->x < min.x) min.x = it->x;
        if (it->y < min.y) min.y = it->y;
        if (it->z < min.z) min.z = it->z;

        if (it->x > max.x) max.x = it->x;
        if (it->y > max.y) max.y = it->y;
        if (it->z > max.z) max.z = it->z;
    }
    return{min,max};
}


void findPointInBound(const std::vector<KittiPoint>& points, std::vector<BasePoint>& boundPoints,
    BasePoint min, BasePoint max)
{
    boundPoints.clear();
    for (auto it = points.begin(); it != points.end(); it++)
    {
        if (it->x > min.x && it->y > min.y && it->z > min.z
            && it->x < max.x && it->y > max.y && it->z > max.z)
        {
            //if (rand() % 5 == 0)
            boundPoints.push_back(*it);
        }
    }

}


float diff(std::vector<float> v1, std::vector<float> v2)
{
    if (v1.size() != v2.size())
        return 0;
    std::vector<float> res(v1.size());
    for (size_t i = 0; i < v1.size(); i++)
    {
        res[i] = v1[i] - v2[i];
    }
    float sum = 0;

    for (size_t i = 0; i < res.size(); i++)
    {
        sum += res[i] * res[i];
    }

    return sqrt(sum);
}

void matches(std::vector<std::vector<float>>& odesc, std::vector<std::vector<float>>& sdesc,
    std::vector<int>& match)
{
    for (size_t i = 0; i < odesc.size(); i++)
    {
        match.push_back(-1);
    }
    std::vector<float> dist(odesc.size());
    for (size_t i = 0; i < odesc.size(); i++)
    {
        dist[i] = 100000000;//numeric_limits<float>().max();
    }

    for (size_t i = 0; i < odesc.size(); i++)
    {
        for (size_t j = 0; j < sdesc.size(); j++)
        {
            if (diff(odesc[i], sdesc[j]) < dist[i])
            {
                match[i] = j;
            }
        }
    }
}

