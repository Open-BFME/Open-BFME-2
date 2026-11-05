// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?Rva004BDFCBTest@@YAEPBVObject@@0@Z @0x004BDFCB 139B
// Two Object* null-checked, status/relationship/range/player checks.
// Honest address name.

enum ObjectStatusTypes
{
	OBJ_STATUS_70 = 0x46
};

enum Relationship
{
	REL_SAME = 0
};

#include "../../Include/Common/Player.h"

#include "../../Include/GameLogic/TAiData.h"
#include "../../Include/GameLogic/AI.h"

class Obj258Inner
{
public:
	char m_pad[0x34];
	int m_flag;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	Relationship getRelationship(const Object *other) const;
	float rva00263763(const void *other) const;
	Player *getControllingPlayer() const;

	char m_pad0[0x94];
	unsigned int m_field94;
	char m_pad94[0x258 - 0x94 - 4];
	Obj258Inner *m_field258;
};

unsigned char __cdecl Rva004BDFCBTest(const Object *object, const Object *b)
{
	if (!b || !object)
		return false;
	if (object->testStatus(OBJ_STATUS_70))
		return false;
	Obj258Inner *obj258Inner = object->m_field258;
	if (obj258Inner && obj258Inner->m_flag != 0)
		return false;
	if ((((unsigned char)(b->m_field94 >> 6)) & 1) != 0)
		return false;
	if (b->getRelationship(object) != REL_SAME)
		return false;
	float dist = object->rva00263763(b);
	float range = TheAI->m_aiData->m_maxRetaliateDistance;
	float rangeSq = range * range;
	if (dist > rangeSq)
		return false;
	Player *pl = object->getControllingPlayer();
	return pl->m_playerType == 0;
}
