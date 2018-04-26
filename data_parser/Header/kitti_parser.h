#pragma once
#include <vector>
#include <fstream>
#include <iostream>

#include "base_parser.h"
#include "pc_struct.h"

namespace Parsers {

	char  const * const KITTI_PC_PATH = "velodyne_points/data/";
	char  const * const KITTI_FILE_NAME_BASE = "0000000000";

	const unsigned PC_VEC_RESERVE_COUNT = 100000u;

	class KittiParser : public Parser
	{
	public:
		KittiParser() :Parser() 
		{}
		~KittiParser(){}

		void readFiles(std::vector<std::vector<KittiPoint> >& pointClouds,int maxCount = 0)
		{
			if (m_dataPath == "" || m_dataPath.empty())
			{
			//LOG	
			}
			pointClouds.clear();
			//std::vector<std::vector<KittiPoint> > pointClouds;
			std::ifstream file;
			std::string   filePath;
			unsigned int  fileCounter = 1;
			filePath = m_dataPath +
				       std::string(KITTI_PC_PATH) + 
				       toKittyFileName(fileCounter) + 
				       std::string(".txt");

			file.open(filePath, std::ios::in);
		
			unsigned int maxCount_ = static_cast<unsigned int>(maxCount);
			while (file.is_open() && fileCounter < maxCount_)
			{
				std::vector<KittiPoint> kittiPoints;
				readPointsFromCharFileStream(file,kittiPoints);
				pointClouds.push_back(kittiPoints);
				file.close();
				fileCounter++;

				std::cout << fileCounter << std::endl;

				filePath = m_dataPath +
					std::string(KITTI_PC_PATH) +
					toKittyFileName(fileCounter) +
					std::string(".txt");
				file.open(filePath);

			}

			//return pointClouds;
		};


	protected:
		void parse() override
		{	
		}

	private:
		std::string toKittyFileName(int num)
		{
			std::string s = std::to_string(num);
			std::string r = KITTI_FILE_NAME_BASE;
			for (auto itr = r.end() - 1, its = s.begin(); 
				itr!=r.begin() && its!=s.end(); 
				itr--,its++)
			{
				*itr = *its;
			}
			return r;
		}

		void readPointsFromCharFileStream(std::ifstream & file, 
			std::vector<KittiPoint>& kittiPoints)
		{
			kittiPoints.clear();
			kittiPoints.reserve(PC_VEC_RESERVE_COUNT);
			KittiPoint kittiPoint;

			std::string strX;
			std::string strY;
			std::string strZ;
			std::string strIntensity;
		
			while (!file.eof())
			{
				file >> strX;
				file >> strY;
				file >> strZ;
				file >> strIntensity;
				if (strX == "" ||
					strY == "" ||
					strZ == "" ||
					strIntensity == "") 
				{
					return;
				}

				kittiPoint.x = std::stof(strX);
				kittiPoint.y = std::stof(strY);
				kittiPoint.z = std::stof(strZ);
				kittiPoint.intensity = std::stof(strIntensity);

				kittiPoints.push_back(kittiPoint);
			}
		}
	};

}
