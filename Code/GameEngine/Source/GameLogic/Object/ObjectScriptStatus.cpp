// cl: /O1 /G7 /arch:SSE /MD
// Regional O1/SSE/G7 preserved; /MD imports the native _isnan dependency.
// Object script-status and disabled-state helpers at retail 0x00291C9B+.
// Decoded from retail bytes (all verified):
// - setDisabledUntil pin (0x00290114) carries (DisabledType, frame); the
//   FOREVER literal below is 0x3FFFFFFF (UPDATE_SLEEP_FOREVER).
// - setScriptStatus bit layout (ObjectScriptStatusBit) and the DISABLED
//   enumerators (9/10) match reference/shims/bfmeobject/GameLogic/Object.h;
//   the retail offsets below (+0x437 status, +0x4C4 partition) are read from
//   the binary and supersede the shim's stale notes.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum DisabledType
{
	DISABLED_MIN = 0,
	DISABLED_SCRIPT_DISABLED = 9,
	DISABLED_SCRIPT_UNDERPOWERED = 10
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 0x02
};

// Saved status bits (Zero Hour donor ObjectStatusTypes.h; values are inert
// in this TU -- setStatus forwards its arguments without comparing them).
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE,
	OBJECT_STATUS_DESTROYED,
	OBJECT_STATUS_CAN_ATTACK,
	OBJECT_STATUS_UNDER_CONSTRUCTION,
	OBJECT_STATUS_UNSELECTABLE,
	OBJECT_STATUS_NO_COLLISIONS,
	OBJECT_STATUS_NO_ATTACK,
	OBJECT_STATUS_AIRBORNE_TARGET,
	OBJECT_STATUS_PARACHUTING,
	OBJECT_STATUS_REPULSOR,
	OBJECT_STATUS_HIJACKED,
	OBJECT_STATUS_AFLAME,
	OBJECT_STATUS_BURNED,
	OBJECT_STATUS_WET,
	OBJECT_STATUS_IS_FIRING_WEAPON,
	OBJECT_STATUS_BRAKING,
	OBJECT_STATUS_STEALTHED,
	OBJECT_STATUS_DETECTED,
	OBJECT_STATUS_CAN_STEALTH,
	OBJECT_STATUS_SOLD,
	OBJECT_STATUS_UNDERGOING_REPAIR,
	OBJECT_STATUS_RECONSTRUCTING,
	OBJECT_STATUS_MASKED,
	OBJECT_STATUS_IS_ATTACKING,
	OBJECT_STATUS_IS_USING_ABILITY,
	OBJECT_STATUS_IS_AIMING_WEAPON,
	OBJECT_STATUS_NO_ATTACK_FROM_AI,
	OBJECT_STATUS_IGNORING_STEALTH,
	OBJECT_STATUS_IS_CARBOMB,
	OBJECT_STATUS_DECK_HEIGHT_OFFSET,
	OBJECT_STATUS_RIDER1,
	OBJECT_STATUS_RIDER2,
	OBJECT_STATUS_RIDER3,
	OBJECT_STATUS_RIDER4,
	OBJECT_STATUS_RIDER5,
	OBJECT_STATUS_RIDER6,
	OBJECT_STATUS_RIDER7,
	OBJECT_STATUS_RIDER8,
	OBJECT_STATUS_FAERIE_FIRE,
	OBJECT_STATUS_MISSILE_KILLING_SELF,
	OBJECT_STATUS_REASSIGN_PARKING,
	OBJECT_STATUS_BOOBY_TRAPPED,
	OBJECT_STATUS_IMMOBILE,
	OBJECT_STATUS_DISGUISED,
	OBJECT_STATUS_DEPLOYED,

	OBJECT_STATUS_COUNT
};

// Native 0x23DA79 consumes two arguments (RET8) and builds four words.
// The boolean is already on the outer 0x28CDEB call stack while the mask
// is constructed; it belongs to that setter, whose own RET8 consumes it.
class Rva0023DA79
{
public:
	Rva0023DA79 *rva0023DA79(int ignored, int index);
	unsigned int m_bits[4];
};

class Rva00346BC0
{
public:
	unsigned int m_words[4];
};

class PartitionData
{
public:
	void makeDirty( void );
};

#include <float.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class Matrix3D;
class Thing { public: void setTransformMatrix(const Matrix3D *); };
class Object;
struct Rva00287C21Other;
class FireLogicSystem { public: void RegisterObject(Rva00287C21Other *); void UnregisterObject(Rva00287C21Other *); };
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
extern GameLogic *TheGameLogic;
struct ObjectTransformRegion {
 Coord3D lo, hi;
 bool contains(const Coord3D *p) const { return p->x > lo.x && p->x < hi.x && p->y > lo.y && p->y < hi.y; }
};
class TerrainLogic {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void getExtent(ObjectTransformRegion *);
};
extern TerrainLogic *TheTerrainLogic;
bool isPosDifferent(const Coord3D *,const Coord3D *);
bool isAngleDifferent(float,float);
class ObjectTransformContain {
public: virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void notify();
};
class ObjectTransformCallbacks {
public: virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18();
};

enum PathfindLayerEnum { LAYER_GROUND = 1 };
struct Rva002ED236Pos {
 float x,y,z;
 Rva002ED236Pos(const Coord3D &p) { x=p.x;y=p.y;z=p.z; }
 Rva002ED236Pos(const Rva002ED236Pos &p) { x=p.x;y=p.y;z=p.z; }
 ~Rva002ED236Pos() {}
};
class Pathfinder { public:
 PathfindLayerEnum rva002ED236(Object *,Rva002ED236Pos);
 bool QuickDoesPathExist(Object *, const Coord3D *, const Coord3D *, int);
};
class AI { char unknown00[0x10]; Pathfinder *m_pathfinder; public: Pathfinder *getPathfinder() { return m_pathfinder; } };
extern AI *TheAI;


class Rva001E3591 { public: bool rva001E3591(); };
class AIUpdateInterface {
public:
 bool isMoving() const;
 char unknown00[0x140];
 Rva001E3591 *path;
};
class Object
{
public:
	void setDisabledUntil( DisabledType type, UnsignedInt frame );
	void setDisabled( DisabledType type );
	Bool clearDisabled( DisabledType type );
	void makeDirty( void );
	void setScriptStatus( ObjectScriptStatusBit bit, Bool set );
	void setStatus( ObjectStatusTypes bit, Bool flag );
	Bool rva00292ED0( DisabledType type );
	void rva00292EB3( DisabledType type );
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);

protected:
 virtual void reactToTransformChange(const Matrix3D *, const Coord3D *, float);
public:
 void rva00291EB1();
 void rva0028B98B();
 char rva00294815();
 signed char rva0028CE7B() const;
 bool canCrushOrSquishNoAlly(Object *, int);
private:
 // Primary vptr at +0; all accessed fields are witnessed in retail.
 unsigned char m_pad04[0x38-4];
 Coord3D position; // +0x38
 float angle; // +0x44
 unsigned char m_pad48[0x84-0x48];
 Thing *drawable; // +0x84
 unsigned char m_pad88[0x1C4-0x88];
 float initialZ; // +0x1C4
 unsigned char m_pad1C8[0x1F8-0x1C8];
 int m_unk1F8[11];
 unsigned char m_pad224[0x248-0x224];
 bool squishable; // +0x248, independently witnessed by the native predicate
 unsigned char m_pad249[0x250-0x249];
 ObjectTransformContain *contain; // +0x250
 unsigned char m_pad254[0x258-0x254];
 AIUpdateInterface *ai; // +0x258
 unsigned char m_pad25C[0x437-0x25C];
 unsigned char m_scriptStatus; // +0x437
 unsigned char flags438; // +0x438
 unsigned char m_pad439[0x48C-0x439];
 bool pending; // +0x48C, forced ground-layer expiration is pending
 unsigned char m_pad48D[3];
 unsigned int cachedFrame; // +0x490
 unsigned char m_pad494[0x49C-0x494];
 int fireIndex; // +0x49C
 unsigned char m_pad4A0[0x4C4-0x4A0];
 PartitionData *m_partitionData; // +0x4C4
};

// ?setDisabled@Object@@QAEXW4DisabledType@@@Z
void Object::setDisabled( DisabledType type )
{
	setDisabledUntil( type, 0x3FFFFFFF );
}

// ?makeDirty@Object@@QAEXXZ
void Object::makeDirty( void )
{
	if( m_partitionData )
		m_partitionData->makeDirty();
}


// ?setStatus@Object@@QAEXW4ObjectStatusTypes@@_N@Z
void Object::setStatus( ObjectStatusTypes bit, Bool flag )
{
	Rva0023DA79 mask;
	rva0028CDEB(*reinterpret_cast<const Rva00346BC0 *>(mask.rva0023DA79(0, (int)bit)), flag);
}

// ?setScriptStatus@Object@@QAEXW4ObjectScriptStatusBit@@_N@Z
void Object::setScriptStatus( ObjectScriptStatusBit bit, Bool set )
{
	UnsignedInt oldScriptStatus = m_scriptStatus;

	if( set )
	{
		m_scriptStatus |= bit;
	}
	else
	{
		m_scriptStatus &= ~bit;
	}

	if( m_scriptStatus != oldScriptStatus )
	{
		if( (m_scriptStatus & OBJECT_STATUS_SCRIPT_DISABLED) != (oldScriptStatus & OBJECT_STATUS_SCRIPT_DISABLED) )
		{
			makeDirty();
			if( m_scriptStatus & OBJECT_STATUS_SCRIPT_DISABLED )
			{
				setDisabled( DISABLED_SCRIPT_DISABLED );
			}
			else
			{
				clearDisabled( DISABLED_SCRIPT_DISABLED );
			}
		}
		if( (m_scriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED) != (oldScriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED) )
		{
			makeDirty();
			if( m_scriptStatus & OBJECT_STATUS_SCRIPT_UNPOWERED )
			{
				setDisabled( DISABLED_SCRIPT_UNDERPOWERED );
			}
			else
			{
				clearDisabled( DISABLED_SCRIPT_UNDERPOWERED );
			}
		}
	}
}

// ?rva00292ED0@Object@@QAE_NW4DisabledType@@@Z
Bool Object::rva00292ED0( DisabledType type )
{
	if( --m_unk1F8[ type ] == 0 )
		return clearDisabled( type );
	return false;
}

void Object::rva00292EB3( DisabledType type )
{
	if( m_unk1F8[ type ] == 0 )
		setDisabled( type );
	++m_unk1F8[ type ];
}

template <int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

// placement unverified: no rowed DIR32 site yet; ZH ObjectStatusMaskType starts clear.
BitFlags<45> OBJECT_STATUS_MASK_NONE = { { 0, 0 } };

// ?reactToTransformChange@Object@@MAEXPBVMatrix3D@@PBUCoord3D@@M@Z
// BFME1 Object.cpp donor 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Native 0x00292D49..0x00292EB3 (RET12), WB 0x00CC8A20, and the named
// transform diff callees independently support Object callback identity.
// Target deltas: drawable +3A4/+3A8/+3A9, contain +250 slot0C, fire-system
// reregister pair, initial-Z +1C4 and strict interior map bounds, OFF_MAP bit8.
// The two unrowed Object helpers retain address names; no donor name is assumed.
// TheTriggerManager is the ledger owner at DFEC68; its FireLogicSystem view is
// established by RegisterObject/UnregisterObject and the init subsystem literal.
void Object::reactToTransformChange(const Matrix3D *oldMtx,const Coord3D *oldPos,float oldAngle) {
 if (_isnan(position.x) || _isnan(position.y) || _isnan(position.z)) TheGameLogic->destroyObject(this);
 if (drawable) {
  char *bytes=reinterpret_cast<char *>(drawable);
  *reinterpret_cast<unsigned *>(bytes+0x3a4)=TheGameLogic->getFrame();
  bytes[0x3a8]=0; bytes[0x3a9]=0;
  drawable->setTransformMatrix(reinterpret_cast<const Matrix3D *>(reinterpret_cast<char *>(this)+8));
 }
 bool posDiff=isPosDifferent(oldPos,&position);
 bool angDiff=isAngleDifferent(oldAngle,angle);
 if (posDiff || angDiff) {
  reinterpret_cast<ObjectTransformCallbacks *>(this)->slot18();
  if (contain) contain->notify();
  if (fireIndex>=0) {
   reinterpret_cast<FireLogicSystem *>(TheTriggerManager)->UnregisterObject(reinterpret_cast<Rva00287C21Other *>(this));
   reinterpret_cast<FireLogicSystem *>(TheTriggerManager)->RegisterObject(reinterpret_cast<Rva00287C21Other *>(this));
  }
 }
 if (posDiff) {
  if (initialZ==0.0f) initialZ=position.z;
  rva00291EB1();
  ObjectTransformRegion extent;
  TheTerrainLogic->getExtent(&extent);
  if (extent.contains(&position)) flags438 &= ~8; else flags438 |= 8;
  rva0028B98B();
 }
}

// ?rva0028B98B@Object@@QAEXXZ
// BFME1 ObjectHeightAndLayer.cpp 9cbfb551 clean forced-layer expiration donor.
// Native28B98B..28B9F6 RET0 and WB CD8420 corroborate Object fields38/48C/490,
// frame+40, AI pathfinder+10, 13-frame delay and the ground-layer result1.
// TerrainLogicBridges.cpp independently proves the existing Rva002ED236Pos
// callee-destroyed by-value ABI; explicit component copy plus a named local
// reproduces the native outgoing argument and saved argument-address slot.
// The helper and pathfinder method retain their existing address identities.
void Object::rva0028B98B() {
 if(pending && cachedFrame+13<=TheGameLogic->getFrame()) {
  Rva002ED236Pos p(position);
  if(TheAI->getPathfinder()->rva002ED236(this,p)==1) {
   cachedFrame=(unsigned int)-1;
   pending=false;
  }
 }
}

// ?canCrushOrSquishNoAlly@Object@@QAE_NPAV1@H@Z
// Clean BFME1 ObjectCanCrushOrSquish.cpp donor9cbfb551fe20dae985f91f2319d8997287b6a705.
// Target native294898..29493F RET8, named WB CC40B0 Object.cpp2538 and its
// path/isMoving call graph independently establish the NoAlly variant.
// Target fields248/258, signed level comparisons and tests0/1/2 are witnessed;
// the mode parameter stays an int ABI view rather than asserting an enum name.
// Getter method names remain address-derived through the existing pins.
// TheAI real global replaces the old attempt's address-global blocker.
bool Object::canCrushOrSquishNoAlly(Object *other,int testType) {
 if(!other) return false;
 char crusherLevel=rva00294815();
 if(!crusherLevel) return false;
 if(other->rva0028CE7B()>=crusherLevel) return false;
 AIUpdateInterface *update=ai;
 bool pathOk=false;
 if(update) {
  Rva001E3591 *path=update->path;
  if(update->isMoving() && path) pathOk=path->rva001E3591();
 }
 if(!pathOk) pathOk=TheAI->getPathfinder()->QuickDoesPathExist(this,&position,&other->position,0);
 if(!pathOk) return false;
 if(testType==1 || testType==2) { if(other->squishable) return true; }
 if(testType==0 || testType==2) { if(crusherLevel>other->rva0028CE7B()) return true; }
 return false;
}
