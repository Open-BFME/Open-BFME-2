// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?rva00291A8C@Object@@QAEXMMMABVAsciiString@@@Z
#include <math.h>
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
// stlport
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
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
#include "../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
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
 void RemoveObjectFromPathfindMap(Object *);
 void AddObjectToPathfindMap(Object *);
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
class AttributeModifierPoolUpdate { public: bool rva00403382(int,float *,int);bool rva00403448(int,float*,int,int); };
enum KindOfType { KINDOF_VIEW_UNKNOWN = 0 };
struct ObjectCrushLevelsView {
 char unknown00[0x5f9];
 char crusher,crushable,alternateCrusher,alternateCrushable;
 char unknown5fd;
 bool gate5fe;
};

#include "Common/BfmeAudioEventPrefix136.h"
extern "C" void *memset(void*,int,unsigned int);
class Rva002D9508 {public:void rva002D9508(const void*);};
class Object; class Player; class RadarWindowOverrideSource;
class Rva002390CB {public:
 int key;OpaqueRefElement4 value;
 Rva002390CB(const Rva002390CB &);
 __forceinline ~Rva002390CB(){if(value.referent)value.referent->Release_Ref();}
};
class Drawable { public: Rva002390CB rva0028F912(); void setDrawableHidden(bool); char pad[0x43c]; bool flag43c; };
class PlayerList { public: char pad[0x10]; Player *local; };
extern PlayerList *ThePlayerList;
class GameMessage { public: enum Type { TYPE_VIEW=0 }; void appendObjectIDArgument(ObjectID); };
class MessageStream { public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
 virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
 virtual void s40(); virtual void s44(); virtual GameMessage *appendMessage(GameMessage::Type);
};
extern MessageStream *TheMessageStream;
struct Rva002D76C6Owner;
class Radar { public: void removeObject(Rva002D76C6Owner *); };
extern Radar *TheRadar;
class Rva002D37Owner { public: void rva002D373E(int); };
struct Obj00526309;
class Rva002D3726 { public: void rva002D3726(Obj00526309 *); };
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

template <int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
 bool any()const;
 int countInverseIntersection(const BitFlags &)const;
};


class Rva001E4A4E {public:int rva001E4A4E(int);};
class Rva00270619 {public:void Rva00270619Clear(int);};
class ObjectCollisionFlags {public:
 unsigned bits[3];
 __forceinline unsigned test(int i)const{return bits[i>>5]&(1u<<(i&31));}
 __forceinline void set(int i){bits[i>>5]|=1u<<(i&31);}
};
struct Rva0028AC4EEntry {char pad[0x40];float m_float;};
class Rva001E46E1 {public:float rva001E48CF(Object*);};
class Rva002627E8 {public:float rva002627E8()const;};
class Rva001E415F {public:void rva001E415F(float,int);};
class Rva002D9531 {public:void rva002D9531(int);};
extern const int g_009BA4E4;
class Object
{
public:
 __forceinline unsigned testCollision(int i)const{return collisionFlags.test(i);}
 __forceinline void setCollision(int i){collisionFlags.set(i);}
 void rva002929F9(Object*);
 void rva00291A8C(float,float,float,const AsciiString &);
 void rva0028AE9B(int);
 float GetRelativeAngle(const Coord3D*)const;
 const Rva0028AC4EEntry *rva0028AC4E()const;
	void setDisabledUntil( DisabledType type, UnsignedInt frame );
	void setDisabled( DisabledType type );
	Bool clearDisabled( DisabledType type );
 void rva0028B292(int)const;void rva0028AE6D();void rva00290357();void rva0028B8A6(bool);
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
 bool rva00293926(KindOfType);
 signed char rva0028CE7B() const;
 bool canCrushOrSquishNoAlly(Object *, int);
 bool testStatus(ObjectStatusTypes) const;
 Player *getControllingPlayer() const;
 void rva0028BAC0();
 void rva0029004B();
 void tempRemoveObjectFromWorld();
 void restoreObjectToWorldInternal();
 void rva0028DCC4();
 void rva00290095();
private:
 __forceinline const ObjectCrushLevelsView *getTemplate() const { return m_template; }
 AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
 // Primary vptr at +0; all accessed fields are witnessed in retail.
 const ObjectCrushLevelsView *m_template; // +0x04
 unsigned char m_pad08[0x38-8];
 Coord3D position; // +0x38
 float angle; // +0x44
 unsigned char m_pad48[0x74-0x48];
 ObjectID id; // +0x74, native message object ID
 unsigned char m_pad78[0x84-0x78];
 Thing *drawable; // +0x84
 unsigned char m_pad88[0x110-0x88];
 ObjectCollisionFlags collisionFlags;
 unsigned char m_pad11C[0x124-0x11c];
 unsigned int mountedFlags; // +0x124, target bit22 selects alternate level
 unsigned char m_pad128[0x1C4-0x128];
 float initialZ; // +0x1C4
 BitFlags<11> disabledMask;
 unsigned int disabledTill[11];
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

// ?rva00294815@Object@@QAEDXZ
// BFME1 Object.cpp crusher/mounted-level donor9cbfb551 with native BFME2 deltas.
// Native294815..294898 RET0 and the rowed no-ally predicate establish Object
// receiver and signed-byte level role; the original getter name is unproved.
// Template5F9/5FB/5FE and Object124 bit22 are native witnesses. The target adds
// KindOf query132 when5FE is set, then pool attribute23 as a truncating bonus
// and clamps negative signed-byte sums. Attribute/mode names stay numeric.
// Byte extraction and an explicit hasBonus value reproduce the complete131B.
char Object::rva00294815() {
 const ObjectCrushLevelsView *tpl=getTemplate();
 if(tpl->gate5fe && !rva00293926((KindOfType)0x84)) return 0;
 char level;
 if(((unsigned char)(mountedFlags>>22)&1) && tpl->alternateCrusher != -1)
  level=tpl->alternateCrusher;
 else level=tpl->crusher;
 float bonus=0.0f;
 AttributeModifierPoolUpdate *pool=findAttributeModifierPoolUpdate();
 bool hasBonus=false;
 if(pool) hasBonus=pool->rva00403382(0x17,&bonus,0);
 if(!hasBonus) return level;
 level+=(char)(int)bonus;
 if(level<0) return 0;
 return level;
}

// WB CCB670 names Object.cpp tempRemoveObjectFromWorld at line4548.
// Native291B7C..291C20 RET0 independently witnesses this receiver, Object74/84,
// Drawable43C, PlayerList10 and MessageStream slot48. BFME1 Object.cpp9cbfb551
// supplies the removal-order semantic lead; hidden status51, message1005 and
// the target-only lifecycle calls are native. Opaque helper meanings stay open.
// ?tempRemoveObjectFromWorld@Object@@QAEXXZ
void Object::tempRemoveObjectFromWorld() {
 if(testStatus((ObjectStatusTypes)0x33)) return;
 Drawable *draw=(Drawable *)drawable;
 if(draw) {
  draw->setDrawableHidden(true);
  Player *localPlayer=ThePlayerList->local;
  if(getControllingPlayer()==localPlayer && draw->flag43c) {
   GameMessage *message=TheMessageStream->appendMessage((GameMessage::Type)0x3ed);
   message->appendObjectIDArgument(id);
  }
 }
 TheRadar->removeObject((Rva002D76C6Owner *)this);
 TheAI->getPathfinder()->RemoveObjectFromPathfindMap(this);
 if(theRadarWindowOverrideSource) ((Rva002D37Owner *)theRadarWindowOverrideSource)->rva002D373E((int)this);
 rva0028BAC0(); rva0029004B(); setStatus((ObjectStatusTypes)0x33,true);
}

// ?restoreObjectToWorldInternal@Object@@QAEXXZ
// WB CCB850 names Object.cpp internal restore. Native291C20..291C84 RET0
// tests and clears hidden51 while showing Drawable84 and restoring path-map
// occupancy; the native radar call is removeObject. Opaque calls stay numeric.
void Object::restoreObjectToWorldInternal() {
 if(!testStatus((ObjectStatusTypes)0x33)) return;
 if(drawable) ((Drawable *)drawable)->setDrawableHidden(false);
 TheRadar->removeObject((Rva002D76C6Owner *)this);
 TheAI->getPathfinder()->AddObjectToPathfindMap(this);
 if(theRadarWindowOverrideSource) ((Rva002D3726 *)theRadarWindowOverrideSource)->rva002D3726((Obj00526309 *)this);
 rva0028DCC4(); rva00290095(); setStatus((ObjectStatusTypes)0x33,false);
}

// BF1 f989 Object_clearDisabled_Thunk and ZH Object::clearDisabled are the
// semantic guides; native291CAC..291EB1 independently supplies all offsets,
// two136B audio lifetimes, condition14E bit1 and the calls used below.
class ObjectDisabledContain {
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
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual Object *getRider();
};
class ObjectDisabledAudio {
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
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void addAudioEvent(BfmeAudioEventPrefix136*);
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void *getMiscAudio();
};
class AudioManager;extern AudioManager *TheAudio;
Bool Object::clearDisabled(DisabledType type)
{
 if((int)type<0 || (int)type>=11) return false;
 if(!(unsigned char)reinterpret_cast<Rva001E4A4E*>(this)->rva001E4A4E(type))return false;
 if((int)type==6 || (int)type==2) {
  if((disabledMask.m_bits[0]&0x40) && (int)type!=6)goto no_sound;
  if((disabledMask.m_bits[0]&4) && (int)type!=2)goto no_sound;
  const unsigned char *kind=reinterpret_cast<const unsigned char*>(m_template);
  if(kind[0x108]&0x80) {
   BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4*>(reinterpret_cast<char*>(reinterpret_cast<ObjectDisabledAudio*>(TheAudio)->getMiscAudio())+0x44),0);
   reinterpret_cast<Rva002D9508*>(&event)->rva002D9508(&position);
   reinterpret_cast<ObjectDisabledAudio*>(TheAudio)->addAudioEvent(&event);
  } else if(kind[0x109]&8) {
   BfmeAudioEventPrefix136 event(*reinterpret_cast<const OpaqueRefElement4*>(reinterpret_cast<char*>(reinterpret_cast<ObjectDisabledAudio*>(TheAudio)->getMiscAudio())+0x4c),0);
   reinterpret_cast<Rva002D9508*>(&event)->rva002D9508(&position);
   reinterpret_cast<ObjectDisabledAudio*>(TheAudio)->addAudioEvent(&event);
  }
 }
no_sound:
 if((int)type!=3) rva0028B292(0);
 if(contain) {
  Object *rider=reinterpret_cast<ObjectDisabledContain*>(contain)->getRider();
  if(rider && disabledTill[type]==0x3fffffff)rider->clearDisabled(type);
 }
 disabledTill[type]=0;
 BitFlags<11> &mask=disabledMask;
 mask.m_bits[(unsigned int)type>>5]&=~(1u<<((int)type&31));
 if((int)type==1 && (reinterpret_cast<unsigned char*>(this)[0x14e]&2)) {
  *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this)+0x14c)&=~0x20000u;
  rva0028AE6D();
 }
 BitFlags<11> exceptions;
 memset(&exceptions,0,sizeof(exceptions));
 exceptions.m_bits[0]|=0x228;
 if(!mask.any() || mask.countInverseIntersection(exceptions)==0) {
  if(drawable)reinterpret_cast<Rva00270619*>(drawable)->Rva00270619Clear(1);
 }
 rva00290357();
 if(!mask.any())rva0028B8A6(false);
 return true;
}

// BFME1 f98983a7 Object_rva001CC250.cpp is the semantic guide; native
// BFME2 supplies the changed template/member offsets and modifier kinds.
class ObjectCollisionContain {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual int count(int);
};
static __forceinline float clampCollision(float low,float value,float high)
{return value<low?low:(value>high?high:value);}
void Object::rva002929F9(Object *other)
{
 if(other->flags438&1)return;
 if(drawable && TheAudio){
  BfmeAudioEventPrefix136 sound(reinterpret_cast<Drawable*>(drawable)->rva0028F912().value,0);
  reinterpret_cast<Rva002D9531*>(&sound)->rva002D9531(id);
  reinterpret_cast<ObjectDisabledAudio*>(TheAudio)->addAudioEvent(&sound);
 }
 float factor;float multiplier;
 Object *container=*reinterpret_cast<Object**>(reinterpret_cast<char*>(this)+0x274);
 if(container && (reinterpret_cast<const unsigned char*>(container->m_template)[0x115]&0x20)){
  container->rva002929F9(other);return;
 }
 {
  const char *tmpl=reinterpret_cast<const char*>(m_template);
  factor=*reinterpret_cast<const float*>(tmpl+0x514);
  float vertical=*reinterpret_cast<const float*>(tmpl+0x518);
  if(factor>0.0f){
   float relative=GetRelativeAngle(&other->position);
   if(relative>1.5707964f)relative=1.5707964f;
   relative=relative*0.3f+angle;
   const AsciiString &name=AsciiString("");
   other->rva00291A8C(relative*57.2957763671875f,factor,vertical,name);
  }
 }
 AIUpdateInterface *currentAI=ai;
 if(!currentAI)return;
 factor=*reinterpret_cast<const float*>(reinterpret_cast<const char*>(m_template)+0x510);
 float bonus=1.0f;
 AttributeModifierPoolUpdate *pool=findAttributeModifierPoolUpdate();
 if(pool && pool->rva00403448(9,&bonus,0,1))factor*=bonus;
 pool=other->findAttributeModifierPoolUpdate();
 if(pool && pool->rva00403448(0x1a,&bonus,0,1))factor*=bonus;
 if(factor<=0.0f)return;
 Rva0028AC4EEntry *locomotor=const_cast<Rva0028AC4EEntry*>(rva0028AC4E());
 if(!locomotor)return;
 float current=reinterpret_cast<Rva001E46E1*>(locomotor)->rva001E48CF(this);
 factor=reinterpret_cast<Rva002627E8*>(currentAI)->rva002627E8()*factor;
 if(reinterpret_cast<const unsigned char*>(m_template)[0x115]&0x20){
  ObjectTransformContain *contained=contain;
  if(contained){
   int count=reinterpret_cast<ObjectCollisionContain*>(contained)->count(0);
   if(count>1)factor=factor/count;
  }
 }
 multiplier=1.0f;
 pool=findAttributeModifierPoolUpdate();
 if(pool && pool->rva00403448(0x12,&multiplier,0,1)){
  float base=clampCollision(0.05f,*reinterpret_cast<const float*>(reinterpret_cast<const char*>(m_template)+0x50c),0.95f);
  multiplier=clampCollision(0.05f,base*multiplier,0.95f);
  factor=(1.0f-base)/(1.0f-multiplier)*factor;
 }
 float speed=current-factor;
 if(speed<0.0f)speed=0.0f;
 if(locomotor->m_float>speed)locomotor->m_float=speed;
 reinterpret_cast<Rva001E415F*>(locomotor)->rva001E415F(speed,g_009BA4E4);
}

#pragma function(sin,cos)
class PhysicsBehavior {public:void rva00390629(bool);};
class ObjectCollisionPhysics {
public:
 void rva00390629(bool);
 char pad[0x5c];bool blocked;
};
class Rva003909FAObj {public:void consume(void*,int,int);};
class ObjectCollisionAI {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual void slot133();
 virtual void slot134();
 virtual void slot135();
 virtual void slot136();
 virtual void slot137();
 virtual void slot138();
 virtual void slot139();
 virtual void slot140();
 virtual void slot141();
 virtual void slot142();
 virtual void slot143();
 virtual void slot144();
 virtual void slot145();
 virtual void slot146();
 virtual void slot147();
 virtual void slot148();
 virtual void slot149();
 virtual void slot150();
 virtual void slot151();
 virtual void slot152();
virtual void launch();
};
static const char *const collisionRockNames[3]={"NONE","CATAPULT_ROCK","TREBUCHET_ROCK"};
void Object::rva00291A8C(float degrees,float magnitude,float vertical,const AsciiString &rock)
{
 ObjectCollisionPhysics *physics=*reinterpret_cast<ObjectCollisionPhysics**>(reinterpret_cast<char*>(this)+0x25c);
 if(!physics)return;
 if(physics->blocked)return;
 if(*reinterpret_cast<const float*>(reinterpret_cast<const char*>(m_template)+0x610)>=100.0f)return;
 degrees*=0.017453292f;
 volatile float x=cos(degrees);
 float y=sin(degrees);
 Coord3D force;
 force.z=magnitude*vertical;
 force.x=x*magnitude;
 force.y=y*magnitude;
 reinterpret_cast<Rva003909FAObj*>(physics)->consume(&force,0,0);
 reinterpret_cast<PhysicsBehavior*>(physics)->rva00390629(true);
 if(!testCollision(95)){
  setCollision(95);rva0028AE6D();
 }
 AIUpdateInterface *listener=ai;
 if(listener)reinterpret_cast<ObjectCollisionAI*>(listener)->launch();
 int index=0;
 for(int i=0;i<3;++i){
  if(reinterpret_cast<const StringBase<char>*>(&rock)->compare(collisionRockNames[i])==0){index=i;break;}
 }
 rva0028AE9B(index);
}
