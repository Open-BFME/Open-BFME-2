// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
#include "../../../Common/RTS/XYDistanceCallView.h"
//
// ?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x00490225, 589 bytes: slot 0 of the UpdateModuleInterface vtable
// 0x00C4D058 that the matched ctor 0x004900B1 installs at +0x10, so the
// override runs with the +0x10 subobject this. Layout is the 0x2C-byte class
// of LargeGroupBonusUpdateCtor.cpp / LargeGroupBonusUpdateXfer.cpp.
//
// Every module-data delay (+0x08) frames, or every frame for the object
// kinds whose template bits +0x109 bit 0/1 are set: count the horde members
// within the +0x14 radius (the HordeMemberFilter-led field +0x0C, BFME2's
// partition filter chain: that filter, same controlling player, alive, not
// this object), and turn the bonus on when the count reaches +0x10 - 1, or
// otherwise when a hit whose behavior interface (slot 0x74) answers slot 2
// lies within the +0x1C distance. A change applies or removes the attribute
// modifier named at +0x2C (Object::addAttributeModifierToPool /
// Object::removeAttributeModifierFromPool).

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class Thing;
class ModuleData;
class Object;
class Player;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

template <int N> class Rva00490225Slots : public Rva00490225Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00490225Slots<0>
{
};

// The +0x0C field of the module data (the HordeMemberFilter entry).
struct Rva00490225MemberFilter
{
	void *m_00;
};

// The interface Object::rva0028C197 returns: slot 0x60 counts the members
// the given filter accepts.
class Rva00490225Contain : public Rva00490225Slots<96>
{
public:
	virtual UnsignedInt countMembers(const Rva00490225MemberFilter *filter) = 0;
};

// What a behavior module's slot 0x74 hands back: slot 2 says whether it
// counts toward the bonus.
class Rva00490225Member
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual Bool isActive() = 0;
};

class Rva00490225BehaviorIface : public Rva00490225Slots<29>
{
public:
	virtual Rva00490225Member *getMember() = 0;
};

class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;			// +0x08
};

class BehaviorModule : public ObjectModuleBase, public Rva00490225BehaviorIface
{
};

struct ObjectKindBytes
{
	// The KindOf mask. Retail tests +0x109 bit 0 and bit 1 with two
	// separate byte tests; read at one width, cl 7.1 folds the pair into a
	// single test al,3, so the second bit is read off the dword.
	unsigned char m_pad000[0x108];
	union {
		unsigned char m_bytes[28];
		unsigned int m_words[7];
	};
};

class Object
{
public:
	Player *getControllingPlayer() const;				// 0x0028AFA9
	void *rva0028C197() const;				// 0x0028C197
	Bool addAttributeModifierToPool(const AsciiString &name, int duration);
	void removeAttributeModifierFromPool(const AsciiString &name);
	const Coord3D *getPosition() const { return &m_pos; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	Bool isKindOf109Bit0() const { return (m_template->m_bytes[1] & 1) != 0; }
	unsigned int isKindOf109Bit1() const { return m_template->m_words[0] & 0x200; }
	__forceinline Rva00490225Member *findMember() const
	{
		for (BehaviorModule **m = getBehaviorModules(); *m; ++m) {
			Rva00490225Member *member = (*m)->getMember();
			if (member)
				return member;
		}
		return 0;
	}
	const ObjectKindBytes *m_template;	// +0x04 (after the vptr)
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad044[0x244 - 0x44];
	BehaviorModule **m_behaviors;		// +0x244
	unsigned char m_pad248[0x438 - 0x248];
	unsigned char m_438;			// +0x438
private:
	virtual void anchor();
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00C4D040, allow 0x00260F9E: the member filter at +0x08 and
// whether a counted hit allows.
class Rva00260F9EFilter : public Rva000421C8
{
public:
	Rva00260F9EFilter(const Rva00490225MemberFilter *filter, bool match)
		: m_filter(filter), m_match(match) {}
	virtual bool allow(Object *obj);
	const Rva00490225MemberFilter *m_filter;
	bool m_match;
};

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF: not the given object.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

struct Rva00490225HitEntry
{
	Object *m_object;
	unsigned m_distanceBits;
};

struct Rva00490225HitList
{
	Rva00490225HitEntry *m_begin;	// +0x00
	Rva00490225HitEntry *m_end;	// +0x04
	void *m_08;
	Rva00490225HitEntry *m_cursor;	// +0x0C
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void reset() { m_value->m_cursor = m_value->m_begin; }
	Rva00490225HitList *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

struct LargeGroupBonusUpdateModuleData
{
	unsigned char m_pad00[0x08];
	UnsignedInt m_delay;				// +0x08
	Rva00490225MemberFilter m_memberFilter;	// +0x0C
	UnsignedInt m_count;				// +0x10
	Real m_radius;					// +0x14
	unsigned char m_pad18[0x1C - 0x18];
	Real m_nearDistance;				// +0x1C
	unsigned char m_pad20[0x2C - 0x20];
	AsciiString m_modifierName;			// +0x2C
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public ObjectModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class LargeGroupBonusTrailing
{
public:
	virtual void trailingSlot();
};

class LargeGroupBonusUpdate : public UpdateModule, public LargeGroupBonusTrailing
{
public:
	virtual UpdateSleepTime update();
private:
	const LargeGroupBonusUpdateModuleData *getLargeGroupBonusUpdateModuleData() const
	{
		return (const LargeGroupBonusUpdateModuleData *)m_moduleData;
	}
	UnsignedInt m_lastFrame;	// +0x24
	Bool m_active;			// +0x28
	Bool m_bySize;			// +0x29
	Bool m_2A;
};

UpdateSleepTime LargeGroupBonusUpdate::update()
{
	Object *obj = m_object;
	if (!obj)
		return UPDATE_SLEEP_FOREVER;

	Bool wasActive = m_active;
	const LargeGroupBonusUpdateModuleData *data = getLargeGroupBonusUpdateModuleData();
	Bool everyFrame = obj->isKindOf109Bit0() || obj->isKindOf109Bit1();
	if (everyFrame || TheGameLogic->getFrame() > m_lastFrame + data->m_delay) {
		m_lastFrame = TheGameLogic->getFrame();
		Rva00260F9EFilter filterMember(&data->m_memberFilter, true);
		Rva00260E2AFilter filterPlayer(obj->getControllingPlayer());
		Rva0026119DFilter filterAlive;
		Rva002611BFFilter filterNotThis(obj);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), data->m_radius, 3,
			filterMember.link(filterPlayer.link(filterAlive.link(&filterNotThis))), 0);
		UnsignedInt count = 0;
		Object *other;
		while ((other = hits.next()) != 0) {
			Rva00490225Contain *contain = (Rva00490225Contain *)other->rva0028C197();
			if (contain)
				count += contain->countMembers(&data->m_memberFilter);
		}
		hits.reset();
		if (count >= data->m_count - 1) {
			m_bySize = true;
			m_active = true;
		} else {
			m_active = false;
			m_bySize = false;
			Real nearSqr = data->m_nearDistance * data->m_nearDistance;
			while ((other = hits.next()) != 0) {
				Rva00490225Member *member = other->findMember();
				if (member && member->isActive()) {
					Real distSqr = reinterpret_cast<Rva000CBA20 *>(m_object)->distSq(reinterpret_cast<const Rva000CBA20Point *>(other->getPosition()));
					if (distSqr <= nearSqr) {
						m_active = true;
						break;
					}
				}
			}
		}
		if (wasActive != m_active) {
			if (m_active)
				obj->addAttributeModifierToPool(data->m_modifierName, 0);
			else
				obj->removeAttributeModifierFromPool(data->m_modifierName);
		}
	}
	if (obj->m_438 & 1)
		return UPDATE_SLEEP_FOREVER;
	obj->rva0028C197();
	return everyFrame ? (UpdateSleepTime)data->m_delay : UPDATE_SLEEP_NONE;
}
