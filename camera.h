#pragma once
#include "osgGA/TrackballManipulator"

using namespace osgGA;
class Camera
{
public:
	Camera() {
		m_camera = new osg::Camera;
		m_manipulator = new osgGA::OrbitManipulator;
	
		m_camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		m_camera->setClearMask(GL_DEPTH_BUFFER_BIT);
		m_camera->setRenderOrder(osg::Camera::POST_RENDER);
		m_camera->setAllowEventFocus(false);
		//m_camera->getProjectionMatrixAsPerspective();
		m_camera->getOrCreateStateSet()->setMode(
			GL_LIGHTING, osg::StateAttribute::OFF);
	}
	~Camera() = default;

private:
	osg::ref_ptr<osgGA::OrbitManipulator> m_manipulator;
	osg::ref_ptr<osg::Camera> m_camera;
};

