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

class Object
{
public:
	Object *getNextObject() { return m_next; }

private:
	char m_pad[0x8C];
	Object *m_next; // +0x8C
};

class GameLogic
{
public:
	UnsignedInt getObjectCount();
	Object *getFirstObject() { return m_firstObject; }

private:
	unsigned char m_pad[0xAC];
	Object *m_firstObject; // +0xAC
};

UnsignedInt GameLogic::getObjectCount()
{
	UnsignedInt totalObjects = 0;
	Object *obj;
	for (obj = getFirstObject(); obj; obj = obj->getNextObject()) {
		++totalObjects;
	}
	return totalObjects;
}
