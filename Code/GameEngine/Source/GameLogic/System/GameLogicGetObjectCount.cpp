// cl: /DNDEBUG /MD /EHsc
//
// ?getObjectCount@GameLogic@@QAEIXZ @0x0023CFCE, 22B.
// GameLogic::getObjectCount. Counts world objects by walking the object list:
// head at GameLogic+0xAC (rowed getFirstObject), next at Object+0x8C.
// Donor: BFME1 GameLogic::getObjectCount
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/System/GameLogic.cpp:7335).
// Callers 0x00048DAE and 0x00247BDF (which passes ebx=edi-0xC, head at +0xAC).
// Flags from rowed GameLogic sibling GameLogic_getFirstObject.cpp.

typedef unsigned int UnsignedInt;

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/Thing/thing.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };
class Module;
class Drawable;
class Player;

class Object : public Thing, public Snapshot
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType key) const {return findModule(key);}
	bool isMassSelectable() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
	void friend_bindToDrawable( Drawable *draw );
	void rva0028B31A(int val);
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }

	char m_pad64[0x74 - 0x64];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
};

// ?getFirstObject@GameLogic@@QAEPAVObject@@XZ @0x0023CAD2, 7B: the object list head.
Object *GameLogic::getFirstObject()
{
	return m_firstObject;
}

UnsignedInt GameLogic::getObjectCount()
{
	UnsignedInt totalObjects = 0;
	Object *obj;
	for (obj = m_firstObject; obj; obj = obj->getNextObject()) {
		++totalObjects;
	}
	return totalObjects;
}
