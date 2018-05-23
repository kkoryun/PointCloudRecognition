#pragma once

#include <memory>

#include "osg/Group"
#include "pc_struct.h"
#include "osg/MatrixTransform"
#include "osg/Geode"
#include "osg/Geometry"
#include "osg/PrimitiveSet"
#include "osgManipulator/TabBoxDragger"

using namespace osg;
class SceneItem
{
public:
	SceneItem()
	{
		m_geode = new Geode;
		m_transformMatrix = new MatrixTransform;
		m_transformMatrix->addChild(m_geode.get());
	}

	osg::ref_ptr<osg::MatrixTransform> getRoot() const 
	{
		return m_transformMatrix;
	}

	virtual ~SceneItem() = default;
protected:
	osg::ref_ptr<osg::MatrixTransform> m_transformMatrix;
	osg::ref_ptr<osg::Geode> m_geode;
};

class PointCloudSceneItem : public SceneItem
{
public:
	PointCloudSceneItem(): SceneItem()
	{
		m_geometry = new Geometry;
		m_geode->addDrawable(m_geometry.get());
	}
	void create(const std::vector<KittiPoint> & data) 
	{
		ref_ptr<Vec3Array> vertices = new Vec3Array;

		ref_ptr<Vec3Array> colors = new Vec3Array;


		vertices->reserve(data.size());
		for (auto it = data.begin(); it != data.end(); it++)
		{			
			vertices->push_back(Vec3(it->x, it->y, it->z));
		}

		colors->push_back(Vec3(0, 0, 0));
	
		m_geometry->setVertexArray(vertices.get());
		m_geometry->setColorArray(colors.get(),Array::BIND_OVERALL);
		m_geometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::POINTS, 0, vertices->size()));
	}

protected:
	osg::ref_ptr<osg::Geometry> m_geometry;
};

class BoxSceneItem : public SceneItem {
public:
	BoxSceneItem() :SceneItem() 
	{
		//m_geometry = new Geometry;
		//m_geometry->getOrCreateStateSet()->setMode(
			//GL_LIGHTING, osg::StateAttribute::OFF);
		//m_geode->addDrawable(m_geometry.get());
	}

	void create(osg::Vec3 p1,osg::Vec3 p2) 
	{
		m_p1 = p1;
		m_p2 = p2;
		m_dragger = new osgManipulator::TabBoxDragger();
		m_dragger->setupDefaultGeometry();
		m_dragger->setActivationKeyEvent('s');
		m_dragger->setHandleEvents(true);
		m_transformMatrix->addChild(m_dragger);
		Vec3 scale(abs(p1.x() - p2.x()), abs(p1.y() - p2.y()), abs(p1.z() - p2.z()));
		Vec3 translate(p1 + (p2 - p1) * 0.5);
		m_dragger->setMatrix(Matrix::scale(scale) * Matrix::translate(translate));
	}

    
//private:
	osg::Vec3 m_p1, m_p2;
	osg::ref_ptr<osgManipulator::TabBoxDragger> m_dragger;
	//osg::ref_ptr<osg::Geometry> m_geometry;
};

class GridSceneItem: public SceneItem
{
public:
	GridSceneItem() :SceneItem() 
	{
		m_geometry = new Geometry;
		m_geometry->getOrCreateStateSet()->setMode(
			GL_LIGHTING, osg::StateAttribute::OFF);
		m_geode->addDrawable(m_geometry.get());
	};

	void create(BasePoint min, BasePoint max )
	{
		m_min = min;
		m_max = max;

		ref_ptr<Vec3Array> vertices = new Vec3Array;
		ref_ptr<Vec4Array> colors = new Vec4Array;
		float z;
		if (min.z <= max.z) z = min.z;
		if (min.z > max.z) z = max.z;
		z = -2.;
		vertices->push_back(Vec3(m_min.x, m_min.y, z));
		vertices->push_back(Vec3(m_max.x, m_min.y, z));
		vertices->push_back(Vec3(m_max.x, m_max.y, z));
		vertices->push_back(Vec3(m_min.x, m_max.y, z));
		
		
		//vertices->push_back(Vec3(m_min.x, m_min.y, 0));
		colors->push_back(Vec4(0.727450991, 0.727450991, 0.727450991, 0.5));

		m_geometry->setVertexArray(vertices.get());
		m_geometry->setColorArray(colors.get(), Array::BIND_OVERALL);
		m_geometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS, 0, vertices->size()));

	}
protected:
	BasePoint m_min, m_max;

	osg::ref_ptr<osg::Geometry> m_geometry;
};

class PointsNormalsItem : public SceneItem{
public:
    PointsNormalsItem(): SceneItem()
    {
        m_geometry = new Geometry;
        m_geometry->getOrCreateStateSet()->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
        m_geode->addDrawable(m_geometry.get());
    };

    void create(const std::vector<BasePoint> & points, const std::vector<BasePoint> & normals)
    {
        ref_ptr<Vec3Array> vertices = new Vec3Array;

        ref_ptr<Vec3Array> colors = new Vec3Array;


        vertices->reserve(points.size());
        vertices->reserve(points.size());
        for (auto p_it = points.begin(), n_it = normals.begin(); 
            p_it != points.end() || n_it != normals.end();
            p_it++, n_it++)
        {
            vertices->push_back(Vec3(p_it->x, p_it->y, p_it->z));
            vertices->push_back(Vec3(p_it->x + n_it->x, p_it->y + n_it->y, p_it->z + n_it->z));
        }

        colors->push_back(Vec3(1.f, 0, 0));

        m_geometry->setVertexArray(vertices.get());
        m_geometry->setColorArray(colors.get(), Array::BIND_OVERALL);
        m_geometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, vertices->size()));
    }
protected:

    osg::ref_ptr<osg::Geometry> m_geometry;
};

class Scene
{
public:
	Scene() 
	{
		m_root = new Group;
		m_pointCloud = std::shared_ptr<PointCloudSceneItem>(new PointCloudSceneItem);
		m_grid = std::shared_ptr<GridSceneItem>(new GridSceneItem);
		m_box = std::shared_ptr<BoxSceneItem>(new BoxSceneItem);
        m_normals = std::shared_ptr<PointsNormalsItem>(new PointsNormalsItem);
		m_root->addChild(m_pointCloud->getRoot());
		m_root->addChild(m_grid->getRoot());
		m_root->addChild(m_box->getRoot());
        m_root->addChild(m_normals->getRoot());
	}

	osg::ref_ptr<osg::Group> getRoot() const 
	{
		return m_root;
	}

	void setPointCloud(const std::vector<KittiPoint> & data)
	{
		std::shared_ptr<PointCloudSceneItem> pointCloud = std::shared_ptr<PointCloudSceneItem>(new PointCloudSceneItem);
		pointCloud->create(data);
		m_root->addChild(pointCloud->getRoot());
		m_root->removeChild(m_pointCloud->getRoot());
		m_pointCloud = pointCloud;
	}

	void setGrid(BasePoint min, BasePoint max)
	{
		std::shared_ptr<GridSceneItem> grid = std::shared_ptr<GridSceneItem>(new GridSceneItem);
		grid->create(min, max);
		m_root->addChild(grid->getRoot());
		m_root->removeChild(m_grid->getRoot());
		m_grid = grid;
	}

	void setBox(osg::Vec3 p1, osg::Vec3 p2) 
	{
		std::shared_ptr<BoxSceneItem> box = std::shared_ptr<BoxSceneItem>(new BoxSceneItem);
		box->create(p1,p2);
		m_root->addChild(box->getRoot());
		m_root->removeChild(m_box->getRoot());
		m_box = box;
	}

    void setNormals(const std::vector<BasePoint>& points,const std::vector<BasePoint>& normals)
    {
        std::shared_ptr<PointsNormalsItem> pointsNormals = std::shared_ptr<PointsNormalsItem>(new PointsNormalsItem);
        pointsNormals->create(points, normals);
        m_root->addChild(pointsNormals->getRoot());
        m_root->removeChild(m_normals->getRoot());
        m_normals = pointsNormals;
    }

protected:
    template<class SceneItemType>
    void changeSceneItem(std::shared_ptr<SceneItemType> oldItem)
    {
        std::shared_ptr<SceneItemType> newItem = std::shared_ptr<SceneItemType>(new SceneItemType);
        //item->create();
        m_root->addChild(newItem->getRoot());
        m_root->removeChild(oldItem->getRoot());
        oldItem = newItem;
    }
protected:
	osg::ref_ptr<osg::Group> m_root;
	std::shared_ptr<PointCloudSceneItem> m_pointCloud;
	std::shared_ptr<GridSceneItem> m_grid;
	std::shared_ptr<BoxSceneItem> m_box;
    std::shared_ptr<PointsNormalsItem> m_normals;
};
