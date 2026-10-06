// cl: /MD
// ?removeAllInfluence@PropagandaTowerBehavior@@MAEXXZ @0x00481D4C (88B):
// vtable slot 13 (offset 0x34) of 0x00849248 (class of ??1Rva0048180C@@UAE@XZ,
// PropagandaTowerBehavior via pool string and name getter 0x0048182C).
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehaviorRemoveAllInfluence.cpp
// (same two-phase shape: findObjectByID + effectLogic(false) loop, then delete list).
// Slot 15 (0x3C) callee is effectLogic 0x00481A9E; slot 14 is doScan 0x00481DA4.
// No callers. Layout: ModuleData at +4, m_insideList at +0x28 (matches xfer 0x00481842
// and doScan tail). ::delete reproduces retail push-0 + operator-delete split.

class Object;
class PropagandaTowerBehaviorModuleData;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ObjectTracker
{
public:
	virtual ~ObjectTracker();
	ObjectID objectID;
	ObjectTracker *next;
};

class PropagandaTowerBehavior
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
protected:
	virtual void removeAllInfluence();
	virtual void doScan();
	virtual void effectLogic(Object *obj, bool giving, const PropagandaTowerBehaviorModuleData *modData);
private:
	const PropagandaTowerBehaviorModuleData *m_moduleData;
	unsigned char m_pad08[0x20];
	ObjectTracker *m_insideList;
};

void PropagandaTowerBehavior::removeAllInfluence()
{
	for (ObjectTracker *cur = m_insideList; cur; cur = cur->next)
	{
		Object *obj = TheGameLogic->findObjectByID(cur->objectID);
		if (obj)
			effectLogic(obj, false, m_moduleData);
	}
	while (m_insideList)
	{
		ObjectTracker *next = m_insideList->next;
		::delete m_insideList;
		m_insideList = next;
	}
}
