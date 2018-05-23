#pragma once 

#include <vector>
#include <map>
#include <algorithm>

#include "pc_struct.h"

class NormalsEstimator
{
public:
    NormalsEstimator() {}
    void calculate(std::vector<BasePoint> & points, std::vector<std::vector<float>> & desc)
    {
        desc.clear();
        std::vector< std::vector<BasePoint> > nearests;
        findKNearests(points, nearests, 10);

        //std::vector<BasePoint> pointsNormals;
        auto itn = nearests.begin();
        for (auto itp = points.begin(); itp != points.end(), itn != nearests.end(); itp++, itn++)
        {
            desc.push_back(calculatePointNormalDesc(*itp, *itn));
        }

        //for (auto it = points.begin(); it != points.end(); it++)
        //{
        //	std::vector<BasePoint> pointsNormals;
        //	std::vector<std::vector<BasePoint> > near;
        //
        //	findKNearests(points, near, 10);
        //	nearests.push_back(near);
        //	//pointsNormals.push_back(calculatePointNormal(*it, findKnearest(*it,10)));
        //	std::cout << ".";
        //}
        int a = 1;

    }

    std::vector<float> calculatePointNormalDesc(BasePoint point, std::vector<BasePoint> & locality)
    {
        BasePoint pointNormal;
        std::vector<BasePoint> nearests;
        findNearests(locality, nearests);

        std::vector<float> desc;
        std::vector<BasePoint> pointsNormals(locality.size());

        int i = 0;
        for (auto it1 = locality.begin(), it2 = nearests.begin();
            it1 != locality.end(), it2 != nearests.end(), i < locality.size();
            it2++, it1++, i++)
        {
            BasePoint v1;
            v1.x = point.x - it1->x;
            v1.y = point.y - it1->y;
            v1.z = point.z - it1->z;

            BasePoint nearest = *it2;
            BasePoint v2;
            v2.x = nearest.x - it1->x;
            v2.y = nearest.y - it1->y;
            v2.z = nearest.z - it1->z;

            BasePoint normal;
            normal.x = (v1.y * v2.z) - (v1.z*v2.y);
            normal.y = (v1.z*v2.x) - (v1.x*v2.z);
            normal.z = (v1.x*v2.y) - (v1.y*v2.x);

            //pointsNormals[i].x += normal.x;
            //pointsNormals[i].y += normal.y;
            //pointsNormals[i].z += normal.z;

            for (size_t i = 0; i < locality.size(); i++)
            {
                if (locality[i] == *it1 || locality[i] == *it2)
                {
                    pointsNormals[i].x += normal.x;
                    pointsNormals[i].y += normal.y;
                    pointsNormals[i].z += normal.z;
                }
            }

            //float norm = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
            //normal.x /= norm;
            //normal.y /= norm;
            //normal.z /= norm;

            pointNormal.x += normal.x;
            pointNormal.y += normal.y;
            pointNormal.z += normal.z;
        }

        osg::Vec3 v(pointNormal.x, pointNormal.y, pointNormal.z);
        v.normalize();

        for (auto it = pointsNormals.begin(); it != pointsNormals.end(); it++)
        {
            osg::Vec3 vec(it->x, it->y, it->z);
            vec.normalize();
            desc.push_back(vec*v);
        }


        return desc;
    }

private:

    std::map<BasePoint, BasePoint> m_normals;

    void findNearests(std::vector<BasePoint> & locality, std::vector<BasePoint> & nearests)
    {
        nearests.push_back(*(locality.end() - 1));
        for (auto it = locality.begin() + 1; it != locality.end(); it++)
        {
            nearests.push_back(*locality.begin());
        }

        for (auto it = locality.begin(), itn = nearests.begin(); it != locality.end(), itn != nearests.end(); it++, itn++)
        {
            for (auto itl = locality.begin(); itl != locality.end(); itl++)
            {
                if (*it != *itl)
                {
                    if (L2(*it, *itl) < L2(*it, *itn))
                    {
                        *itn = *itl;
                    }
                }
            }
        }
    }

    void findKNearests(std::vector<BasePoint> & locality, std::vector<std::vector<BasePoint> > & nearests, int k)
    {
        for (auto it : locality)
        {
            std::vector<std::pair<float, std::vector<BasePoint>::iterator> > dist;
            for (auto itl = locality.begin(); itl != locality.end(); itl++)
            {
                dist.push_back(std::pair<float, std::vector<BasePoint>::iterator>(L2(it, *itl), itl));
            }
            std::sort(dist.begin(), dist.end(), [](std::pair<float, std::vector<BasePoint>::iterator> p1, std::pair<float, std::vector<BasePoint>::iterator> p2)
            {
                return p1.first < p2.first;
            });
            std::vector<BasePoint> n;
            for (size_t i = 1; i < k + 1; i++)
            {
                n.push_back(*dist[i].second);
            }
            nearests.push_back(n);
            std::cout << ".";
        }
    }

    float L2(BasePoint p1, BasePoint p2)
    {
        float x = p1.x - p2.x;
        float y = p1.y - p2.y;
        float z = p1.z - p2.z;
        return sqrtf(x*x + y * y + z * z);
        //return x*x + y*y + z*z;
    }
};

