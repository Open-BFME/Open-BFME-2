// ?rva002697FC@AIUpdateInterface@@UAE_NXZ
// partial score=0.85 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /G7
// AIUpdate vtable 0x00BFA480 slot 152, retail 0x002697FC (234B). Reduced from
// Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp.
// Needs pins (symbols.csv, land with the body):
//   ?rva002FA2DC@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@PAVWeapon@@H@Z,0x002FA2DC
//   ?rva00262B0F@AIUpdateInterface@@QAEXPAVObject@@@Z,0x00262B0F
// Wall: retail pushes ebx/edi at entry, esi after the ID modulo and ebp after
// the state check, with a separate xor-al/jmp exit per level; this pushes all
// four up front with one shared exit. Everything else matches.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI };
enum ObjectID { INVALID_ID = 0 };
enum KindOfType { BFME_KINDOF_02 = 0x02, BFME_KINDOF_07 = 0x07 };
enum ObjectStatusTypes { BFME_OBJECT_STATUS_26 = 0x26 };
enum StateID { BFME_AI_HUNT = 0x11, BFME_AI_ATTACK_MOVE_TO = 0x21 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
struct Coord3D { float x, y, z; };
class Weapon;
class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindof[t >> 5] & (1U << (t & 31)); }
	unsigned char m_unmodelled_00[0x108];
	UnsignedInt m_kindof[4];
};
class Thing
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	virtual void slot00();
	ThingTemplate *m_template;
};
class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
	ObjectID getID() const { return m_id; }
	unsigned char m_unmodelled_08[0x38 - 8];
	Coord3D m_cachedPos;
	unsigned char m_unmodelled_44[0x74 - 0x44];
	ObjectID m_id;
};
class Pathfinder
{
public:
	Bool rva002FA2DC(Object *obj, const Coord3D *pos, Weapon *weapon, Int value);
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	unsigned char m_unmodelled_00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;
class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	unsigned char m_unmodelled_00[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;
extern Int g_Va00DBA4E4;
template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template<>
class BfmeVirtualSlots<0>
{
};
class AIUpdateSlot143 : public BfmeVirtualSlots<143>
{
public:
	virtual CommandSourceType getLastCommandSource() const = 0;
};
class AIUpdateInterface
{
public:
	virtual Bool rva002697FC();
	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
	void rva00262B0F(Object *obj);
	Object *getCurrentVictim() const;
	void destroyPath();
	Int rva00260DED() const;
	Object *getObject() const { return m_object; }
	unsigned char m_unmodelled_04[4];
	Object *m_object;
};

Bool AIUpdateInterface::rva002697FC()
{
	Object *obj = getObject();
	if (obj->testStatus(BFME_OBJECT_STATUS_26) || obj->isKindOf(BFME_KINDOF_02))
		return false;

	Int period = 2 * g_Va00DBA4E4;
	Int slot = obj->getID() % period;
	if (TheGameLogic->getFrame() % period != slot)
		return false;

	Int state = rva00260DED();
	if (state == BFME_AI_HUNT)
		return false;

	if (reinterpret_cast<AIUpdateSlot143 *>(this)->getLastCommandSource() == CMD_FROM_AI
		|| state == BFME_AI_ATTACK_MOVE_TO)
	{
		Object *victim = getCurrentVictim();
		if (victim && victim->isKindOf(BFME_KINDOF_07))
		{
			Object *other = getNextMoodTarget(true, false);
			if (other && other != victim && !other->isKindOf(BFME_KINDOF_07)
				&& TheAI->pathfinder()->rva002FA2DC(obj, other->getPosition(), obj->getCurrentWeapon(0), 0))
			{
				rva00262B0F(other);
				destroyPath();
				return true;
			}
		}
	}
	return false;
}
