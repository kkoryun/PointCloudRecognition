#pragma once 

#include <vector>
#include <map>
#include <algorithm>

#include "pc_struct.h"

class NormalsEstimator
{
public:
	NormalsEstimator() {}
	void calculate(std::vector<BasePoint> & points, std::vector<BasePoint> & normals)
	{
		std::vector< std::vector<BasePoint> > nearests;
		findKNearests(points, nearests, 10);

		//std::vector<BasePoint> pointsNormals;
		auto itn = nearests.begin();
		for (auto itp = points.begin(); itp != points.end(),itn!=nearests.end(); itp++,itn++)
		{
			normals.push_back(calculatePointNormal(*itp, *itn));
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
	
	BasePoint calculatePointNormal(BasePoint point, std::vector<BasePoint> & locality)
	{
		BasePoint pointNormal;
		std::vector<BasePoint> nearests;
		findNearests(locality, nearests);

		for (auto it = locality.begin(),i = nearests.begin(); it != locality.end(),i!=nearests.end(); i++,it++)
		{
			BasePoint v1;
			v1.x = point.x - it->x;
			v1.y = point.y - it->y;
			v1.z = point.z - it->z;

			BasePoint nearest = *i;
			BasePoint v2;
			v2.x = nearest.x - it->x;
			v2.y = nearest.y - it->y;
			v2.z = nearest.z - it->z;

			BasePoint normal;
			normal.x = (v1.y * v2.z) - (v1.z*v2.y);
			normal.y = (v1.z*v2.x) - (v1.x*v2.z);
			normal.z = (v1.x*v2.y) - (v1.y*v2.x);

			//float norm = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
			//normal.x /= norm;
			//normal.y /= norm;
			//normal.z /= norm;

			pointNormal.x += normal.x;
			pointNormal.y += normal.y;
			pointNormal.z += normal.z;
		}
		return pointNormal;
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
				if ( *it != *itl)
				{
					if (L2(*it, *itl) < L2(*it,*itn ))
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
				dist.push_back(std::pair<float,std::vector<BasePoint>::iterator>(L2(it, *itl), itl));
			}
			std::sort(dist.begin(), dist.end(), [](std::pair<float, std::vector<BasePoint>::iterator> p1, std::pair<float, std::vector<BasePoint>::iterator> p2)
			{
				return p1.first < p2.first;
			});
			std::vector<BasePoint> n;
			for (size_t i = 1; i < k+1; i++)
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
		//return sqrtf(x*x + y*y + z*z);
		return x*x + y*y + z*z;
	}
};

