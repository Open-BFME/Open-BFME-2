// ?rva004AC722@DestroyEnvironmentUpdate@@QAEXXZ
// partial score=0.97 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva004AC722@DestroyEnvironmentUpdate@@QAEXXZ @0x004AC722 69B.
// Object-id teardown: resolve +0x24, release the attached actor, destroy
// the object, then clear the id. 0x004AC5F5 consumes the object still in eax.

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Actor
{
public:
	virtual void release(float amount);
};

Actor *rva004AC5F5();

class DestroyEnvironmentUpdate
{
public:
	void rva004AC722();

private:
	char m_pad[0x24];
	unsigned int m_objectID;
};

void DestroyEnvironmentUpdate::rva004AC722()
{
	ObjectID id = (ObjectID)m_objectID;
	if (id == 0)
		return;
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj != 0) {
		Actor *actor = rva004AC5F5();
		if (actor != 0) {
			actor->release(0.0f);
			TheGameLogic->destroyObject(obj);
		}
	}
	m_objectID = 0;
}
