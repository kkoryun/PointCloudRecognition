#pragma once

	class BasePoint
	{
	public:
		BasePoint()
		{
			x = y = z = 0;
		}
		virtual ~BasePoint(){}
		float operator[](int index)
		{
			if (index >= 3) 
			{
				//error
				
			}
			switch (index)
			{
			case 0: {return x; break;}
			case 1: {return y; break;}
			case 2: {return z; break;}
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
		KittiPoint(): BasePoint(){}

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
		return{ min,max };
	}

	void findPointInBound(const std::vector<KittiPoint>& points,  std::vector<BasePoint>& boundPoints,
		BasePoint min,BasePoint max)
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



    void matches(std::vector<BasePoint>& object, std::vector<BasePoint>& odesc, 
                 std::vector<BasePoint>& scene, std::vector<BasePoint>& sdesc ,
                 std::vector<BasePoint>& match
        )
    {
        for (size_t i = 0; i < object.size(); i++)
        {
            for (size_t j = 0; j < scene.size(); j++)
            {
                //if()
            }
        }
    }