// ?checkTarget@AITacticOffensive@@QAEEPAX@Z
// partial score=0.75 date=2026-10-07
// cl: /O1 /DNDEBUG /MD
// ?checkTarget@AITacticOffensive@@QAEEPAX@Z retail 0x005DC763, 252 B: WB AITacticOffensive::checkTarget.
// Bank: control flow, calls and offsets follow retail; cl keeps this in a
// frame slot and the reach result in bl where retail keeps this in ebx and the
// result in [ebp-1] (xor with the slot-10 answer). 0x002F4B33 needs a pin.
struct Coord3D { float x, y, z; };
class Player;

class ThingTemplate
{
public:
	unsigned char m_pad[0x108];
	unsigned int m_kindOf108;			// +0x108
	unsigned char m_pad10C[0x120 - 0x10C];
	unsigned int m_kindOf120;			// +0x120
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
	unsigned char m_pad08[0x38 - 8];
	Coord3D m_pos;					// +0x38
	unsigned char m_pad44[0x94 - 0x44];
	unsigned int m_flags94;				// +0x94
	unsigned char m_pad98[0x438 - 0x98];
	unsigned int m_status438;			// +0x438
};

class Pathfinder
{
public:
	bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, int flags);	// 0x002F477E
	bool QuickDoesPathExistToStructure(Object *obj, const Coord3D *from, Object *structure, int flags);	// 0x002F4B33
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad[0x10];
	Pathfinder *m_pathfinder;			// +0x10
};
extern AI *TheAI;

namespace _STL
{
template <class T> struct hash;
template <class T> struct equal_to;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;		// 0x002BEDAB
};
}
typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > Rva005DC763Units;

class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);			// 0x0025BFF8
};

struct Rva002A8AB1Record
{
	unsigned char m_pad[0x16C];
	int m_16C;					// +0x16C
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);		// 0x002A8F24
	Rva002A8AB1Record *rva002A8AB1(void *owner);	// 0x002A8AB1
};
extern Rva002A8F24 *g_00DFEEF8;

// The tactic's target (WorldBuilder AITarget), rowed under a placeholder.
class Rva002C589B
{
public:
	Object *rva002C5DA6();				// 0x002C5DA6
	unsigned char m_pad[0xC];
	Coord3D m_pos;					// +0x0C
};

class AITacticOffensive
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
	virtual bool slot10();				// +0x28

	unsigned char checkTarget(void *target);

private:
	unsigned char m_pad04[0x24 - 4];
	Player *m_player;				// +0x24
};

unsigned char AITacticOffensive::checkTarget(void *targetPtr)
{
	Rva002C589B *target = (Rva002C589B *)targetPtr;
	Rva005DC763Units *units = *(Rva005DC763Units **)g_00DFEEF8->rva002A8F24(m_player);
	Object *obj = 0;
	for (unsigned int i = 0; i < units->bucket_count(); ++i)
	{
		obj = ((Rva0025BFF8 *)units)->rva0025BFF8(i);
		if (obj && (obj->getTemplate()->m_kindOf108 & 8) && !(obj->getTemplate()->m_kindOf108 & 4))
		{
			bool canReach;
			Object *structure = target->rva002C5DA6();
			if (structure)
				canReach = TheAI->pathfinder()->QuickDoesPathExistToStructure(obj, &obj->m_pos, structure, 0);
			else
				canReach = TheAI->pathfinder()->QuickDoesPathExist(obj, &obj->m_pos, &target->m_pos, 0);
			if (slot10() == canReach)
				return false;
			break;
		}
	}

	if (obj == 0)
		return false;
	if (g_00DFEEF8->rva002A8AB1(m_player)->m_16C != 0)
		return true;
	Object *structure = target->rva002C5DA6();
	if (structure == 0)
		return true;
	if ((structure->getTemplate()->m_kindOf120 & 4) == 0)
		return true;
	if (structure->m_flags94 & 1)
		return true;
	if (structure->m_status438 & 1)
		return true;
	return false;
}
