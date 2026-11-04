// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/shims/moduledata
//
// ??1AttachUpdateModuleData@@UAE@XZ retail 0x00491AA0 48B, called by ??_G at
// 0x00491A84 (slot 0 of vftable 0x00C4DD18). Destroys ObjectFilter at +8
// through the pinned 0x00360D26, then the inline Snapshot destructor restores
// 0x00BBB554. The novtable view keeps the entry vptr store retail lacks out
// of the body; the single tracked member gives the state-0 EH frame. The
// declarations below are AttachUpdate.cpp's (the approved TU).

class Object;
class Player;
class Rva00346BC0;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"	// Coord3D::equals 0x00003702
#include "../../../Common/GameLogicObjectLookupView.h"
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};
enum DamageType
{
	DAMAGE_RVA00491D2F_8 = 8
};
enum DeathType
{
	DEATH_NORMAL = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA00491AD0_98 = 0x62
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
// BFME2's partition filter chain (the view AIStructureCreepTactic.cpp
// documents): link 0x00625790 chains the next filter.
#include "../../../../Include/GameLogic/PartitionFilter.h"
// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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
namespace _STL {
template <int _Words> struct _Base_bitset
{
	bool _M_is_any() const;	// 0x000454BA
	unsigned long _M_w[_Words];
};
}
#include "../../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
#include "../../../../Include/Common/Player.h"
#include "../../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../../Include/Common/ThingTemplate.h"
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};
enum EvaEventID { EVA_EVENT_STUB = 0 };
#include "../../../../Include/GameClient/Eva.h"
extern Eva *TheEva;
#include "../../../../Include/Common/Geometry.h"
#include "../../../Common/Thing/thing.h"
class Object : public Thing
{
public:
	void teleportTo(const Coord3D *pos, bool flag);  // rowed 0x0029660C
	__declspec(dllimport) __forceinline void rva0029660C(const Coord3D *pos, int flag) { (this->*reinterpret_cast<void (Object::*)(const Coord3D *, int)>(&Object::teleportTo))(pos, flag); }
	void kill(DamageType damageType, DeathType deathType);	// 0x002984D4
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool rva002931BA();	// 0x002931BA
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);	// 0x0028CDEB (row spelling)
	void setStatus(ObjectStatusTypes bit, bool flag);	// 0x0023DB0E
	ObjectID getID() const { return m_id; }
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getRider() const { return m_274; }	// +0x274 (WB reads it through a getter)
	void *rva0028C197() const;	// 0x0028C197, the +0x250 interface
	const GeometryInfo *getGeometryInfo() const { return &m_geometryInfo; }
	char m_pad060[0x74 - 0x60];
	ObjectID m_id;		// +0x74
	char m_pad078[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;	// +0xA8
	char m_pad104[0x250 - 0x104];
	void *m_250;		// +0x250
	char m_pad254[0x274 - 0x254];
	Object *m_274;		// +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_438;	// +0x438 (bit 0: effectively dead)
};
extern GameLogic *TheGameLogic;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"
// The module data (ctor 0x00491968, vftable 0x00C4DD18; its destructor
// 0x00491AA0 destroys ObjectFilter, then Snapshot restores 0x00BBB554).
class __declspec(novtable) AttachUpdateModuleData : public Snapshot
{
public:
	virtual ~AttachUpdateModuleData();
	int m_unused04;			// +0x04
	Rva003623E5Member m_objectFilter;	// +0x08 ObjectFilter
	_STL::_Base_bitset<4> m_parentStatus;	// +0x0C ParentStatus
	float m_scanRange;		// +0x1C ScanRange
	bool m_alwaysTeleport;		// +0x20 AlwaysTeleport
	bool m_anchorToTopOfGeometry;	// +0x21
	int m_parentOwnerAttachmentEvaEvent;	// +0x24
	int m_parentAllyAttachmentEvaEvent;	// +0x28
	int m_parentEnemyAttachmentEvaEvent;	// +0x2C
	const FXList *m_attachFX;	// +0x30 AttachFX
	int m_parentOwnerDiedEvaEvent;	// +0x34
	int m_parentAllyDiedEvaEvent;	// +0x38
	int m_parentEnemyDiedEvaEvent;	// +0x3C
};
class ModuleData;
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
enum NameKeyType
{
	NK_UNKNOWN = 0
};
#include "../../../../Include/Common/NameKeyGenerator.h"
//
// AttachUpdate::xfer, retail 0x004918AC (102 bytes): slot 3 of the class's
// primary vtable 0x00C4DB20. Version 3 over the UpdateModule base: the
// attached Object's ID (+0x20); before version 2 a dropped bool; from version
// 3 the +0x24 handle through TheEva's 0x001DEC48 (pinned by address; it runs
// its own versioned xfer). The version block is the BFME2 two-byte form the
// rowed Rva0054840AXfer.cpp uses.
typedef unsigned char UnsignedByte;
typedef bool Bool;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);

extern NameKeyGenerator *TheNameKeyGenerator;

class AttachUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva00491AD0();	// 0x00491AD0
	void rva00491C84(Coord3D *out, const Object *parent);	// 0x00491C84, the anchor point
protected:
	virtual void xfer(Xfer *xfer);
private:
	const AttachUpdateModuleData *getAttachUpdateModuleData() const
	{
		return (const AttachUpdateModuleData *)m_moduleData;
	}
	ObjectID m_parentID;	// +0x20
	int m_diedEvaEvent;	// +0x24
public:
	virtual NameKeyType getModuleNameKey() const;
};

AttachUpdateModuleData::~AttachUpdateModuleData()
{
}
