#include "data_parser/Header/kitti_parser.h"

#include "osgViewer/Viewer"
#include "osgGA/TrackballManipulator"
#include "osg/ShapeDrawable"

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>
#include<queue>

#include "scene.h"
#include "userEventHandler.h"
#include "pc_struct.h"
#include "description/normalsEstimation.h"

Scene scene;
std::vector<std::vector<KittiPoint> > data;
std::queue<osg::Vec3d> pointq;
BasePoint P1;
BasePoint P2;

std::vector<std::vector<float>> objectDesc, sceneDesc;
std::vector<BasePoint> objectPC, scenePC;


unsigned int i = 0;

bool tracking = false;

void changeData(int key) {
	if (key == 79)
	{
		i++;
		i %= 3;
		scene.setPointCloud(data[i]);
	}
	if (key == 89)
	{

		i--;
		i %= 3;
		scene.setPointCloud(data[i]);
	}

	if (key == 89 || key == 79)
	{
		auto bound = getDataBound(data[i]);
		scene.setGrid(bound.first, bound.second);

		if (tracking) 
		{
			//std::vector<BasePoint> boundPoints;
			BasePoint p1;
			p1.x = P1.x - 1;
			p1.y = P1.y - 1;
			p1.z = P1.z;
			BasePoint p2;
			p2.x = P2.x + 1;
			p2.y = P2.y + 1;
			p2.z = P2.z;
			findPointInBound(data[i], scenePC, p1, p2);
			NormalsEstimator ne;
			ne.calculate(scenePC, sceneDesc);
            std::vector<int> match;
            matches(objectDesc, sceneDesc, match);
			//scene.setNormals(boundPoints,normals);
            float x = 0, y = 0, z = 0;
            for (size_t i = 0; i < match.size(); i++)
            {
                x += scenePC[match[i]].x;
                y += scenePC[match[i]].y;
                z += scenePC[match[i]].z;
            }

            BasePoint p;
            p.x = x;
            p.y = y;
            p.z = z;

            
		}
	}

	if (key == 50) 
	{
		if (pointq.size() < 2) return;
		auto p1 = pointq.front();
		pointq.pop();
		auto p2 = pointq.front();
		pointq.pop();

		scene.setBox(p1, p2 + osg::Vec3d(0, 0, 2));
		P1.x = p1.x();
		P1.y = p1.y();
		P1.z = p1.z();
		P2.x = p2.x();
		P2.y = p2.y();
		P2.z = p2.z();
		
		findPointInBound(data[i], objectPC, P1, P2);
     
		NormalsEstimator ne;
		ne.calculate(objectPC, objectDesc);
		tracking = true;
	}
}

void intersectHandler(osg::Vec3d v) 
{
	std::cout << v.x() << " " << v.y() << " " << v.z() << " " << std::endl;
	pointq.push(v);
}

void setting(osgViewer::Viewer & viewer)
{
	viewer.setUpViewInWindow(0, 0, 800, 800);
	viewer.setCameraManipulator(new osgGA::OrbitManipulator);

	UserEventHandler* ueh = new UserEventHandler;
	ueh->setKeyBoardHandler(changeData);
	viewer.addEventHandler(ueh);
	
	PickHandler* ph = new PickHandler;
	ph->setIntersectHandler(intersectHandler);
	viewer.addEventHandler(ph);
	

}

int main()
{
	//std::string KITTI_DATA_PATH = "C:/Project/2011_09_26_drive_0001_extract/2011_09_26/2011_09_26_drive_0001_extract";
    
    std::string KITTI_DATA_PATH = "F:/resource/KITTI/2011_09_26_drive_0001_extract/2011_09_26/2011_09_26_drive_0001_extract";

    Parsers::KittiParser kittiParser;
	kittiParser.setFilePath(KITTI_DATA_PATH);

	
	kittiParser.readFiles(data, 4);
	
	osgViewer::Viewer viewer;
	setting(viewer);

	//scene.addPointCloud(data[0]);
	
    viewer.setSceneData(scene.getRoot().get());
	return viewer.run();
	
	return 0;
}
