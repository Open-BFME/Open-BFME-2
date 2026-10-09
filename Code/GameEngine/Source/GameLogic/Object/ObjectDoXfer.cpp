// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// ?xfer@Object@@MAEXPAVXfer@@@Z
// Retail 0x00297684 3413 bytes RET4 (EH frame). Object's Snapshot xfer:
// slot 3 of the Object Snapshot vftable at 0x007FC2F0 (deleting dtor thunk
// 0x00299C89 then loadPostProcess 0x00293EFF and the name getter 0x00299C6E).
// It runs with this at the Snapshot base (Object+0x60). WB twin 0x00CD6340
// (Object::DoXfer Object.cpp lines 7742..8077) gives the order of the
// transfers; field offsets and version gates are read from retail.
// Version 1/26 through Xfer slot 0x28. A light CRC sends the template name
// id and transform then health and AI goal state and the six weapons.
// Otherwise the Zero Hour Object::xfer order with the BFME 2 additions:
// upgrade mask (rowed 0x003064CB / 0x00291440) model condition flags
// unresolved trigger names (pair list) the module data blocks named
// "BehaviorModule" (Xfer slots 5/6/7) the 0x7C-byte record list (ctor
// 0x00263895 and xfer 0x004D6F86) living-world army/region fields and the
// PathfinderPosGoalManager at +0xA4 (dtor 0x004DDF3A ctor 0x004DD7E3 xfer
// 0x004DD658). Missing drawable and team throw XferException tags 0 and 5.
// Callee names are the ledger rows/pins at each address. The record count
// is STLport list::size() (bfmelist iterator helpers) and the unresolved
// trigger pair comes from STLport make_pair (rowed out of line at
// 0x0023FC23); the other list members bind to their rowed instantiations
// through explicit-specialization declarations. The trigger loop sits in its
// own block (VC7.1 for-scope) which is what gives retail's frame packing.

#include "ascii_string.h"
#include <list>
#include "Common/Snapshot.h"
#include "Coord3D.h"
#include "Coord2D.h"

class UnicodeString;
class PooledString;
struct XferUnknown11;
struct ICoord3D
{
	int x;
	int y;
	int z;
};
class Region3D;
class IRegion3D;
struct ICoord2D
{
	int x;
	int y;
};
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void BeginBlock(const char *name) = 0;
	virtual void EndBlock() = 0;
	virtual void SkipBlock(const char *name) = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3D &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

enum ObjectID
{
	INVALID_ID = 0
};

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	WEAPONSLOT_COUNT = 6
};

enum
{
	MAX_TRIGGER_AREA_INFOS = 7,
	DISABLED_COUNT = 11
};

void XferObjectID(Xfer *xfer, ObjectID *id);
void XferDrawableID(Xfer *xfer, int *id);
void Rva003062FEXfer(Xfer *xfer, float *values);
class Rva00291440;
void rva003064CB(Xfer *xfer, Rva00291440 *mask);
Xfer *XferPathfindLayerEnum(Xfer *xfer, int *layer);
void XferFormationID(Xfer *xfer, int *id);
void XferLivingWorldArmyID(Xfer *xfer, int *id);
void Rva004E12D7Parse(void *xfer, void *value);
class Rva004E075FObj;
int Rva004E075FGet(Rva004E075FObj *xfer, int value);
class Rva0028C5CC;
Rva0028C5CC *Rva0028C5CCGet(Rva0028C5CC *xfer, char *bytes);

class Vector4
{
public:
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; }

	Vector4 Row[3];
};

template <int NUMBITS> class BitFlags
{
public:
	void xfer(Xfer *xfer);

	unsigned int m_bits[(NUMBITS + 31) / 32];
};

class Sink00291440;
class Rva00291440
{
public:
	void rva00291440(Sink00291440 *xfer);

	unsigned int m_bits[32];
};

class ThingTemplate
{
public:
	char m_pad000[0x64];
	AsciiString m_name;            // +0x64
	char m_pad068[0x10F - 0x68];
	unsigned char m_kindOfByte10F;  // +0x10F
};

class Team
{
public:
	unsigned int getID() const { return m_id; }

	char m_pad00[0x34];
	unsigned int m_id;              // +0x34
};

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};
extern TeamFactory *TheTeamFactory;

class Object;

struct Rva002D76C6Owner;
class Radar
{
public:
	void removeObject(Rva002D76C6Owner *owner);
};
extern Radar *TheRadar;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

	char m_pad00[0x10];
	Pathfinder *m_pathfinder;       // +0x10
};
extern AI *TheAI;

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class PolygonTrigger
{
public:
	char m_pad00[0x40];
	AsciiString m_triggerName;      // +0x40
};

#define OBJX_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();

class TerrainLogic
{
public:
	OBJX_SLOTS4(a) OBJX_SLOTS4(b) OBJX_SLOTS4(c) OBJX_SLOTS4(d)
	OBJX_SLOTS4(e) OBJX_SLOTS4(f) OBJX_SLOTS4(g) OBJX_SLOTS4(h)
	OBJX_SLOTS4(i)
	virtual void j0(); virtual void j1(); virtual void j2();
	virtual PolygonTrigger *getTriggerAreaByName(const AsciiString &name); // slot 39
};
extern TerrainLogic *TheTerrainLogic;

class Drawable
{
public:
	OBJX_SLOTS4(a) OBJX_SLOTS4(b) OBJX_SLOTS4(c)
	virtual void slot12();
	virtual void slot13();         // +0x34

	DrawableID getID() const;
};

class Rva00271058
{
public:
	void rva00271058(void *id);
};

class BodyModule
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual float getHealth() const;              // +0x10
	virtual void s5(); virtual void s6(); virtual void s7();
	virtual int s8();                             // +0x20
	OBJX_SLOTS4(a) OBJX_SLOTS4(b) OBJX_SLOTS4(c) OBJX_SLOTS4(d)
	virtual void t25(); virtual void t26();
	virtual float getMaxHealth() const;           // +0x6C
};

class StateMachine
{
public:
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }

	char m_pad00[0x24];
	Coord3D m_goalPosition;         // +0x24
};

class AIUpdateInterface
{
public:
	int rva00260DED() const;
	StateMachine *getStateMachine() const { return m_stateMachine; }

	char m_pad00[0x30];
	StateMachine *m_stateMachine;   // +0x30
};

class Weapon
{
public:
	AsciiString getName() const;
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
	void updateWeaponSet(const Object *obj);

	char m_data[0x40];
};

class ModuleData
{
public:
	char m_pad00[4];
	NameKeyType m_moduleTagNameKey; // +0x04
};

class BehaviorModule
{
public:
	NameKeyType getModuleTagNameKey() const { return m_moduleData->m_moduleTagNameKey; }

	void *m_vtbl;
	const ModuleData *m_moduleData; // +0x04
};

class GeometryInfo
{
public:
	char m_data[0x64];
};

struct TriggerInfo
{
	PolygonTrigger *pTrigger;
	char entered;
	char exited;
	char isInside;
	char pad;
};

struct CameraMarker;
class Rva00295969Obj;

struct BfmePod124
{
	char m_data[124];
};

// Calls bind to the rowed STLport instantiations without emitting bodies.
template <> void _STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> >::clear();
template <> void _STL::_List_base<int, _STL::allocator<int> >::clear();
template <> void _STL::list<BfmePod124, _STL::allocator<BfmePod124> >::push_back(const BfmePod124 &value);
template <> void _STL::list<Rva00295969Obj *, _STL::allocator<Rva00295969Obj *> >::push_back(Rva00295969Obj *const &value);

typedef _STL::pair<int, AsciiString> UnresolvedTrigger;

class UnresolvedTriggerList
{
public:
	void clear() { ((_STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> > *)this)->clear(); }
	void push_back(const UnresolvedTrigger &t)
	{
		((_STL::list<Rva00295969Obj *> *)this)->push_back(*(Rva00295969Obj *const *)&t);
	}

	void *m_node;
};

class Rva00263895Member
{
public:
	Rva00263895Member();
	void rva004D6F86(void *xfer);

	char m_data[0x7C];
};

class Rva00263895Record
{
public:
	virtual void xfer(Xfer *xfer);
};

struct Rva00263895Node
{
	Rva00263895Node *next;
	Rva00263895Node *prev;
	Rva00263895Record data;
};

class Rva00263895List
{
public:
	unsigned int size() const { return ((const _STL::list<BfmePod124> *)this)->size(); }
	void clear() { ((_STL::_List_base<int, _STL::allocator<int> > *)this)->clear(); }
	void push_back(const Rva00263895Member &m) { ((_STL::list<BfmePod124> *)this)->push_back(*(const BfmePod124 *)&m); }

	Rva00263895Node *m_node;
};

class Rva004E0513
{
public:
	void rva004E0513(Xfer *xfer);

	int m_value;
};

class Rva004DD843
{
public:
	void rva004DD658(Xfer *xfer);
};

class Rva004DDF3A
{
public:
	~Rva004DDF3A();
};

class Rva004DD7E3
{
public:
	Rva004DD7E3(int owner);

	char m_data[0x4C];
};

class Thing
{
public:
	virtual ~Thing();
	void setTransformMatrix(const Matrix3D *mx);

	ThingTemplate *m_template;      // +0x04
	Matrix3D m_transform;           // +0x08
	char m_thingPad[0x60 - 0x38];
};

class Object : public Thing, public Snapshot
{
public:
	ObjectID getID() const { return m_id; }

protected:
	void setID(ObjectID id);
	virtual void xfer(Xfer *xfer);

private:
	void setOrRestoreTeam(Team *team, bool restoring);

public:
	char m_pad064[0x10];
	ObjectID m_id; // +0x074
	ObjectID m_producerID; // +0x078
	ObjectID m_builderID; // +0x07C
	ObjectID m_field80; // +0x080
	Drawable *m_drawable; // +0x084
	AsciiString m_name; // +0x088
	char m_pad08C[0x8];
	BitFlags<101> m_status; // +0x094
	Rva004DD843 *m_posGoal; // +0x0A4
	GeometryInfo m_geometryInfo; // +0x0A8
	BitFlags<591> m_modelConditionFlags; // +0x10C
	char m_pad158[0x54];
	float m_field1AC; // +0x1AC
	float m_visionRange; // +0x1B0
	float m_shroudClearingRange; // +0x1B4
	float m_shroudRange; // +0x1B8
	float m_field1BC; // +0x1BC
	float m_field1C0; // +0x1C0
	float m_field1C4; // +0x1C4
	BitFlags<11> m_disabledMask; // +0x1C8
	unsigned int m_disabledTillFrame[11]; // +0x1CC
	unsigned int m_field1F8[11]; // +0x1F8
	char m_pad224[0x18];
	Snapshot *m_experienceTracker; // +0x23C
	char m_pad240[0x4];
	BehaviorModule **m_behaviors; // +0x244
	char m_pad248[0xC];
	BodyModule *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x4];
	void *m_radarData; // +0x260
	Snapshot *m_partitionLastLook; // +0x264
	char m_pad268[0xC];
	Object *m_containedBy; // +0x274
	ObjectID m_xferContainedByID; // +0x278
	unsigned int m_containedByFrame; // +0x27C
	float m_constructionPercent; // +0x280
	Rva00291440 m_upgrades; // +0x284
	Team *m_team; // +0x304
	AsciiString m_originalTeamName; // +0x308
	int m_indicatorColor; // +0x30C
	Coord3D m_healthBoxOffset; // +0x310
	Coord2D m_field31C; // +0x31C
	float m_field324; // +0x324
	char m_pad328[0x8];
	WeaponSet m_weaponSet; // +0x330
	BitFlags<104> m_curWeaponSetFlags; // +0x370
	unsigned int m_field380; // +0x380
	char m_weaponSlotBytes[6]; // +0x384
	char m_pad38A[0x2];
	Coord3D m_field38C; // +0x38C
	ObjectID m_field398; // +0x398
	char m_pad39C[0x8];
	BitFlags<154> m_specialPowerBits; // +0x3A4
	ObjectID m_soleHealingBenefactorID; // +0x3B8
	unsigned int m_soleHealingBenefactorExpirationFrame; // +0x3BC
	TriggerInfo m_triggerInfo[MAX_TRIGGER_AREA_INFOS]; // +0x3C0
	unsigned int m_enteredOrExitedFrame; // +0x3F8
	ICoord3D m_iPos; // +0x3FC
	UnresolvedTriggerList m_unresolvedTriggers; // +0x408
	int m_layer; // +0x40C
	int m_formationID; // +0x410
	Coord2D m_formationOffset; // +0x414
	AsciiString m_field41C; // +0x41C
	AsciiString m_commandSetStringOverride; // +0x420
	AsciiString m_field424; // +0x424
	unsigned int m_safeOcclusionFrame; // +0x428
	unsigned int m_field42C; // +0x42C
	unsigned int m_field430; // +0x430
	bool m_isSelectable; // +0x434
	bool m_field435; // +0x435
	bool m_field436; // +0x436
	unsigned char m_scriptStatus; // +0x437
	unsigned char m_privateStatus; // +0x438
	unsigned char m_field439; // +0x439
	char m_numTriggerAreasActive; // +0x43A
	bool m_singleUseCommandUsed; // +0x43B
	bool m_field43C; // +0x43C
	char m_pad43D[0x3];
	Rva00263895List m_podList; // +0x440
	float m_field444; // +0x444
	unsigned int m_field448; // +0x448
	ObjectID m_field44C; // +0x44C
	char m_pad450[0x6];
	bool m_field456; // +0x456
	char m_pad457[0x1];
	unsigned int m_field458; // +0x458
	int m_armyID; // +0x45C
	int m_field460; // +0x460
	int m_field464; // +0x464
	Rva004E0513 m_field468; // +0x468
	int m_field46C; // +0x46C
	int m_field470; // +0x470
	char m_pad474[0xC];
	bool m_field480; // +0x480
	char m_pad481[0x3];
	ObjectID m_field484; // +0x484
	ObjectID m_field488; // +0x488
	bool m_field48C; // +0x48C
	char m_pad48D[0x3];
	unsigned int m_field490; // +0x490
	char m_pad494[0x2C];
	unsigned int m_field4C0; // +0x4C0
};

void Object::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 26);
	*xfer == version;

	if (version.m_minimum < 14)
	{
		AsciiString unused;
		*xfer == unused;
	}

	bool notLightCRC = !xfer->IsLightCRC();

	AsciiString templateName = m_template->m_name;
	*xfer == templateName;

	ObjectID id = m_id;
	XferObjectID(xfer, &id);
	setID(id);

	if (!xfer->IsLightCRC())
	{
		Matrix3D mtx = m_transform;
		Rva003062FEXfer(xfer, (float *)&mtx);
		if (xfer->IsLoading())
			setTransformMatrix(&mtx);
	}

	*xfer == m_privateStatus;

	if (notLightCRC)
		rva003064CB(xfer, &m_upgrades);
	else
		m_upgrades.rva00291440((Sink00291440 *)xfer);

	*xfer == *m_partitionLastLook;
	*xfer == m_field380;

	if (xfer->IsLightCRC())
	{
		float health = m_body->getHealth();
		*xfer == health;
		float maxHealth = m_body->getMaxHealth();
		*xfer == maxHealth;

		XferObjectID(xfer, &m_producerID);
		XferObjectID(xfer, &m_builderID);
		*xfer == m_iPos;
		*xfer == m_originalTeamName;

		AIUpdateInterface *ai = m_ai;
		if (ai)
		{
			AsciiString aiName = ((const Weapon *)ai)->getName();
			*xfer == aiName;

			unsigned int aiState = ai->rva00260DED();
			*xfer == aiState;

			ObjectID goalID = ai->getStateMachine()->getGoalObject() ? ai->getStateMachine()->getGoalObject()->getID() : INVALID_ID;
			XferObjectID(xfer, &goalID);

			Coord3D goalPos;
			if (ai->getStateMachine()->getGoalPosition())
			{
				const Coord3D *gp = ai->getStateMachine()->getGoalPosition();
				goalPos.x = gp->x;
				goalPos.y = gp->y;
				goalPos.z = gp->z;
			}
			else
			{
				goalPos.x = 0.0f;
				goalPos.y = 0.0f;
				goalPos.z = 0.0f;
			}
			*xfer == goalPos;
		}

		for (int i = 0; i < WEAPONSLOT_COUNT; ++i)
		{
			Weapon *weapon = m_weaponSet.getWeaponInWeaponSlot((WeaponSlotType)i);
			if (weapon)
				*xfer == *(Snapshot *)weapon;
		}
		return;
	}

	unsigned int teamID = m_team ? m_team->getID() : 0;
	*xfer == teamID;

	XferObjectID(xfer, &m_producerID);
	XferObjectID(xfer, &m_builderID);

	Drawable *draw = m_drawable;
	DrawableID drawableID = draw ? draw->getID() : INVALID_DRAWABLE_ID;
	if (!xfer->IsCRC())
		XferDrawableID(xfer, (int *)&drawableID);
	if (xfer->IsLoading())
	{
		if (draw == 0)
			throw XferException(0, 0);
		((Rva00271058 *)draw)->rva00271058((void *)drawableID);
	}

	*xfer == m_name;
	m_status.xfer(xfer);

	if (version.m_minimum < 16)
	{
		ICoord2D oldValue;
		oldValue.x = 0;
		oldValue.y = 0;
		*xfer == oldValue;
		*xfer == oldValue;
	}

	m_modelConditionFlags.xfer(xfer);
	*xfer == m_scriptStatus;
	*xfer == m_field458;

	if (xfer->IsLoading())
	{
		Team *team = TheTeamFactory->findTeamByID(teamID);
		if (team == 0)
			throw XferException(5, 0);
		const bool restoring = true;
		setOrRestoreTeam(team, restoring);
	}

	*xfer == *(Snapshot *)&m_geometryInfo;
	*xfer == m_visionRange;
	*xfer == m_shroudClearingRange;
	*xfer == m_shroudRange;
	m_disabledMask.xfer(xfer);
	*xfer == m_singleUseCommandUsed;
	for (int d = 0; d < DISABLED_COUNT; ++d)
		*xfer == m_disabledTillFrame[d];

	if (xfer->IsLoading() && m_radarData)
		TheRadar->removeObject((Rva002D76C6Owner *)this);

	if (xfer->IsStoring())
	{
		if (m_containedBy)
			m_xferContainedByID = m_containedBy->getID();
		else
			m_xferContainedByID = INVALID_ID;
	}
	XferObjectID(xfer, &m_xferContainedByID);
	*xfer == m_containedByFrame;
	*xfer == m_constructionPercent;
	*xfer == m_originalTeamName;
	*xfer == m_indicatorColor;
	*xfer == m_healthBoxOffset;
	*xfer == m_field38C;
	XferObjectID(xfer, &m_field398);

	m_unresolvedTriggers.clear();
	*xfer == m_numTriggerAreasActive;
	*xfer == m_enteredOrExitedFrame;
	*xfer == m_iPos;
	if (m_numTriggerAreasActive < 0 || m_numTriggerAreasActive > MAX_TRIGGER_AREA_INFOS)
		throw XferException(5, 0);

	{
	for (int i = 0; i < m_numTriggerAreasActive; i++)
	{
		AsciiString triggerName;
		PolygonTrigger **trigger = &m_triggerInfo[i].pTrigger;
		if (*trigger)
			triggerName = (*trigger)->m_triggerName;
		*xfer == triggerName;
		if (xfer->IsLoading())
			*trigger = TheTerrainLogic->getTriggerAreaByName(triggerName);
		*xfer == m_triggerInfo[i].entered;
		*xfer == m_triggerInfo[i].exited;
		*xfer == m_triggerInfo[i].isInside;
		if (*trigger == 0)
			m_unresolvedTriggers.push_back(_STL::make_pair(i, triggerName));
	}
	}

	XferPathfindLayerEnum(xfer, &m_layer);
	if (version.m_minimum < 16)
	{
		int oldLayer;
		XferPathfindLayerEnum(xfer, &oldLayer);
	}
	*xfer == m_isSelectable;
	*xfer == m_safeOcclusionFrame;
	XferFormationID(xfer, &m_formationID);
	if (m_formationID != 0)
		*xfer == m_formationOffset;

	if (version.m_minimum >= 26)
	{
		m_curWeaponSetFlags.xfer(xfer);
		for (int w = 0; w < WEAPONSLOT_COUNT; ++w)
			*xfer == m_weaponSlotBytes[w];
		*xfer == *(Snapshot *)&m_weaponSet;
		m_weaponSet.updateWeaponSet(this);
	}

	unsigned short moduleCount = 0;
	BehaviorModule **b;
	for (b = m_behaviors; *b; ++b)
		++moduleCount;
	*xfer == moduleCount;

	AsciiString moduleIdentifier;
	BehaviorModule *module;
	if (xfer->IsStoring())
	{
		for (b = m_behaviors; *b; ++b)
		{
			module = *b;
			moduleIdentifier = TheNameKeyGenerator->keyToName(module->getModuleTagNameKey());
			*xfer == moduleIdentifier;
			xfer->BeginBlock("BehaviorModule");
			*xfer == *(Snapshot *)module;
			xfer->EndBlock();
		}
	}
	else
	{
		AsciiString otherModuleIdentifier;
		for (unsigned short m = 0; m < moduleCount; ++m)
		{
			*xfer == moduleIdentifier;
			NameKeyType moduleIdentifierKey = TheNameKeyGenerator->nameToKey(moduleIdentifier);
			module = 0;
			for (b = m_behaviors; b && *b; ++b)
			{
				if (moduleIdentifierKey == (*b)->getModuleTagNameKey())
				{
					module = *b;
					break;
				}
			}
			if (module == 0)
			{
				xfer->SkipBlock("BehaviorModule");
			}
			else
			{
				xfer->BeginBlock("BehaviorModule");
				*xfer == *(Snapshot *)module;
				xfer->EndBlock();
			}
		}
	}

	XferObjectID(xfer, &m_soleHealingBenefactorID);
	*xfer == m_soleHealingBenefactorExpirationFrame;
	*xfer == *m_experienceTracker;

	if (version.m_minimum < 26)
	{
		m_curWeaponSetFlags.xfer(xfer);
		for (int w = 0; w < WEAPONSLOT_COUNT; ++w)
			*xfer == m_weaponSlotBytes[w];
		*xfer == *(Snapshot *)&m_weaponSet;
	}

	m_specialPowerBits.xfer(xfer);
	*xfer == m_commandSetStringOverride;
	*xfer == m_field41C;
	if (version.m_minimum >= 11)
		*xfer == m_field424;
	*xfer == m_field435;
	*xfer == m_field436;
	*xfer == m_field43C;

	if (xfer->IsStoring())
	{
		unsigned int count = m_podList.size();
		*xfer == count;
		for (Rva00263895Node *p = m_podList.m_node->next; p != m_podList.m_node; p = p->next)
			p->data.xfer(xfer);
	}
	else
	{
		m_podList.clear();
		unsigned int count;
		*xfer == count;
		for (unsigned int k = 0; k < count; ++k)
		{
			Rva00263895Member record;
			record.rva004D6F86(xfer);
			m_podList.push_back(record);
		}
	}

	*xfer == m_field448;
	*xfer == m_field444;
	XferObjectID(xfer, &m_field44C);
	*xfer == m_field456;
	*xfer == m_field439;

	if (!xfer->IsCRC())
	{
		XferLivingWorldArmyID(xfer, &m_armyID);
		if (version.m_minimum >= 16)
			Rva004E12D7Parse(xfer, &m_field460);
		if (version.m_minimum >= 17)
			Rva004E075FGet((Rva004E075FObj *)xfer, (int)&m_field464);
		if (version.m_minimum < 10)
		{
			int oldInt;
			*xfer == oldInt;
			AsciiString oldString;
			*xfer == oldString;
		}
		if (version.m_minimum >= 7)
		{
			m_field468.rva004E0513(xfer);
		}
		else if (version.m_minimum >= 6)
		{
			*xfer == m_field46C;
			*xfer == m_field470;
			int oldZero = 0;
			*xfer == oldZero;
		}
	}

	*xfer == m_field480;
	bool oldFlag = false;
	*xfer == oldFlag;
	if (version.m_minimum < 18)
	{
		bool oldBool;
		*xfer == oldBool;
	}
	if (version.m_minimum < 16)
	{
		int oldValue2;
		*xfer == oldValue2;
	}
	*xfer == m_field1BC;
	*xfer == m_field1AC;

	if (xfer->IsLoading() && m_drawable)
		m_drawable->slot13();

	if (version.m_minimum >= 2)
		*xfer == m_field42C;
	if (version.m_minimum >= 3)
		*xfer == m_field430;
	if (version.m_minimum >= 4)
		*xfer == m_field48C;
	*xfer == m_field490;
	if (version.m_minimum >= 5)
		XferObjectID(xfer, &m_field484);
	if (version.m_minimum >= 8)
		XferObjectID(xfer, &m_field488);
	if (version.m_minimum >= 9)
		*xfer == m_field324;
	if (version.m_minimum >= 12)
		*xfer == m_field1C0;
	if (version.m_minimum >= 13)
		*xfer == m_field1C4;

	if (xfer->IsLoading() && (m_template->m_kindOfByte10F & 0x10))
	{
		if (!(m_privateStatus & 1) || (m_body && m_body->s8() == 0))
			TheAI->pathfinder()->AddObjectToPathfindMap(this);
	}

	if (version.m_minimum >= 15)
		XferObjectID(xfer, &m_field80);

	if (version.m_minimum >= 16)
	{
		bool hasPosGoal = m_posGoal != 0;
		*xfer == hasPosGoal;
		if (hasPosGoal)
		{
			if (xfer->IsLoading())
			{
				delete (Rva004DDF3A *)m_posGoal;
				m_posGoal = (Rva004DD843 *)new Rva004DD7E3((int)this);
			}
			m_posGoal->rva004DD658(xfer);
		}
	}

	if (version.m_minimum >= 19 && version.m_minimum < 21)
	{
		unsigned char oldByte;
		*xfer == oldByte;
	}
	if (version.m_minimum >= 20)
		*xfer == m_field31C;
	if (version.m_minimum == 21)
	{
		char oldBytes[4];
		Rva0028C5CCGet((Rva0028C5CC *)xfer, oldBytes);
	}
	if (version.m_minimum >= 23)
		*xfer == m_field4C0;
	if (version.m_minimum >= 25)
	{
		for (int f = 0; f < DISABLED_COUNT; ++f)
			*xfer == m_field1F8[f];
	}
}
