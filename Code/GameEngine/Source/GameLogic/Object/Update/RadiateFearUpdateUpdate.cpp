// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// RadiateFearUpdate::update (0x0049C21E, slot 0 of its UpdateModuleInterface
// vftable 0x00850FB0; ctor 0x0049C106 installs it). Asleep for good once the
// object is effectively dead or its upgrade (the UpgradeMux at +0x20, slot 0)
// is not active. With any of the module data's +0x10/+0x11/+0x12 flags,
// every object other than this one the controlling player's relationship
// flag 4 accepts within the data's +0x14 radius (BFME2's partition filter
// chain, the view AIStructureCreepTactic.cpp documents) that the data's
// +0x1C object filter accepts gets 0x0028EC68 (6, 4 and 5 respectively;
// this object; the data's +0x18). Sleeps the +0x18 delay plus ID mod 5.

extern "C" const void *const __identifier("??_7RadiateFearUpdateModuleData@@6B@")[];
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};
#include "../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class Thing;
class ModuleData;
class Object;
#include "../../../../Include/Common/ObjectModule.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
#include "../../../../Include/Common/BfmeXfer.h"
#define BFME_DISP8_BYTECHASE_GETTER(NAME, DISP1, DISP2) \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
		char m_lead[DISP1]; \
		void *m_ptr; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return *(unsigned char *)((char *)m_ptr + DISP2); \
	}
#define BFME_DISP8_BYTECHASE_BEFORE_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		unsigned char m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}
#pragma inline_depth(0)
#pragma inline_depth()

#include "../../../../Include/Common/XferVersion.h"

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class RadiateFearUpdate;

class UpgradeMux
{
	friend class RadiateFearUpdate;
public:
	UpgradeMux();
	void giveSelfUpgrade();
	virtual bool isAlreadyUpgraded() const;	// slot 0, 0x00098CBC
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

class Player;

#include "../../../../Include/GameLogic/PartitionFilter.h"

class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Common/PartitionRangeQueryCallView.h"

extern PartitionManager *ThePartitionManager;

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);	// 0x00362437
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028EC68(int a, void *b, int c);	// 0x0028EC68
	void applyFrom(int a, Object *source, const int &c) { rva0028EC68(a, source, c); }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	const Coord3D *getPosition() const { return &m_pos; }
	int getID() const { return m_74; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x74 - 0x44];
	int m_74;		// +0x74 the ID
	char m_pad078[0x438 - 0x78];
	unsigned char m_438;	// +0x438
};

class RadiateFearUpdateModuleData;

class RadiateFearUpdate : public UpdateModule, public UpgradeMux
{
public:
	RadiateFearUpdate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual UpdateSleepTime update();
private:
	const RadiateFearUpdateModuleData *getRadiateFearUpdateModuleData() const
	{
		return (const RadiateFearUpdateModuleData *)m_moduleData;
	}
};

template <int N> class BitFlags;

extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);
private:
	int m_filterData; // +0x00
};

#include "../../../../Include/GameLogic/Module/WeaponSetUpgradeModuleData.h"

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};

enum NameKeyType;

#include "../../../../Include/GameLogic/ExperienceTracker.h"

class MultiIniFieldParse;

class INI;

typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

#include "../../../../Include/Common/INI/FieldParse.h"

#include "../../../../Include/Common/INI/INI.h"

void Rva000B9468Parse(INI *, void *, void *, const void *);

void Rva002567EAParse(INI *, void *, void *, const void *);

void Rva002C8C06Parse(INI *, void *, void *, const void *);

void Rva00464081ParseMask(INI *, void *, void *, const void *);

void Rva00464574Parse(INI *, void *, void *, const void *);

void iniParseObjectFilter(INI *, void *, void *, const void *);

void rva004649A1(INI *, void *, void *, const void *);

void rva004B5293(INI *, void *, void *, const void *);

void Rva0049B51EParse(INI *, void *, void *, const void *);

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdateModuleData.h"

class DockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

#include "../../../../Include/GameLogic/Module/TeleportToCasterSpecialPowerModuleData.h"

#include "../../../../Include/GameLogic/Module/StoreObjectsSpecialPowerModuleData.h"

#include "../../../../Include/GameLogic/Module/CurseSpecialPowerModuleData.h"

class SupplyWarehouseDockUpdateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

#include "../../../../Include/GameLogic/Module/DelayedDeathBodyModuleData.h"

int Rva004CE29DGet(void);

int Rva004CE52EGet(void);

#include "../../../../Include/GameLogic/Module/DominateEnemySpecialPowerModuleData.h"

class RadiateFearUpdateModuleData : public UpdateModuleData
{
private:
	friend class RadiateFearUpdate;
public:
	RadiateFearUpdateModuleData();
private:
	void *m_vtable;
private:
	int m_unused04;
private:
	bool m_initiallyActive;
private:
	char m_pad09[3];
private:
	int m_whichSpecialPower;
private:
	unsigned char m_generateTerror;
private:
	unsigned char m_generateFear;
private:
	unsigned char m_generateUncontrollableFear;
private:
	unsigned char m_pad13;
private:
	float m_emotionPulseRadius;
private:
	int m_emotionPulseInterval;
private:
	Rva003623E5Filter m_victimFilter;
private:
	Rva0025342CMember m_20;
private:
	unsigned char m_pad[0x130 - 0x20 - 4];
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

UpdateSleepTime RadiateFearUpdate::update()
{
	Object *obj = m_object;
	const RadiateFearUpdateModuleData *data = getRadiateFearUpdateModuleData();
	if (obj->isEffectivelyDead())
		return UPDATE_SLEEP_FOREVER;
	if (!isAlreadyUpgraded())
		return UPDATE_SLEEP_FOREVER;
	if (data->m_generateTerror || data->m_generateFear || data->m_generateUncontrollableFear) {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(getObject()->getPosition(), data->m_emotionPulseRadius, 0,
			Rva00261409Filter(m_object->getControllingPlayer(), true, 4).link(&Rva002611BFFilter(m_object)), 0);
		Object *other;
		while ((other = hits.next()) != 0) {
			if (((Rva2225E0Filter &)data->m_victimFilter).accepts(other, obj->getControllingPlayer())) {
				if (data->m_generateTerror)
					other->applyFrom(6, m_object, data->m_emotionPulseInterval);
				if (data->m_generateFear)
					other->applyFrom(4, m_object, data->m_emotionPulseInterval);
				if (data->m_generateUncontrollableFear)
					other->applyFrom(5, m_object, data->m_emotionPulseInterval);
			}
		}
	}
	return (UpdateSleepTime)(obj->getID() % 5 + data->m_emotionPulseInterval);
}
