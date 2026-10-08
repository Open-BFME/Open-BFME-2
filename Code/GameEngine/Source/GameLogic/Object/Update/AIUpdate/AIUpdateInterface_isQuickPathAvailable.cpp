// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// ?isQuickPathAvailable@AIUpdateInterface@@QBE_NPBUCoord3D@@@Z @0x00264274 234B
// unlock: path test with optional TransportShip locomotor set. Evidence: callers 0x0029DEFB 0x0034859A 0x003EA1FB; callee rows 0x00148E1A 0x001E7087 0x001E6FEA 0x001E88CE pins 0x002F477E 0x001E86D0; neighbours Rva00264237Dist.cpp.
// naming: __thiscall method reading ecx+8, 1 stack arg (ret 4), bool return.
// Identity: WorldBuilder's AIUpdate.cpp:3678 asserts in AIUpdateInterface::isQuickPathAvailable,
// whose body builds the same "TransportShipLocomotorForUnitInteraction" LocomotorSet and calls
// Pathfinder::QuickDoesPathExist (0x002F477E) on both paths; the caller 0x0029DEFB reaches it
// through Object +0x258 (the AI interface). Zero Hour's isQuickPathAvailable is the plain form.
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};
extern NameKeyGenerator *TheNameKeyGenerator;

extern unsigned int g_Va00DFEAE8;
extern int g_00DFEAE4;

class LocomotorTemplate;
class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int key);
};
extern class LocomotorStore *TheLocomotorStore;

class LocomotorSet
{
public:
	void addLocomotor(const LocomotorTemplate *lt, bool flag);
};

class AIUpdateInterface;
class Rva001E7087
{
	friend class AIUpdateInterface;
public:
	Rva001E7087();
protected:
	virtual ~Rva001E7087();
private:
	char _m20[0x20]; // +4..+0x23 total 0x24 with vtable like donor Rva001E7087Ctor
};

class ObjectAux
{
public:
	unsigned char _pad116[0x116];
	unsigned char m_116;
	unsigned char _pad117[0x11F - 0x116 - 1];
	unsigned char m_11F;
};

class Object
{
public:
	void *m_vtable; // +0
	ObjectAux *m_aux; // +4
	char _pad08[0x38 - 8];
	Coord3D m_pos; // +0x38
	char _pad44[0x250 - 0x38 - 12];
	int m_250; // +0x250
};

class Pathfinder;
class AI
{
public:
	char _pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern class AI *TheAI;

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int extra);
};

class AIUpdateInterface
{
public:
	bool isQuickPathAvailable(const Coord3D *destination) const;
private:
	char _pad00[8];
	Object *m_object; // +8
};

bool AIUpdateInterface::isQuickPathAvailable(const Coord3D *destination) const
{
	if (destination == 0)
		return false;
	Object *obj = m_object;
	const Coord3D *from = &obj->m_pos;
	if (obj->m_250 != 0)
	{
		ObjectAux *aux = (ObjectAux *)obj->m_aux;
		if ((aux->m_11F & 0x80) != 0 && (aux->m_116 & 0x40) != 0)
		{
			static NameKeyType s_transportKey = TheNameKeyGenerator->nameToKey("TransportShipLocomotorForUnitInteraction");
			Rva001E7087 set;
			((LocomotorSet *)&set)->addLocomotor(TheLocomotorStore->findLocomotorTemplate(s_transportKey), false);
			AI *ai = TheAI;
			Pathfinder *pf = ai->m_pathfinder;
			return pf->QuickDoesPathExist((Object *)obj, from, destination, (int)&set);
		}
	}
	AI *ai2 = TheAI;
	Pathfinder *pf2 = ai2->m_pathfinder;
	return pf2->QuickDoesPathExist((Object *)obj, from, destination, 0);
}
