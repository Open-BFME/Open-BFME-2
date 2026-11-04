// cl: /MD /GX
//
// EntEnragedUpdate members that ask the partition manager whether anything
// qualifying is near (+0x04 the module data, +0x08 the object; both called
// from the unrowed 0x004B2761, at 0x004B2847 and 0x004B2857). Each is true
// when an object within the module data's +0x14 range (2D centre) passes:
//
//   0x004B25C9  the 0x002614EC filter over the module data's +0x18 and the
//               object's controlling player, the 0x002611AF one and the
//               allied (relationship 4) one
//   0x004B266D  the 0x00261058 player filter, the 0x002614EC one over the
//               module data's +0x1C, and alive
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
class Object;
class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF8FE4, allow 0x0026109D: +0x08 the object's controlling player
// (or none), +0x0C a flag.
class Rva00261058 : public Rva000421C8
{
public:
	Rva00261058(Object *obj, bool flag);
	virtual bool allow(Object *obj);
	Player *m_player;
	bool m_flag;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00C56930, allow 0x002611AF: no members of its own.
class Rva002611AFFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
};

#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

// Use the constructor TU's +0x20 UpdateModule hierarchy and module-data
// fields; the scan bodies read the same offsets without a second flat view.
enum NameKeyType { NK_UNKNOWN = 0 };
class Thing;
class ModuleData;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

private:
};

class EntEnragedUpdateModuleData : public UpdateModuleData
{
public:
	EntEnragedUpdateModuleData();

private:
	friend class EntEnragedUpdate;
	const void *m_vtable; // +0
	int m_baseTail; // +4
	int m_scanDelayTime; // +8, defaults to LogicFramesPerSecond
	int m_enragedTime; // +0xC
	int m_timeUntilCanRageAgain; // +0x10
	float m_scanDistance; // +0x14
	Rva003623E5Member m_hatedFilter; // +0x18
	Rva003623E5Member m_friendlyFilter; // +0x1C
	int m_transitionTime; // +0x20
	int m_transitionFX; // +0x24
	int m_onBuffFX; // +0x28
	int m_offBuffFX; // +0x2C
};

class EntEnragedUpdate : public UpdateModule
{
public:
	EntEnragedUpdate(Thing *, const ModuleData *);
	virtual ~EntEnragedUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva004B23C5(Xfer *xfer); // slot 3 of 0x00C56948
	// Rowed in EntEnragedUpdateUpdate.cpp: slot 0 of retail's UpdateModuleInterface table 0x00C5693C.
	virtual UpdateSleepTime update();
	bool rva004B25C9();
	bool rva004B266D();

private:
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	bool m_2C;
	bool m_2D;
	bool m_2E;
	bool m_2F;
	bool m_30;
};

bool EntEnragedUpdate::rva004B25C9()
{
	Object *obj = m_object;
	const EntEnragedUpdateModuleData *md = (const EntEnragedUpdateModuleData *)m_moduleData;
	Rva002614ECFilter same(&md->m_hatedFilter, obj->getControllingPlayer(), true);
	Rva00260EB1Filter allies(obj, 4, false);
	Rva002611AFFilter third;
	same.link(&third);
	same.link(&allies);
	return ThePartitionManager->getClosestObject(&obj->m_pos, md->m_scanDistance, 1, &same) != 0;
}

bool EntEnragedUpdate::rva004B266D()
{
	const EntEnragedUpdateModuleData *md = (const EntEnragedUpdateModuleData *)m_moduleData;
	Object *obj = m_object;
	Rva00261058 player(obj, false);
	Rva002614ECFilter same(&md->m_friendlyFilter, obj->getControllingPlayer(), true);
	Rva0026119DFilter alive;
	player.link(&same);
	player.link(&alive);
	return ThePartitionManager->getClosestObject(&obj->m_pos, md->m_scanDistance, 1, &player) != 0;
}
