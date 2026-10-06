// cl: /MD
//
// ?Rva00547070@AttackObjectGroupOrder@@UAEPAUCoord3D@@H@Z, retail 0x00547070 41B.
// Virtual slot 8 (offset 0x20) of vtable 0x0086A420 (class of
// ??1AttackObjectGroupOrder@@UAE@XZ in Rva00548948Derived.cpp). No donor (opaque Rva).
// Evidence: push [ebx+0x18] ObjectID plus TheGameLogic findObjectByID row
// 0x00049DC5 plus copy of found Object position +0x38 into this Coord3D +0x20
// via lea plus 3x movsd plus lea eax return. No callers. Ignores int dummy
// param (ret 4) and uses this only.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};
class Object;
class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void rva0026C2D9(Object *obj, int maxShotsToFire, CommandSourceType cmdSource);
};
class AIUpdateInterface
{
public:
	char m_pad0[0x20];
	AICommandInterface m_commands; // +0x20
};
typedef void (*ContainIterateFunc)(Object *obj, void *userData);
template <int N> class Rva0054711ASlots : public Rva0054711ASlots<N - 1>
{
public:
	virtual void gap(char (*)[N + 1]) = 0;
};
template <> class Rva0054711ASlots<0>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
// Object +0x250: slot 68 walks the contained Objects.
class ContainModuleInterface : public Rva0054711ASlots<67>
{
public:
	virtual void iterateContained(ContainIterateFunc func, void *userData, bool reverse) = 0;
};
struct Rva0054711ATemplate
{
	char m_pad0[0x115];
	unsigned char m_115; // +0x115
};
class Object
{
public:
	char m_pad0[4];
	const Rva0054711ATemplate *m_template; // +0x04
	char m_pad8[0x38 - 8];
	Coord3D m_position; // +0x38
	char m_pad44[0x250 - 0x44];
	ContainModuleInterface *m_contain; // +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_flags438; // +0x438 bit0
	bool isUsingAirborneLocomotor() const;
};
class GameLogic
{
public:
	Object* findObjectByID(ObjectID id);
};
extern GameLogic* TheGameLogic;
class BuildListInfo
{
public:
	int getDesiredGatherers();
};
class AttackObjectGroupOrder
{
public:
	virtual ~AttackObjectGroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void rva0054711A(ObjectID id);
	virtual bool Rva0054703E(int dummy);
	virtual void slot06();
	virtual void slot07();
	virtual Coord3D* Rva00547070(int dummy);
	virtual void slot09();
	virtual void slot10();
	virtual bool rva00547099(int *outID, void *out);
	static void rva005470F8(Object *obj, void *userData);
private:
	char m_pad04[0x18 - 4];
	ObjectID m_targetID; // +0x18
	bool m_b1C; // +0x1C
	char m_pad1D[3];
	Coord3D m_pos; // +0x20
};
Coord3D* AttackObjectGroupOrder::Rva00547070(int dummy)
{
	Object* found = TheGameLogic->findObjectByID(m_targetID);
	if (found != 0) {
		Coord3D* dst = &m_pos;
		const Coord3D* src = &found->m_position;
		*dst = *src;
	}
	return &m_pos;
}

// ?Rva0054703E@AttackObjectGroupOrder@@UAE_NH@Z @0x0054703E 50B.
// Virtual slot 5 (offset 0x14) of vtable 0x0086A420 (same class/vtable/flags
// as slot8 above). Evidence: m_b1C check plus m_targetID plus TheGameLogic
// findObjectByID row 0x00049DC5 plus Object+0x438 bit0 test. No callers.
// Ignores int dummy param (ret 4) and uses this only.
bool AttackObjectGroupOrder::Rva0054703E(int dummy)
{
	if (m_b1C) {
		return true;
	}
	Object* found = TheGameLogic->findObjectByID(m_targetID);
	if (found == 0) {
		m_b1C = true;
		return true;
	}
	if ((found->m_flags438 & 1) == 0) {
		return false;
	}
	m_b1C = true;
	return true;
}

// ?rva00547099@AttackObjectGroupOrder@@UAE_NPAHPAX@Z, retail 0x00547099 95B.
// Virtual slot 11 (offset 0x2C) of vtable 0x0086A420 (same class/vtable/flags
// as slots 5/8 above). Sets *outID to 0x425, finds Object via m_targetID,
// copies found position+0x38 or own m_pos to out+0x14 via 3x movsd, gatherers
// to out+4, airborne to out+0. Returns true. Evidence: vslot, donor layout,
// callers none.
bool AttackObjectGroupOrder::rva00547099(int *outID, void *out)
{
	*outID = 0x425;
	Object *found = TheGameLogic->findObjectByID(m_targetID);
	if (found) {
		int gatherers = ((BuildListInfo *)found)->getDesiredGatherers();
		*(int *)((char *)out + 4) = gatherers;
		*(Coord3D *)((char *)out + 0x14) = found->m_position;
		*(bool *)out = found->isUsingAirborneLocomotor();
	} else {
		*(Coord3D *)((char *)out + 0x14) = m_pos;
	}
	return true;
}

// ?rva005470F8@AttackObjectGroupOrder@@SAXPAVObject@@PAX@Z @0x005470F8 34B.
// The contain-iterate callback slot 4 below hands its target's contain
// module: each contained Object with an AI attacks the Object passed as user
// data (rowed AICommandInterface::rva0026C2D9 0x0026C2D9 on the AI +0x20
// commands, 0x7FFFFFFF shots, from the player). Only slot 4 references it.
void AttackObjectGroupOrder::rva005470F8(Object *obj, void *userData)
{
	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
		ai->m_commands.rva0026C2D9((Object *)userData, 0x7FFFFFFF, CMD_FROM_PLAYER);
}

// ?rva0054711A@AttackObjectGroupOrder@@UAEXW4ObjectID@@@Z @0x0054711A 110B.
// Virtual slot 4 of vtable 0x00C6A420: the Object named by the argument
// attacks the order's +0x18 target (same command as the callback above) and,
// unless its template's +0x115 byte has bit 0x20, sends what it contains
// after the target too, through its contain module's slot 68 with
// rva005470F8 (reverse true).
void AttackObjectGroupOrder::rva0054711A(ObjectID id)
{
	GameLogic *logic = TheGameLogic;
	Object *target = logic->findObjectByID(m_targetID);
	Object *obj = logic->findObjectByID(id);
	if (target && obj)
	{
		AIUpdateInterface *ai = obj->m_ai;
		if (ai)
		{
			ai->m_commands.rva0026C2D9(target, 0x7FFFFFFF, CMD_FROM_PLAYER);
			if ((obj->m_template->m_115 & 0x20) == 0)
			{
				ContainModuleInterface *contain = obj->m_contain;
				if (contain)
					contain->iterateContained(rva005470F8, target, true);
			}
		}
	}
}
