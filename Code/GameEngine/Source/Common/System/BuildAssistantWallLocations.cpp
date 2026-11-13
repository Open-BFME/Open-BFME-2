// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHs /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// platformsdk
// BuildAssistantWallLocations.cpp -- BuildAssistant::rva0039380F (retail 0x0039380F,
// 2217 bytes), the wall-segment placement walk split out of BuildAssistant.cpp.
//
// Identity (target evidence): WB F9C000 is the debug twin of the same member; its frame
// shows delta, delta2, current, unit and previous as function-scope locals and unit as a
// member-wise copy of delta with z cleared. Declarations are carried from the owner TU
// BuildAssistant.cpp (BFME 1 / Zero Hour donor views); the body is reconstructed from
// retail and the WB twin.
//
// Coord3D::length/normalize and Coord2D::toAngle get visible noinline bodies here: the
// calls stay out of line (retail 0x3571, 0x35B6, 0x5923) but c2 then sees that `this`
// does not escape, which gives retail's stack colouring (sub esp,0xe8).
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <list>
class Drawable;
#include "../../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL{
template <> __declspec(noinline)
_List_base<Drawable*,allocator<Drawable*> >::_List_base(const allocator<Drawable*>&__a)
: _M_node(__a,(_List_node<Drawable*>*)0)
{
_List_node<Drawable*>*node=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
node->_M_next=node;
node->_M_prev=node;
_M_node._M_data=node;
}
template <> _List_base<Drawable*,allocator<Drawable*> >::~_List_base();
template <> __declspec(noinline)_List_node<Drawable*>*
list<Drawable*>::_M_create_node(Drawable*const&value)
{
_List_node<Drawable*>*node=(_List_node<Drawable*>*)g_freelistPool00DBA5E0.pop();
_Construct(&node->_M_data,value);
return node;
}
}
namespace _STL{
template <class T,class Traits>
static inline bool operator!=(const _List_iterator<T,Traits>&a,
const _List_iterator<T,Traits>&b)
{return a._M_node !=b._M_node;}
}
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../../Libraries/Include/Lib/Coord2DCtorView.h"
#include "../GameLogicObjectLookupView.h"
#include "../PartitionRangeQueryCallView.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef int Color;
#define GameMakeColor(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))
enum KindOfType
{
KINDOF_2=2,
KINDOF_SHRUBBERY=6,
KINDOF_STRUCTURE=7,
KINDOF_DOZER=14,
KINDOF_15=15,
KINDOF_30=30,
KINDOF_CLEARED_BY_BUILD=51,
KINDOF_58=58,
KINDOF_85=85,
KINDOF_86=86,
KINDOF_INERT=89,
KINDOF_104=104,
KINDOF_149=149,
KINDOF_152=152,
KINDOF_NOT_SELLABLE=154,
KINDOF_156=156,
KINDOF_157=157,
KINDOF_188=188,
KINDOF_189=189
};
enum ObjectStatusTypes
{
OBJECT_STATUS_UNDER_CONSTRUCTION=2,
OBJECT_STATUS_UNSELECTABLE=3,
OBJECT_STATUS_SOLD=19
};
enum DamageType
{
DAMAGE_UNRESISTABLE=8
};
enum DeathType
{
DEATH_8=8
};
enum BodyDamageType
{
BODY_PRISTINE,
BODY_DAMAGED,
BODY_REALLYDAMAGED
};
typedef UnsignedInt PlayerMaskType;
const PlayerMaskType PLAYERMASK_ALL=0xFFFFF;
enum CommandSourceType
{
CMD_FROM_PLAYER,
CMD_FROM_SCRIPT,
CMD_FROM_AI
};
enum PathfindLayerEnum
{
LAYER_INVALID=0,
LAYER_GROUND=1,
LAYER_17=17
};
enum CanMakeType
{
CANMAKE_OK,
CANMAKE_NO_PREREQ,
CANMAKE_NO_MONEY,
CANMAKE_FACTORY_IS_DISABLED,
CANMAKE_QUEUE_FULL,
CANMAKE_PARKING_PLACES_FULL,
CANMAKE_MAXED_OUT_FOR_PLAYER,
CANMAKE_7
};
enum LegalBuildCode
{
LBC_OK=0,
LBC_NO_CLEAR_PATH=2,
LBC_TOO_CLOSE_TO_SUPPLIES=3,
LBC_NOT_FLAT_ENOUGH=5,
LBC_RESTRICTED_TERRAIN=6,
LBC_OBJECTS_IN_THE_WAY=8,
LBC_9=9
};
enum CellShroudStatus
{
CELLSHROUD_CLEAR
};
enum ObjectScriptStatusBit
{
OBJECT_STATUS_SCRIPT_DISABLED=0x01,
OBJECT_STATUS_SCRIPT_UNPOWERED=0x02
};
enum GUICommandType
{
GUI_COMMAND_DOZER_CONSTRUCT=1,
GUI_COMMAND_UNIT_BUILD=3,
GUI_COMMAND_46=46,
GUI_COMMAND_53=53
};
enum CommandOption
{
NEED_UPGRADE=0x40
};
enum UpgradeType
{
UPGRADE_TYPE_PLAYER,
UPGRADE_TYPE_OBJECT
};
enum{MAX_COMMANDS_PER_SET=32};
class Player;
class Object;
#include "../../../../Libraries/Include/Lib/Region3D.h"
class Team;
struct Rva002A7557In;
class Drawable
{
public:
void setAnimationLoopDuration(UnsignedInt numFrames);
};
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Include/Common/Geometry.h"
#include "../../../Include/Common/BfmeThingTemplateShadowSelector.h"
class ModuleData;
class ThingTemplate
{
public:
const AsciiString&getName()const{return m_nameString;}
const AsciiString&getCommandSetString()const{return m_commandSetString;}
__forceinline Bool isKindOfByte(KindOfType t)const{return(((const unsigned char*)m_kindOf)[t >> 3]&(1U <<(t& 7)))!=0;}
Bool isEquivalentTo(const ThingTemplate*tt)const;
const GeometryInfo&getTemplateGeometryInfo()const{return m_geometryInfo;}
__forceinline UnsignedInt isKindOf(KindOfType t)const{return m_kindOf[t >> 5]&(1U <<(t& 31));}
__declspec(dllimport)__forceinline UnsignedInt getMaxSimultaneousOfType()const{return m_maxSimultaneousOfType;}
Real friend_calcVisionRange()const{return m_visionRange;}
UnsignedShort getRefundValue()const{return m_refundValue;}
Int rva0033A69A(const Player*player,Int a,Int b)const;
const ModuleData*rva0033B427(Int unused)const;
private:
unsigned char m_pad000[0x64];
AsciiString m_nameString;
unsigned char m_pad068[8];
AsciiString m_commandSetString;
unsigned char m_pad074[0xA0 - 0x74];
GeometryInfo m_geometryInfo;
unsigned char m_pad0FC[0x108 - 0xFC];
UnsignedInt m_kindOf[8];
unsigned char m_pad128[0x4AC - 0x128];
Real m_visionRange;
unsigned char m_pad4B0[0x5DC - 0x4B0];
UnsignedShort m_refundValue;
UnsignedShort m_pad5DE;
UnsignedShort m_maxSimultaneousOfType;
};
#include "../../../Include/Common/Upgrade.h"
struct UpgradeTemplateList
{
const UpgradeTemplate**m_begin;
const UpgradeTemplate**m_end;
const UpgradeTemplate**m_capacity;
UnsignedInt size()const{return(UnsignedInt)(m_end - m_begin);}
const UpgradeTemplate*operator[](UnsignedInt i)const{return m_begin[i];}
};
class CommandButton
{
public:
GUICommandType getCommandType()const{return m_command;}
UnsignedInt getOptions()const{return m_options;}
const ThingTemplate*rva0035B570()const;
const UpgradeTemplateList&getNeededUpgrades()const{return m_neededUpgrades;}
Bool isAnyUpgradeEnough()const{return m_anyUpgrade;}
private:
unsigned char m_pad00[0x14];
GUICommandType m_command;
unsigned char m_pad18[0x1C - 0x18];
UnsignedInt m_options;
unsigned char m_pad20[0x28 - 0x20];
UpgradeTemplateList m_neededUpgrades;
Bool m_anyUpgrade;
};
class CommandSet
{
public:
const CommandButton*getCommandButton(Int i)const;
};
#include "../../../Include/Common/Rva0031D5F8.h"
#include "../../../Include/GameClient/ControlBar.h"
extern ControlBar*TheControlBar;
#include "../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../Include/GameLogic/Module/ProductionUpdateInterface.h"
#include "../../../Include/GameLogic/Module/ContainModule.h"
class Rva00346BC0
{
public:
UnsignedInt m_bits[4];
};
#include "../../../Include/GameLogic/Module/ProductionUpdateClass.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
class G00DFF080Obj
{
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
	virtual void addFactionBib(Object *factionBuilding, Bool highlight, Real extra = 0); // +0x28
};
extern G00DFF080Obj*g_00DFF080;
struct CreateMask
{
CreateMask(){memset(m_words,0,sizeof(m_words));}
void setBit(Int bit){m_words[bit >> 5]|=1U <<(bit& 31);}
UnsignedInt m_words[4];
};
enum Relationship
{
ENEMIES=0,
NEUTRAL,
ALLIES
};
#include "../../../Include/GameLogic/Module/BodyModule.h"
#include "../Thing/thing.h"
class Object : public Thing
{
public:
__forceinline UnsignedInt isKindOf(KindOfType t)const{return m_template->isKindOf(t);}
Bool isEffectivelyDead()const{return(m_privateStatus& 1)!=0;}
__declspec(dllimport)__forceinline Bool testScriptStatusBit(ObjectScriptStatusBit b)const{return(m_scriptStatus&b)!=0;}
AIUpdateInterface*getAI()const{return m_ai;}
void*rva0028BD17()const;
void*rva0028BC58(Int which);
Player*getControllingPlayer()const;
void setProducer(Object*obj);
void*rva0028BCF4()const;
void rva0028B4CE(PathfindLayerEnum layer);
Int get45C()const{return m_45C;}
Relationship getRelationship(const Object*that)const;
ObjectID getID()const{return m_id;}
ObjectID get7C()const{return m_7C;}
Bool testStatus(ObjectStatusTypes bit)const;
void rva0028CDEB(const Rva00346BC0&mask,Bool set);
__declspec(dllimport)__forceinline void setConstructionPercent(Real percent){m_constructionPercent=percent;}
ContainModuleInterface*getContain()const{return m_contain;}
BehaviorModule**getBehaviorModules()const{return m_behaviors;}
const AsciiString*rva00290E67()const;
Bool rva00290D2B(const UpgradeTemplate*upgrade)const;
const GeometryInfo&getGeometryInfo()const{return m_geometryInfo;}
BodyModuleInterface*getBodyModule()const{return m_body;}
Real getBuildCost()const{return m_buildCost;}
Bool rva0028C264(Int*killerID,Int which);
void kill(DamageType damageType,DeathType deathType);
Team*getTeam()const{return m_team;}
void*rva0029439D();
private:
unsigned char m_pad060[0x74 - 0x60];
ObjectID m_id;
unsigned char m_pad078[4];
ObjectID m_7C;
unsigned char m_pad080[0xA8 - 0x80];
GeometryInfo m_geometryInfo;
unsigned char m_pad104[0x244 - 0x104];
BehaviorModule**m_behaviors;
unsigned char m_pad248[0x250 - 0x248];
ContainModuleInterface*m_contain;
BodyModuleInterface*m_body;
AIUpdateInterface*m_ai;
unsigned char m_pad25C[0x280 - 0x25C];
Real m_constructionPercent;
unsigned char m_pad284[0x304 - 0x284];
Team*m_team;
unsigned char m_pad308[0x324 - 0x308];
Real m_buildCost;
unsigned char m_pad328[0x437 - 0x328];
unsigned char m_scriptStatus;
unsigned char m_privateStatus;
unsigned char m_pad439[0x45C - 0x439];
Int m_45C;
};
#include "../../../Include/GameLogic/Rva002A7461.h"
#include "../../../Include/GameLogic/Rva0037E6E8.h"
#include "../../../Include/GameLogic/Module/Rva0037E421.h"
class Rva0039B7AD;
class Rva0039B795;
#include "../../../Include/GameLogic/Module/Rva003B0D7C.h"
#include "../../../Include/Common/ScoreKeeperClass.h"
class Player
{
public:
__declspec(dllimport)__forceinline Rva003B0D7C*getMoney(){return&m_money;}
void countObjectsByThingTemplate(Int numTmplates,const ThingTemplate*const*things,Bool ignoreDead,Int*counts,Bool ignoreUnderConstruction)const;
Int iterateObjects(Int(*func)(Object*,void*),void*userData)const;
Team*getDefaultTeam()const{return m_defaultTeam;}
void onStructureCreated(Object*builder,Object*structure);
void onStructureConstructionComplete(Object*builder,Object*structure,Bool isRebuild);
void onUnitCreated(Object*factory,Object*unit);
Bool canBuild(const ThingTemplate*tmplate)const;
Bool rva002AB87D(const UpgradeTemplate*upgrade)const;
__declspec(dllimport)__forceinline Color getPlayerColor()const{return m_color;}
Int getPlayerIndex()const{return m_playerIndex;}
void rva002AF614(void*points);
ScoreKeeper*getScoreKeeper(){return&m_scoreKeeper;}
Relationship getRelationship(const Team*that)const;
unsigned char m_pad000[0x54];
Int m_playerIndex;
unsigned char m_pad058[0x60 - 0x58];
Rva002A7461 m_rva060;
unsigned char m_pad061[0x90 - 0x61];
Rva003B0D7C m_money;
unsigned char m_pad098[0x280 - 0x9C];
Color m_color;
unsigned char m_pad284[0x2EC - 0x284];
Team*m_defaultTeam;
unsigned char m_pad2F0[0x3BC - 0x2F0];
ScoreKeeper m_scoreKeeper;
unsigned char m_pad3C0[0x738 - 0x3C0];
union
{
Rva0037E6E8 m_revivalCost;
Rva0037E421 m_revivalTracker;
};
};
class ObjectSellInfo
{
public:
ObjectSellInfo(void): m_id(INVALID_OBJECT_ID),m_sellFrame(0){}
virtual ~ObjectSellInfo(void);
__forceinline void deleteInstance(){::delete this;}
ObjectID m_id;
UnsignedInt m_sellFrame;
};
typedef _STL::list< ObjectSellInfo* > ObjectSellList;
typedef ObjectSellList::iterator ObjectSellListIterator;
class Rva0039205C;
#include "../../../Include/Common/BuildAssistantClass.h"
extern BuildAssistant*TheBuildAssistant;
enum ObjectID; class ThingFactory
{
public:
const ThingTemplate*findTemplate(const AsciiString&name);
Object*newObject(const ThingTemplate*tmplate,Team*team,const CreateMask*statusBits,ObjectID flag);
};
extern ThingFactory*TheThingFactory;
class GlobalData
{
public:
unsigned char m_pad000[0xA68];
Real m_minDistFromEdgeOfMapForBuild;
Real m_supplyBuildBorder;
Real m_allowedHeightVariationForBuilding;
unsigned char m_padA74[0xA94 - 0xA74];
Int m_wallCount;
unsigned char m_padA98[0xB94 - 0xA98];
Real m_sellPercentage;
};
extern GlobalData*TheWritableGlobalData;
#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface*TheGameText;
#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI*TheInGameUI;
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic*TheTerrainLogic;
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI*TheAI;
extern PartitionManager*ThePartitionManager;
extern GameLogic*TheGameLogic;
enum DistanceCalculationType
{
FROM_CENTER_2D,
FROM_CENTER_3D,
FROM_BOUNDINGSPHERE_2D,
FROM_BOUNDINGSPHERE_3D
};
#include "../../../Include/GameLogic/PartitionFilter.h"
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual Bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08; // +0x08
	BfmeFixedStorage0004543D m_24; // +0x24
};
Real GetGameLogicRandomValueReal(Real low,Real high,char*file,Int line);
#define BUILDASSISTANT_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\System\\BuildAssistant.cpp"
#define PI 3.14159265359f
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include "../../../Include/GameClient/DrawableList.h"
class PickAndPlayInfo;
#include "../../../Include/Common/MessageStream.h"
bool pickAndPlayUnitVoiceResponse(const DrawableList*list,GameMessage::Type messageType,
PickAndPlayInfo*info);
struct ProductionCountData
{
public:
	UnsignedInt count; // +0x00
	const ThingTemplate *type; // +0x04
};
static Int countInProduction(Object*obj,void*userData)
{
ProductionUpdateInterface*pui=ProductionUpdate::getProductionUpdateInterfaceFromObject(obj);
if(pui)
{
ProductionCountData*productionCountData=(ProductionCountData*)userData;
productionCountData->count +=pui->countUnitTypeInQueue(productionCountData->type);
}
return 1;
}
#include "../../../Include/Common/SampleBuildData.h"
inline void addCoord3D(Coord3D*sum,const Coord3D*a)
{
sum->x +=a->x;
sum->y +=a->y;
sum->z +=a->z;
}
static void checkSampleBuildLocation(const Coord3D*samplePoint,void*userData)
{
SampleBuildData*sampleData=(SampleBuildData*)userData;
Bool isK188=sampleData->build->isKindOf(KINDOF_188)!=0;
Bool isK189=sampleData->build->isKindOf(KINDOF_189)!=0;
if(sampleData->terrainRestricted&& !isK188)
return;
Bool isValid;
Bool isBlocked=FALSE;
Int cellType;
if(isK189)
TheAI->pathfinder()->GetCellType((int)samplePoint,&isValid,&isBlocked,&cellType,
TheTerrainLogic->getHighestLayerForDestination(samplePoint,FALSE));
else
TheAI->pathfinder()->GetCellType((int)samplePoint,&isValid,&isBlocked,&cellType,1);
sampleData->terrainRestricted=FALSE;
if(isValid)
{
if(isBlocked)
sampleData->terrainRestricted=TRUE;
else
{
switch(cellType)
{
case 0:
break;
case 5:
break;
case 4:
{
ObjectID id=(ObjectID)(Int)TheAI->pathfinder()->getObstacleID(
TheTerrainLogic->getHighestLayerForDestination(samplePoint,FALSE),(int)samplePoint);
Object*obj=TheGameLogic->findObjectByID(id);
if(obj==NULL || obj->m_template->isKindOf(KINDOF_INERT))
sampleData->terrainRestricted=TRUE;
break;
}
case 2:
sampleData->terrainRestricted=TRUE;
break;
case 1:
case 7:
if(!isK188)
sampleData->terrainRestricted=TRUE;
break;
default:
sampleData->terrainRestricted=TRUE;
break;
}
}
}
else
sampleData->terrainRestricted=TRUE;
Bool isWater=FALSE;
if(isK188)
{
isWater=TheTerrainLogic->isUnderwater(samplePoint->x,samplePoint->y);
if(isWater)
{
sampleData->waterSamples +=1.0f;
addCoord3D(&sampleData->waterSum,samplePoint);
}
else
{
sampleData->landSamples +=1.0f;
addCoord3D(&sampleData->landSum,samplePoint);
}
}
if(!isWater)
{
if(samplePoint->z < sampleData->loZ)
sampleData->loZ=samplePoint->z;
if(samplePoint->z > sampleData->hiZ)
sampleData->hiZ=samplePoint->z;
}
if(TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild > 0.0f)
{
if(samplePoint->x < sampleData->mapRegion.lo.x + TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild
|| samplePoint->x > sampleData->mapRegion.hi.x - TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild
|| samplePoint->y < sampleData->mapRegion.lo.y + TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild
|| samplePoint->y > sampleData->mapRegion.hi.y - TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild)
{
sampleData->terrainRestricted=TRUE;
}
}
}
#define MAP_XY_FACTOR (10.0f)
static Real s_maxWaterLandSampleRatio=6.0f;
extern PartitionManager*TheShroudManager;
Bool Rva003919F6Connected(Object*a,Object*b);
// ?rva00391A70@BuildAssistant@@UAE_NPBVThingTemplate@@PBVObject@@@Z @0x00391A70 (49B)
typedef void(*IterateFootprintFunc)(const Coord3D*,void*);
__forceinline void rotateFootprint(Matrix3D&matrix3D,float theta)
{
float tmp1,tmp2;
float c=cosf(theta);
float s=sinf(theta);
tmp1=matrix3D[0][0];
tmp2=matrix3D[0][1];
matrix3D[0][0]=(float)((c ? c : c)*tmp1 + s*tmp2);
matrix3D[0][1]=(float)(-s*tmp1 +(c ? c : c)*tmp2);
tmp1=matrix3D[1][0];
tmp2=matrix3D[1][1];
matrix3D[1][0]=(float)((c ? c : c)*tmp1 + s*tmp2);
matrix3D[1][1]=(float)(-s*tmp1 +(c ? c : c)*tmp2);
tmp1=matrix3D[2][0];
tmp2=matrix3D[2][1];
matrix3D[2][0]=(float)((c ? c : c)*tmp1 + s*tmp2);
matrix3D[2][1]=(float)(-s*tmp1 +(c ? c : c)*tmp2);
}
#include "../../../Include/Common/Rva00293330.h"
class Rva0039380FModule{
public:
virtual void slot0();
virtual const ThingTemplate*getSegment(Int index);
virtual const ThingTemplate*getHub();
virtual const ThingTemplate*getEnd();
virtual const ThingTemplate*getTerrainPiece();
virtual void slot5();virtual void slot6();virtual void slot7();
virtual void slot8();virtual void slot9();virtual void slot10();
virtual Real getInitialStep();
virtual Bool getRange(Real*range);
};
class Rva00260E2AFilter : public Rva000421C8{
public:
Rva00260E2AFilter(Player*player): m_player(player){}
virtual Bool allow(Object*obj);
virtual Int getPlayerMask();
Player*m_player;
};
struct Rva003920F7Src
{
public:
	int a; // +0x00
	int b; // +0x04
	int c; // +0x08
};
class Rva003920F7
{
public:
	void rva003920F7(UnsignedInt index, const Rva003920F7Src *src);
};
class Rva0039205C{
public:
void rva00392129(UnsignedInt index,Real angle);
void rva0039215F(UnsignedInt index,const AsciiString&name);
void rva00392196(UnsignedInt index,Int status);
void rva003921C8(UnsignedInt index,unsigned char flag);
Int rva00392D71(Int index);
void rva00392CAC();
UnsignedInt count;
Int cost;
void*array;
Bool endAtObject,startNewHub;
unsigned char padE[2];
Int status;
ObjectID endID;
__forceinline void setPos(UnsignedInt index,const Coord3D*p){((Rva003920F7*)this)->rva003920F7(index,(const Rva003920F7Src*)p);}
};
__declspec(noinline) inline float Coord3D::length() const { return (float)sqrt(x*x+y*y+z*z); }
__declspec(noinline) inline void Coord3D::normalize() { float len=length(); if(len!=0.0f){ float scale=1.0f/len; x*=scale; y*=scale; z*=scale; } }
inline float Coord2D::length() const { return (float)sqrt(x*x+y*y); }
// Use retail's float ACos helper (0x00873940), as the rowed Coord2D owner does.
// Calling CRT double acos here emitted a divergent out-of-line toAngle copy.
float ACos(float value);
__declspec(noinline) inline float Coord2D::toAngle() const { float len=length(); if(len==0.0f) return 0.0f; const float raw=x/len; float cosine; if(raw<-1.0f) cosine=-1.0f; else if(raw>1.0f) cosine=1.0f; else cosine=raw; if(y<0.0f) return -ACos(cosine); return ACos(cosine); }
Real normalizeAngle(Real angle);
Bool BuildAssistant::rva0039380F(Rva0039205C*out,Object*builder,const Coord3D*start,const Coord3D*end,UnsignedInt key)
{
if((builder==0)|| !start || !end)return false;
if(!builder->m_template->isKindOfByte(KINDOF_156))return false;
Rva0039380FModule*module=(Rva0039380FModule*)((Rva00293330*)builder)->rva00293330(key);
if(!module)return false;
const ThingTemplate*hubTemplate=module->getHub();
if((hubTemplate==0))return false;
Object*nearObject;
nearObject=ThePartitionManager->getClosestObject(end,20.f,FROM_BOUNDINGSPHERE_3D,
Rva00260E2AFilter(builder->getControllingPlayer()).link(&Rva0004584D(
*(BfmeFixedStorage0004543D*)&Rva00045411BitSet(0,KINDOF_156),*(BfmeFixedStorage0004543D*)&KINDOFMASK_NONE)));
Bool endAtObject=false;
Coord3D endPoint;endPoint.x=end->x;endPoint.y=end->y;endPoint.z=end->z;
Real nearRadius=0.f;
Real hubHalf=hubTemplate->getTemplateGeometryInfo().field28;
if(nearObject){
nearRadius=nearObject->getGeometryInfo().getBoundingCircleRadius();
Rva0039380FModule*nearModule=(Rva0039380FModule*)((Rva00293330*)nearObject)->rva00293330(0);
if(nearModule)nearRadius=nearModule->getInitialStep();
if(nearRadius >=hubHalf*.666f){
endAtObject=true;
endPoint=*nearObject->getPosition();
out->endID=nearObject->getID();
}
}
Bool startNewHub=!endAtObject;
Real range=99990.f;
_STL::vector<Coord3D> points;
if(module->getRange(&range)){
Player*owner=builder->getControllingPlayer();
if(owner)owner->rva002AF614(&points);
}
Coord3D delta;delta.x=endPoint.x-start->x;delta.y=endPoint.y-start->y;delta.z=0.f;
Coord2D delta2;delta2.x=endPoint.x-start->x;delta2.y=endPoint.y-start->y;
Real angle=normalizeAngle(delta2.toAngle()+1.5707964f);
Coord3D current;current.x=start->x;current.y=start->y;current.z=start->z;
Coord3D unit;unit.x=delta.x;unit.y=delta.y;unit.z=0.f;
unit.normalize();
if(nearRadius > hubHalf){
endPoint.x -=(nearRadius-hubHalf)*unit.x;
endPoint.y -=(nearRadius-hubHalf)*unit.y;
delta.x=endPoint.x-start->x;delta.y=endPoint.y-start->y;
}
Real progress=0.f;
Real firstStep=module->getInitialStep();
progress+=firstStep;
current.x+=firstStep*unit.x;current.y+=firstStep*unit.y;
Int funds=builder->getControllingPlayer()->getMoney()->countMoney();
Int index=0;
Real remaining=delta.length();
Coord3D previous=current;
Bool connected=endAtObject&&Rva003919F6Connected(builder,nearObject);
Bool lastWouldBeLegal=false;
remaining-=hubHalf;
while(progress < remaining&&index < TheWritableGlobalData->m_wallCount-1){
const ThingTemplate*segment=module->getSegment(index);
if(!segment)segment=builder->m_template;
Real half=segment->getTemplateGeometryInfo().field28;half-=1.f;
if(progress+half*2.f > remaining){
segment=module->getEnd();
if(!segment)segment=builder->m_template;
half=segment->getTemplateGeometryInfo().field28;half-=1.f;
}
Coord3D step(unit.x*half,unit.y*half,0.f);
previous=current;
current.x+=step.x;current.y+=step.y;
current.z=TheTerrainLogic->getGroundHeight(current.x,current.y,0);
Int code=isLocationLegalToBuild(&current,segment,angle,0x55,builder,0);
Bool blocked=!points.empty();
for(_STL::vector<Coord3D>::iterator i=points.begin();i!=points.end();++i){
Coord3D diff;diff.x=current.x-i->x;diff.y=current.y-i->y;diff.z=current.z-i->z;
if(diff.length()<=range){blocked=false;break;}
}
if(blocked)code=9;
if(code==8&&progress+half+1.f < remaining)lastWouldBeLegal=true;
out->setPos(index,&current);
out->rva00392129(index,angle);
out->rva0039215F(index,segment->getName());
out->rva00392196(index,code);
if(code==6 || code==5){
const ThingTemplate*terrainPiece=module->getTerrainPiece();
if(terrainPiece)out->rva0039215F(index,terrainPiece->getName());
out->rva00392196(index,0);
current.z=previous.z;
out->setPos(index,&current);
out->rva003921C8(index,1);
const ThingTemplate*hub=module->getHub();
if(!hub)hub=builder->m_template;
if(index>=1){
out->rva0039215F(index-1,hub->getName());
out->cost+=terrainPiece->rva0033A69A(builder->getControllingPlayer(),(Int)builder,-1);
out->cost+=hub->rva0033A69A(builder->getControllingPlayer(),(Int)builder,-1);
out->cost-=segment->rva0033A69A(builder->getControllingPlayer(),(Int)builder,-1);
}
startNewHub=false;endAtObject=false;++index;break;
}
current.x+=step.x;current.y+=step.y;
out->cost+=segment->rva0033A69A(builder->getControllingPlayer(),(Int)builder,-1);
if(out->cost>funds){out->status=7;out->rva00392196(index,7);}
progress+=2.f*half;
++index;
if(index>=TheWritableGlobalData->m_wallCount)break;
}
if(endAtObject){
if(connected&&lastWouldBeLegal){
out->rva00392CAC();
return rva0039321C(out,builder,nearObject,key,false);
}
out->rva00392196(index-1,0);
}else if(startNewHub){
Coord3D step(unit.x*hubHalf,unit.y*hubHalf,0.f);
current.x+=step.x;current.y+=step.y;
current.z=TheTerrainLogic->getGroundHeight(current.x,current.y,0);
Int code=isLocationLegalToBuild(&current,hubTemplate,angle,0x55,builder,0);
out->setPos(index,&current);out->rva00392129(index,angle);out->rva0039215F(index,hubTemplate->getName());
Bool blocked=!points.empty();
for(_STL::vector<Coord3D>::iterator i=points.begin();i!=points.end();++i){
Coord3D diff;diff.x=current.x-i->x;diff.y=current.y-i->y;diff.z=current.z-i->z;
if(diff.length()<=range){blocked=false;break;}
}
if(blocked)code=9;
out->rva00392196(index,code);
out->status=(code>out->status?code:out->status);
out->cost+=hubTemplate->rva0033A69A(builder->getControllingPlayer(),(Int)builder,-1);
if(out->cost>funds){out->status=7;out->rva00392196(index,7);}
current.x+=step.x;current.y+=step.y;++index;
}
out->count=index;out->startNewHub=startNewHub;out->endAtObject=endAtObject;
if(out->count<2){out->count=0;return false;}
for(UnsignedInt i=0;i<out->count;++i)out->status=out->status>out->rva00392D71(i)?out->status:out->rva00392D71(i);
return true;
}
