// cl: /O1 /G7 /DNDEBUG /MD /EHsc /I.
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
//
// InvisibilityUpdate pieces around the interface its matched ctor 0x004A382D
// installs at +0x20 (vtable 0x00C52518; primary 0x00C52534). Names are by
// address.
//
// ?rva004A3877@InvisibilityUpdate@@UAEPAVRva004A3A09Iface@@XZ, retail
// 0x004A3877, 12 bytes: primary slots 10 and 11 (one folded body), the +0x20
// interface of this object, null-checked as cl converts.
//
// ?rva004A3A09@InvisibilityUpdate@@UAE_NXZ, retail 0x004A3A09, 23 bytes: +0x20
// slot 0, whether the module data exists and has its +0x1D0 flag.
//
// ?rva004A39D0@InvisibilityUpdate@@QAEX_N@Z, retail 0x004A39D0, 57 bytes (the
// pinned toggle ToggleHiddenSpecialAbilityUpdate slots 23/24 call): unless the
// module data's +0x1D0 flag is set, raising wakes the module next frame and
// sets +0x24 once; lowering clears +0x24.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

struct InvisibilityUpdateModuleData
{
	unsigned char m_pad000[0xC0];
 unsigned int m_interval;
 unsigned char m_required[128],m_exempt[128];
 bool m_broadcast;
 unsigned char m_pad1C5[3];
 const void *m_filter;
 float m_radius;
	bool m_1D0; // +0x1D0
};

template <int N> class Rva004A3877Slots : public Rva004A3877Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004A3877Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva004A3A09Iface
{
public:
	virtual bool rva004A3A09() = 0;
};

class Rva004A3A20Interface {
public: virtual UpdateSleepTime update() = 0;
};
class InvisibilityUpdatePrimary : public Rva004A3877Slots<10> {
public: virtual Rva004A3A09Iface *rva004A3877() = 0;
protected:
 const InvisibilityUpdateModuleData *m_moduleData;
 Object *m_object;
 unsigned char m_pad0C[4];
};
class UpdateModule : public InvisibilityUpdatePrimary, public Rva004A3A20Interface {
protected:
 void setWakeFrame(Object*,UpdateSleepTime);
 unsigned char m_pad14[12];
};

class InvisibilityUpdate : public UpdateModule, public Rva004A3A09Iface
{
public:
	virtual Rva004A3A09Iface *rva004A3877();
	virtual bool rva004A3A09();
	void rva004A39D0(bool on);
 virtual UpdateSleepTime update();
private:
	bool m_24; // +0x24
};

// ?rva004A3877@InvisibilityUpdate@@UAEPAVRva004A3A09Iface@@XZ @0x004A3877
Rva004A3A09Iface *InvisibilityUpdate::rva004A3877()
{
	return this;
}

// ?rva004A3A09@InvisibilityUpdate@@UAE_NXZ @0x004A3A09
bool InvisibilityUpdate::rva004A3A09()
{
	const InvisibilityUpdateModuleData *data = m_moduleData;
	return data && data->m_1D0;
}

// ?rva004A39D0@InvisibilityUpdate@@QAEX_N@Z @0x004A39D0
void InvisibilityUpdate::rva004A39D0(bool on)
{
	if (m_moduleData->m_1D0)
		return;
	if (on)
	{
		if (!m_24)
		{
			setWakeFrame(m_object, UPDATE_SLEEP_NONE);
			m_24 = true;
		}
	}
	else if (m_24)
		m_24 = false;
}

class Player;
class Rva0033A453 { public: bool rva0033A453(const void*,const void*) const; };
class Object {
public:
 Player *getControllingPlayer() const;
 const Coord3D *getPosition() const { return &m_position; }
 const Rva0033A453 *getUpgrades() const { return &m_upgrades; }
 unsigned char m_pad000[0x38]; Coord3D m_position;
 unsigned char m_pad044[0x284-0x44]; Rva0033A453 m_upgrades;
};
class Rva000421C8 {
public:
 Rva000421C8():m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object*)=0;
 virtual int getPlayerMask();
 Rva000421C8 *m_next;
};
class Rva002614ECFilter : public Rva000421C8 {
public:
 Rva002614ECFilter(const void *what,Player *player,bool match):m_what(what),m_player(player),m_match(match) {}
 virtual bool allow(Object*);
 const void *m_what; Player *m_player; bool m_match;
};
class Rva00439CF7 { public: void rva00439CF7(Object*,int,const void*); };
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;

// WB1211D10 and the retail secondary update dispatch establish this callback.
// Reference semantic lead: Zero Hour InvisibilityUpdate::update; the 128-byte
// target upgrade masks and module-data offsets come from native4A3A20..4A3B35.
// Object +284 is the upgrade-mask receiver of the independently owned66B
// dual-mask tester3A453. The equal-valued receiver PHI preserves the final
// required-mask PUSH / receiver LEA scheduling. Full277 bytes and EH checked.
// BF1 donor revision575ba2b04743f190f069805fbdc59936123c45da.
UpdateSleepTime InvisibilityUpdate::update() {
 const InvisibilityUpdateModuleData *data=m_moduleData;
 Object *owner=m_object;
 if(!m_24) return UPDATE_SLEEP_FOREVER;
 if(!owner) return UPDATE_SLEEP_FOREVER;
 if((data ? owner->getUpgrades() : owner->getUpgrades())->rva0033A453(data->m_required,data->m_exempt)) {
  if(data->m_broadcast) {
   Rva002614ECFilter filter(&data->m_filter,owner->getControllingPlayer(),true);
   BfmeWideResult result=ThePartitionManager->iterateObjectsInRange(owner->getPosition(),data->m_radius,0,&filter,1);
   Object *target;
   while((target=result.next())!=0)
    ((Rva00439CF7*)TheGameLogic->getManager178())->rva00439CF7(target,data->m_interval,(const char*)data+8);
  } else
   ((Rva00439CF7*)TheGameLogic->getManager178())->rva00439CF7(owner,data->m_interval,(const char*)data+8);
 }
 return (UpdateSleepTime)data->m_interval;
}
