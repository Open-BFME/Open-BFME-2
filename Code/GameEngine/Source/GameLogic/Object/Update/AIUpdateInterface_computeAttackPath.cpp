// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?computeAttackPath@AIUpdateInterface@@QAE_NPAVPathfindServicesInterface@@PBVObject@@PBUCoord3D@@@Z
// Retail 0x00266AA2..0x00267179, 1753 bytes, RET 0xC.
// Identity: WorldBuilder 0x00E45730 AIUpdateInterface::computeAttackPath,
// AIUpdate.cpp assertions 3262..3304 and matched call relationships.
// Semantic guide: Zero Hour AIUpdate.cpp and BFME1 f98983a7d game/AIUpdate.cpp.
// Target deltas: path-query completion, attack service flags, model kinds,
// state 16, ignored obstacle, and Object final-goal forwarding are native reads.
// Float gates prove native distance thresholds 400/100 and short-path length30.
// Native layout: AI path140/timestamp160/ignored164/blocked16C/locomotor1CC,
// current locomotor1F0/stuck3B8/attack3CD; node position0C/optimized08.
// Inline integer getValidSurfaces keeps MOV EAX+TEST AL8; direct field test folds.
// WorldBuilder names computeApproachTarget; computePath identity follows the donor
// contact-weapon callsite and its native body, with unnamed WB strings twin.
// Their bodies remain unrowed; bindings are candidate pins with target call evidence.
#include <stdio.h>
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_32 = 0x32,
	OBJECT_STATUS_39 = 0x39
};
enum KindOfType
{
	KINDOF_84 = 0x84
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern GameLogic *TheGameLogic;

#define CRITTER_TRACE(s) \
	if (g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, s); }
#define CRITTER_DETAIL() \
	if (theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, "m_path=%s, m_locomotorSet=%s, destination=%g,%g,%g", \
		m_path ? "VALID" : "NULL", m_locomotorSet.m_name.str(), destination->x, destination->y, destination->z); }
#define CRITTER_NEWDETAIL() \
	if (theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, "m_path=%s, theNewPath=%s, m_locomotorSet=%s, destination=%g,%g,%g", \
		m_path ? "VALID" : "NULL", theNewPath ? "VALID" : "NULL", m_locomotorSet.m_name.str(), destination->x, destination->y, destination->z); }
#define CRITTER_TRACEDETAIL(s) \
	if (g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, s); CRITTER_DETAIL(); }
#define CRITTER_TRACENEW(s) \
	if (g_00E03745 && theLogicRandomLogFile) { fprintf(theLogicRandomLogFile, s); CRITTER_NEWDETAIL(); }

#include "../../../../../Libraries/Include/Lib/Region3D.h"

#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../Common/Thing/thing.h"

class Weapon;
enum WeaponSlotType { SLOT=0 };
// Target model-condition words begin at Object+0x10C. The indexed accessor
// preserves the shared mask calculation used by the retail setter.
class FacingConditionBits {
public:
 unsigned int test(int bit) const { return words[bit>>5] & (1U<<(bit&31)); }
 void set(int bit) { words[bit>>5] |= 1U<<(bit&31); }
 unsigned int words[19];
};

class Object : public Thing
{
public:
	Int rva0028B511() const;
 void rva0028AE6D();
 __forceinline unsigned int hasFacingMask(unsigned int bit) const { return m_conditions.test(bit); }
 __forceinline void addFacingMask(unsigned int bit) { m_conditions.set(bit); }
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 Bool isSignificantlyAboveTerrain() const;
 Real rva002637E2(const Coord3D*,const Coord3D*)const;
 void rva0028AD32();
 void rva0028ACDC(int); // the layer
	signed char rva0028CE7B() const; // the crushable level
	Bool testStatus(ObjectStatusTypes status) const;
	Bool isKindOf(KindOfType kind) const;
	UnsignedInt getID() const { return m_id; }
private:
	unsigned char m_pad60[0x74 - 0x60];
	UnsignedInt m_id; // +0x74
 unsigned char m_pad078[0x10c - 0x78];
 FacingConditionBits m_conditions; // +0x10c
};

#include "../../../../Include/GameLogic/LocomotorClass.h"



struct Rva003642DFNode;
#include "../../../../Include/GameLogic/Rva003642DFResult.h"
class Rva0008BB38FloatField;
#include "../../../../Include/GameLogic/PathNode.h"
class Path { public:
 Path(); Rva003642DFResult rva00364521(const Rva0008BB38FloatField *arg);
 void prependNode(const Coord3D*,PathfindLayerEnum,int);
 unsigned int pad; PathNode *head,*tail; Bool optimized, m_blockedByAlly; char rest[0x28-14];
};
#include "../../../../Include/GameLogic/Weapon.h"
// updateLastNode, rowed under its address name.
#include "../../../../Include/GameLogic/AIPathfind.h"


struct AIData
{
	unsigned char m_pad00[0xB9];
	Bool m_fieldB9; // +0xB9
};

#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

struct TBridgeAttackInfo { Coord3D attackPoint1,attackPoint2; };
#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

Bool Rva001E3679(Int layer);
Int Rva002EDE5B(void *obj, Coord3D *pos);

#include "../../../../Include/Common/StateMachineClass.h"


#include "../../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;


class Rva00265254 {
public:
 Rva00265254(unsigned int,unsigned int,unsigned int,unsigned int);
 int bits[19];
};
#include "../../../../Include/GameLogic/Module/Rva001E42F2.h"

struct FacingDirection : Coord3D {
 FacingDirection(float a,float b,float c) { x=a;y=b;z=c; }
 ~FacingDirection() {}
};

static __forceinline void setFacingCondition(Object *obj,unsigned int bit) {
 if(obj->hasFacingMask(bit)==0) { obj->addFacingMask(bit);obj->rva0028AE6D(); }
}

// Retail 0x0026717B..0x00267266, 235 bytes, RET 0. Direct callers in
// AIUpdateInterface::doLocomotor establish the owner and no-argument ABI.
// WorldBuilder 0x00E4B180 supplies the model-condition bit indices and object
// relationships; its assertion labels do not establish this helper's original
// name. Native reads prove module+8, template+0x11F bit7, matrix+0xC/+0x1C/+0x2C,
// and Object condition word+0x134. The static direction at 0x00DFEB40 has a
// guarded constructor and a registered empty cleanup at 0x007B77CD; the derived
// FacingDirection is a local lifetime view, not a claim about its original type.
// The canonical Coord3D Normalize and existing bitset/reset/notifier providers
// preserve all call identities. Dot-product order is Z+Y+X, including NaNs.
void AIUpdateInterface::rva0026717B()
{
 Object *obj=getObject();
 if(((obj->m_template->m_kindof[5] & 0x80000000U) != 0)) {
  static FacingDirection direction(0.5f,0.5f,0.0f);
  direction.Normalize();
  ((Rva001E42F2*)obj)->rva001E42F2(Rva00265254(0,0x151,0x152,0x153).bits);
  const float *matrix=(const float*)((const char*)obj+0x0c);
  Coord3D axis;
  axis.x=matrix[0];axis.y=matrix[4];axis.z=matrix[8];
  float dot=direction.z*axis.z+direction.y*axis.y+direction.x*axis.x;
  if(dot>0.0f) setFacingCondition(obj,0x153); else setFacingCondition(obj,0x152);
 }
}
