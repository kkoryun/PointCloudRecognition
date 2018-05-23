#pragma once 

#include <map>

#include <osgGA/GUIEventHandler>

using namespace osgGA;

class UserEventHandler: public osgGA::GUIEventHandler
{
public:
    UserEventHandler(): GUIEventHandler()
    {
        osgKeyToKey();
    }

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override
    {
        if (ea.getEventType() == GUIEventAdapter::EventType::KEYDOWN
            //|| ea.getEventType() == GUIEventAdapter::EventType::KEYUP
            )
        {
            if (keyMap.find(ea.getKey()) != keyMap.end())
            {
                m_keyBoardHandler(keyMap[ea.getKey()]);
            }
        }

        return false;
    }

    void setKeyBoardHandler(std::function<void(int)> keyBoardHandler)
    {
        m_keyBoardHandler = keyBoardHandler;
        osgKeyToKey();
    }

    ~UserEventHandler() = default;



    virtual void osgKeyToKey()
    {
        keyMap[GUIEventAdapter::KeySymbol::KEY_Left] = 89;
        keyMap[GUIEventAdapter::KeySymbol::KEY_Right] = 79;
        keyMap[GUIEventAdapter::KeySymbol::KEY_Up] = 83;
        keyMap[GUIEventAdapter::KeySymbol::KEY_Down] = 84;
        keyMap[GUIEventAdapter::KeySymbol::KEY_B] = 50;
    }
protected:
    std::map<int, int> keyMap;
private:
    std::function<void(int)> m_keyBoardHandler;
};

class PickHandler: public osgGA::GUIEventHandler
{
public:
    virtual bool handle(const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
    {
        if (ea.getEventType() != osgGA::GUIEventAdapter::RELEASE
            || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON
            || !(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL))
            return false;
        osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);
        if (viewer)
        {
            osg::ref_ptr<osgUtil::LineSegmentIntersector>
                intersector = new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());

            osgUtil::IntersectionVisitor iv(intersector.get());
            viewer->getCamera()->accept(iv);
            if (intersector->containsIntersections())
            {
                //osgUtil::LineSegmentIntersector::Intersection& result = *(intersector->getIntersections().begin());
                auto interseptions = intersector->getIntersections();
                for (auto it = interseptions.begin(); it != interseptions.end(); it++)
                {
                    auto p = it->getLocalIntersectPoint();
                    m_intersectHandler(p);
                }
            }
        }
        return false;
    }
    void setIntersectHandler(std::function<void(osg::Vec3d)> intersectHandler)
    {
        m_intersectHandler = intersectHandler;
    }
private:
    std::function<void(osg::Vec3d)> m_intersectHandler;
};
