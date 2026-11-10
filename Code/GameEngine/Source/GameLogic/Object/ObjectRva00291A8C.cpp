// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?rva00291A8C@Object@@QAEXMMMABVAsciiString@@@Z
// Keep the float wrappers local; the matched launch body inlines them.
#define inline static inline
#include <math.h>
#undef inline
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

#include "../../../Include/GameLogic/PartitionData.h"

#include <float.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
class Matrix3D;
#include "../../Common/Thing/thing.h"
class Object;
struct Rva00287C21Other;
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
extern GameLogic *TheGameLogic;
struct ObjectTransformRegion {
 Coord3D lo, hi;
 bool contains(const Coord3D *p) const { return p->x > lo.x && p->x < hi.x && p->y > lo.y && p->y < hi.y; }
};
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
bool isPosDifferent(const Coord3D *,const Coord3D *);
bool isAngleDifferent(float,float);
class ObjectTransformContain {
public: virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void notify();
};
enum PathfindLayerEnum { LAYER_GROUND = 1 };
struct Rva002ED236Pos {
 float x,y,z;
 Rva002ED236Pos(const Coord3D &p) { x=p.x;y=p.y;z=p.z; }
 Rva002ED236Pos(const Rva002ED236Pos &p) { x=p.x;y=p.y;z=p.z; }
 ~Rva002ED236Pos() {}
};
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;


#include "../../../Include/Common/Rva001E3591.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../Include/GameLogic/Module/AttributeModifierPoolUpdate.h"
enum KindOfType { KINDOF_VIEW_UNKNOWN = 0 };
struct ObjectCrushLevelsView {
 char unknown00[0x5f9];
 char crusher,crushable,alternateCrusher,alternateCrushable;
 char unknown5fd;
 bool gate5fe;
};

#include "Common/BfmeAudioEventPrefix136.h"
#include <string.h>
class Rva002D9508 {public:void rva002D9508(const void*);};
class Object; class Player; class RadarWindowOverrideSource;
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../Include/Common/MessageStream.h"
extern MessageStream *TheMessageStream;
struct Rva002D76C6Owner;
#include "../../../Include/Common/Radar.h"
extern Radar *TheRadar;
struct Obj00526309;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

template <int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
 bool any()const;
 int countInverseIntersection(const BitFlags &)const;
};


class ObjectCollisionFlags {public:
 unsigned bits[3];
 __forceinline unsigned test(int i)const{return bits[i>>5]&(1u<<(i&31));}
 __forceinline void set(int i){bits[i>>5]|=1u<<(i&31);}
};
struct Rva0028AC4EEntry {char pad[0x40];float m_float;};
extern int BfmeLogicFramesPerSecond;
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
 void rva0028B292(int)const;void rva0028AE6D();void checkDisabledStatus();void rva0028B8A6(bool);
	void makeDirty( void );
	void setScriptStatus( ObjectScriptStatusBit bit, Bool set );
	void setStatus( ObjectStatusTypes bit, Bool flag );
	Bool rva00292ED0( DisabledType type );
	void rva00292EB3( DisabledType type );
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);

protected:
 virtual void reactToTransformChange(const Matrix3D *, const Coord3D *, float);
public:
 void setTriggerAreaFlagsForChangeInPosition();
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
extern BitFlags<45> OBJECT_STATUS_MASK_NONE;

// BF1 f989 Object_clearDisabled_Thunk and ZH Object::clearDisabled are the
// semantic guides; native291CAC..291EB1 independently supplies all offsets,
// two136B audio lifetimes, condition14E bit1 and the calls used below.
class AudioManager;extern AudioManager *TheAudio;
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
#pragma function(sin,cos)
static const char *const collisionRockNames[3]={"NONE","CATAPULT_ROCK","TREBUCHET_ROCK"};

