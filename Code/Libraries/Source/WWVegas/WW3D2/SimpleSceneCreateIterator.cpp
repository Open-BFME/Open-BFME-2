// cl: /DNDEBUG /MD /EHsc

#include "SimpleSceneClass.h"

// scene.h's four pure iterator slots follow the dtor, as in scene.cpp's copy of
// the table (first in link order).
class SceneIterator
{
public:
	virtual ~SceneIterator() {}
	virtual void First(void) = 0;
	virtual void Next(void) = 0;
	virtual bool Is_Done(void) = 0;
	virtual RenderObjClass *Current_Item(void) = 0;
};

class __declspec(novtable) SimpleSceneIterator : public SceneIterator
{
public:
	virtual ~SimpleSceneIterator() {}
	virtual void First(void);
	virtual void Next(void);
	virtual bool Is_Done(void);
	virtual RenderObjClass *Current_Item(void);

protected:
	SimpleSceneIterator(RefMultiListClass<RenderObjClass> *render_list) :
		m_render_list(render_list),
		m_current(render_list->Head.Next)
	{
	}

private:
	RefMultiListClass<RenderObjClass> *m_render_list;
	void *m_current;

	friend class SimpleSceneClass;
};

SceneIterator *SimpleSceneClass::Create_Iterator()
{
	return new SimpleSceneIterator(&RenderList);
}
