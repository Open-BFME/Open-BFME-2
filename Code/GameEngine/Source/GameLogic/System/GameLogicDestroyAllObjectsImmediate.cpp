// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// GameLogic::destroyAllObjectsImmediate, retail 0x00243B52 (78B), from the
// WorldBuilder lead (name, statement order) and Zero Hour's GameLogic.cpp.
// BFME2 first clears the pending destroy list (+0x164, erased through the
// shared out-of-line vector erase 0x0031BD55), walks the object list (+0xAC,
// next at Object +0x8C) destroying each object, processes the destroy list
// (0x002413DF) and finally lets TheGameClient reset through its vtable slot
// 0x90. The destroy-list element type is not established; it keeps an
// address-derived name.

#include <vector>

class Object
{
public:
	Object *getNextObject() const { return m_next; }
	void rva00295F05(bool flags);

private:
	unsigned char m_pad00[0x8C];
	Object *m_next;
};

struct Rva00243B52DestroyEntry;

class GameClient
{
public:
#define CLIENT_SLOT(n) virtual void slot##n();
	CLIENT_SLOT(0) CLIENT_SLOT(1) CLIENT_SLOT(2) CLIENT_SLOT(3) CLIENT_SLOT(4) CLIENT_SLOT(5)
	CLIENT_SLOT(6) CLIENT_SLOT(7) CLIENT_SLOT(8) CLIENT_SLOT(9) CLIENT_SLOT(10) CLIENT_SLOT(11)
	CLIENT_SLOT(12) CLIENT_SLOT(13) CLIENT_SLOT(14) CLIENT_SLOT(15) CLIENT_SLOT(16) CLIENT_SLOT(17)
	CLIENT_SLOT(18) CLIENT_SLOT(19) CLIENT_SLOT(20) CLIENT_SLOT(21) CLIENT_SLOT(22) CLIENT_SLOT(23)
	CLIENT_SLOT(24) CLIENT_SLOT(25) CLIENT_SLOT(26) CLIENT_SLOT(27) CLIENT_SLOT(28) CLIENT_SLOT(29)
	CLIENT_SLOT(30) CLIENT_SLOT(31) CLIENT_SLOT(32) CLIENT_SLOT(33) CLIENT_SLOT(34) CLIENT_SLOT(35)
#undef CLIENT_SLOT
	virtual void slot36(); // 0x90
};
extern GameClient *TheGameClient;

class GameLogic
{
public:
	void destroyAllObjectsImmediate();
	void rva00240EBC();
	void destroyObject(Object *obj);
	void processDestroyList();

private:
	unsigned char m_pad00[0xAC];
	Object *m_objList;
	unsigned char m_padB0[0x164 - 0xB0];
	_STL::vector<Rva00243B52DestroyEntry *> m_objectsToDestroy;
};

void GameLogic::destroyAllObjectsImmediate()
{
	m_objectsToDestroy.clear();
	Object *obj;
	Object *nextObj;
	for (obj = m_objList; obj; obj = nextObj) {
		nextObj = obj->getNextObject();
		destroyObject(obj);
	}
	processDestroyList();
	if (TheGameClient)
		TheGameClient->slot36();
}

// ?rva00240EBC@GameLogic@@QAEXXZ @ 0x00240EBC (51B): retail walks the
// pending-object vector at +0x164/+0x168 calling Object::rva00295F05(1),
// then erases its range through the existing vector helper at 0x0031BD55.
// The neighboring GameLogic body supports the owner and field layout; exact
// method purpose remains address-derived.
void GameLogic::rva00240EBC()
{
	for (Rva00243B52DestroyEntry **entry = m_objectsToDestroy.begin();
		 entry != m_objectsToDestroy.end(); ++entry) {
		reinterpret_cast<Object *>(*entry)->rva00295F05(1);
	}
	m_objectsToDestroy.clear();
}
