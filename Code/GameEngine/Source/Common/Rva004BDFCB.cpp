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

class Player
{
public:
	char m_pad[0x5C];
	int m_field5C;
};

class AIInner
{
public:
	char m_pad[0xC8];
	float m_range;
};

class AI
{
public:
	char m_pad[0x18];
	AIInner *m_inner;
};
extern AI *TheAI;

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

unsigned char __cdecl Rva004BDFCBTest(const Object *a, const Object *b)
{
	if (!b || !a)
		return false;
	if (a->testStatus(OBJ_STATUS_70))
		return false;
	Obj258Inner *t = a->m_field258;
	if (t && t->m_flag != 0)
		return false;
	if ((((unsigned char)(b->m_field94 >> 6)) & 1) != 0)
		return false;
	if (b->getRelationship(a) != REL_SAME)
		return false;
	float dist = a->rva00263763(b);
	float range = TheAI->m_inner->m_range;
	float rangeSq = range * range;
	if (dist > rangeSq)
		return false;
	Player *pl = a->getControllingPlayer();
	return pl->m_field5C == 0;
}
