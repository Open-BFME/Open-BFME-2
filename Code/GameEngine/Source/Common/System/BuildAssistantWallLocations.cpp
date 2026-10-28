// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHs /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
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
#include <list>
class Drawable;
class FreelistPool{public: void*pop();};
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
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
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
extern float g_00E027C4;
#define TOTAL_FRAMES_TO_SELL_OBJECT g_00E027C4
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
enum GeometryType
{
GEOMETRY_SPHERE=0,
GEOMETRY_CYLINDER,
GEOMETRY_BOX
};
class BfmeThingTemplateShadowSelector
{
public:
Bool usePluralShadowName()const;
};
class GeometryInfo
{
public:
GeometryInfo(GeometryType type,Bool isSmall,Real height,Real majorRadius,Real minorRadius);
GeometryInfo(const GeometryInfo&that);
virtual ~GeometryInfo();
Real getMajorRadius()const{return m_majorRadius;}
__declspec(dllimport)__forceinline Real getBoundingCircleRadius()const{return m_boundingCircleRadius;}
Real getBoxMajorRadius()const{return m_boxMajorRadius;}
Real getBoxMinorRadius()const{return m_boxMinorRadius;}
__forceinline Bool isSingleBox()const{return((const BfmeThingTemplateShadowSelector*)this)->usePluralShadowName();}
Real getMaxHeightAbovePosition()const;
void expandFootprint(Real radius);
bool CollidesWith(const Coord3D&pos,Real angle,const GeometryInfo&other,const Coord3D&otherPos,Real otherAngle)const;
private:
unsigned char m_pad04[0x10 - 0x04];
Real m_majorRadius;
Real m_boundingCircleRadius;
unsigned char m_pad18[0x24 - 0x18];
Real m_boxMajorRadius;
Real m_boxMinorRadius;
unsigned char m_pad2C[0x5C - 0x2C];
};
class ModuleData;
class Rva0033B427Data
{
public:
unsigned char m_pad00[0x30];
Real m_range;
};
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
class UpgradeTemplate
{
public:
UpgradeType getUpgradeType()const{return m_type;}
private:
unsigned char m_pad00[4];
UpgradeType m_type;
};
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
class Rva0031D5F8
{
public:
void*rva0031D5F8(const AsciiString*key);
};
class ControlBar : public Rva0031D5F8
{
public:
const CommandSet*findCommandSet(const AsciiString*name)
{
return(const CommandSet*)rva0031D5F8(name);
}
};
extern ControlBar*TheControlBar;
class Rva00392B10Interface
{
public:
virtual AsciiString slot00()const=0;
};
class BehaviorModuleInterface
{
public:
virtual void slot00()=0;virtual void slot01()=0;virtual void slot02()=0;
virtual void slot03()=0;virtual void slot04()=0;virtual void slot05()=0;
virtual void slot06()=0;virtual void slot07()=0;virtual void slot08()=0;
virtual void slot09()=0;virtual void slot10()=0;
virtual Rva00392B10Interface*slot11()=0;
};
class BfmeObjectModule
{
public:
virtual void slot0()=0;
private:
unsigned int m_data[2];
};
class BehaviorModule : public BfmeObjectModule,public BehaviorModuleInterface
{
};
class ProductionUpdateInterface
{
public:
virtual CanMakeType rva0049CFCD()const;
virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();
virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate*type)const;
virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
virtual void slot12();virtual void slot13();virtual void slot14();
virtual void cancelAndRefundAllProduction();
};
class ContainModuleInterface
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();
virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();
virtual void slot24();
virtual void onSelling();
};
class Rva00346BC0
{
public:
UnsignedInt m_bits[4];
};
struct Rva00391F4E : public Rva00346BC0
{
Rva00391F4E(Int unused,Int bit1,Int bit2);
};
class Rva00391994
{
public:
Bool rva00391994();
};
class ProductionUpdate
{
public:
static ProductionUpdateInterface*getProductionUpdateInterfaceFromObject(Object*obj);
};
class Rva0028BD17Interface
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();
virtual void slot03();virtual void slot04();virtual void slot05();
virtual Bool slot06();
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
virtual Bool slot23(ObjectID);
};
class AICommandInterface
{
public:
void aiIdle(CommandSourceType cmdSource);
void aiMoveToPositionEvenIfSleeping(const Coord3D*pos,CommandSourceType cmdSource);
};
class DozerAIInterface
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();
virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();
virtual void slot24();virtual void slot25();virtual void slot26();virtual void slot27();
virtual void slot28();virtual void slot29();
virtual UnsignedInt slot30();
};
struct Rva00391D25PathNode{unsigned char pad0[0x0C];Coord3D pos;};
struct Rva00391D25Path{unsigned char pad0[8];Rva00391D25PathNode*node;};
class AIUpdateInterface
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();virtual void slot09();virtual void slot10();virtual void slot11();
virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();
virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();
virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();
virtual void slot24();virtual void slot25();virtual void slot26();virtual void slot27();
virtual void slot28();virtual void slot29();virtual void slot30();virtual void slot31();
virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();
virtual void slot36();virtual void slot37();virtual void slot38();virtual void slot39();
virtual void slot40();virtual void slot41();virtual void slot42();virtual void slot43();
virtual void slot44();virtual void slot45();virtual void slot46();virtual void slot47();
virtual void slot48();virtual void slot49();virtual void slot50();virtual void slot51();
virtual void slot52();virtual void slot53();virtual void slot54();virtual void slot55();
virtual void slot56();virtual void slot57();virtual void slot58();virtual void slot59();
virtual void slot60();virtual void slot61();virtual void slot62();virtual void slot63();
virtual void slot64();virtual void slot65();virtual void slot66();virtual void slot67();
virtual void slot68();virtual void slot69();virtual void slot70();virtual void slot71();
virtual void slot72();virtual void slot73();virtual void slot74();virtual void slot75();
virtual void slot76();virtual void slot77();virtual void slot78();virtual void slot79();
virtual void slot80();virtual void slot81();virtual void slot82();virtual void slot83();
virtual void slot84();virtual void slot85();virtual void slot86();virtual void slot87();
virtual void slot88();virtual void slot89();virtual void slot90();virtual void slot91();
virtual void slot92();
virtual DozerAIInterface*getDozerAIInterface();
virtual void slot94();virtual void slot95();virtual void slot96();virtual void slot97();
virtual void slot98();virtual void slot99();virtual void slot100();virtual void slot101();
virtual void slot102();virtual void slot103();virtual void slot104();virtual void slot105();
virtual void slot106();virtual void slot107();virtual void slot108();virtual void slot109();
virtual void slot110();virtual void slot111();virtual void slot112();virtual void slot113();
virtual void slot114();virtual void slot115();virtual void slot116();virtual void slot117();
virtual void slot118();virtual void slot119();virtual void slot120();virtual void slot121();
virtual void slot122();virtual void slot123();virtual void slot124();virtual void slot125();
virtual Object*construct(const ThingTemplate*what,const Coord3D*pos,Real angle,Player*owningPlayer,Bool isRebuild,Int flags);
void destroyPath();
Rva00391D25Path*getPath()const{return m_path;}
Bool isPathAvailable(const Coord3D*destination)const;
Bool isQuickPathAvailable(const Coord3D*destination)const;
__forceinline void aiIdle(CommandSourceType cmdSource){m_command.aiIdle(cmdSource);}
__forceinline void aiMoveToPositionEvenIfSleeping(const Coord3D*pos,CommandSourceType cmdSource){m_command.aiMoveToPositionEvenIfSleeping(pos,cmdSource);}
Bool isMoving()const;
private:
unsigned char m_pad04[0x20 - 0x04];
AICommandInterface m_command;
unsigned char m_pad021[0x140 - 0x21];
Rva00391D25Path*m_path;
};
class FoundationAIInterface
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();
virtual Bool slot03();
virtual void slot04();virtual void slot05();virtual void slot06();
virtual Object*construct(const ThingTemplate*what,const Coord3D*pos,Real angle,Player*owningPlayer,Bool isRebuild,Int flags);
};
class G00DFF080Obj
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();virtual void slot09();
virtual void addFactionBib(Object*factionBuilding,Bool highlight,Real extra=0);
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
class BodyModuleInterface
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();
virtual Real slot05()const;
virtual void slot06();virtual void slot07();
virtual BodyDamageType getDamageState()const;
};
class Rva00294D61
{
public:
void report(Object*owner,int setting);
};
class Thing
{
public:
virtual ~Thing();
const ThingTemplate*getTemplate()const{return m_template;}
Drawable*getDrawable()const;
void setPosition(const Coord3D*pos);
void setOrientation(Real angle);
protected:
const ThingTemplate*m_template;
};
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
const Coord3D*getPosition()const{return&m_position;}
Real getOrientation()const{return m_orientation;}
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
unsigned char m_pad008[0x38 - 8];
Coord3D m_position;
Real m_orientation;
unsigned char m_pad048[0x74 - 0x48];
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
class Rva002A7461
{
public:
bool rva002A7557(Rva002A7557In*p,int unused);
};
class Rva0037E6E8
{
public:
Int rva0037E649(Int index,Object*obj);
};
class Rva0037E421
{
public:
void*rva0037E7A5(int index);
unsigned char rva0037E7BC(int index);
};
class Rva0039B7AD;
class Rva003B0D7C
{
public:
void rva003B0D7C(int amount,Rva0039B7AD*score,bool flag);
};
class Money : public Rva003B0D7C
{
public:
UnsignedInt countMoney()const{return m_money;}
private:
unsigned char m_pad0[4];
UnsignedInt m_money;
};
class ScoreKeeper
{
public:
void addObjectLost(const Object*o);
private:
unsigned char m_pad00[4];
};
class Player
{
public:
__declspec(dllimport)__forceinline Money*getMoney(){return&m_money;}
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
Money m_money;
unsigned char m_pad098[0x280 - 0x98];
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
class BuildAssistant
{
public:
virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();
virtual void slot04();virtual void slot05();virtual void slot06();virtual void slot07();
virtual void slot08();
virtual void reset(void);
virtual void update(void);
virtual void slot11();
virtual void slot12();virtual void slot13();
virtual Object*buildObjectNow(Object*constructorObject,const ThingTemplate*what,const Coord3D*pos,Real angle,Player*owningPlayer);
virtual void slot15();
virtual LegalBuildCode isLocationLegalToBuild(const Coord3D*worldPos,const ThingTemplate*build,Real angle,UnsignedInt options,Object*builderObject,Player*player);
virtual Bool isLocationClearOfObjects(const Coord3D*worldPos,const ThingTemplate*build,Real angle,Object*builderObject,UnsignedInt options,Player*player,Bool flag);
virtual Bool rva0039361E(const Coord3D*pos,const ThingTemplate*whatToBuild,Real angle,Object*builder,Player*unused);
virtual void addBibs(const Coord3D*worldPos,const ThingTemplate*build);
virtual Bool rva0039380F(Rva0039205C*out,Object*builder,const Coord3D*start,const Coord3D*end,UnsignedInt key);
virtual Bool slot21(Rva0039205C*out,Object*builder,Object*end,UnsignedInt key,Bool flag);
virtual void slot22();
virtual Bool rva00391A70(const ThingTemplate*whatToBuild,const Object*builder);
virtual CanMakeType canMakeUnit(Object*builder,const ThingTemplate*whatToBuild,Int revivalIndex)const;
virtual Bool isPossibleToMakeUnit(Object*builder,const ThingTemplate*whatToBuild,Int revivalIndex)const;
virtual void sellObject(Object*obj);
void iterateFootprint(const ThingTemplate*build,Real buildOrientation,const Coord3D*worldPos,Real sampleResolution,void(*func)(const Coord3D*samplePoint,void*userData),void*userData);
Bool isRemovableForConstruction(Object*obj);
Bool rva00391AA1(const ThingTemplate*builder,const ThingTemplate*what);
void clearRemovableForConstruction(const ThingTemplate*whatToBuild,const Coord3D*pos,Real angle);
Bool moveObjectsForConstruction(const ThingTemplate*whatToBuild,const Coord3D*pos,Real angle,Player*owningPlayer);
private:
unsigned char m_pad04[0x0C - 0x04];
ObjectSellList m_sellList;
};
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
class GameTextInterface
{
public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();
virtual void v4();virtual void v5();virtual void v6();virtual void v7();
virtual void v8();virtual void v9();virtual void v10();virtual void v11();
virtual void v12();virtual void v13();virtual void v14();virtual void v15();
virtual void v16();
virtual const UnicodeString*fetch(const char*label,Bool*exists);
};
extern GameTextInterface*TheGameText;
class InGameUI
{
public:
#define IGUI_SLOTS10(n) virtual void s##n##0(); virtual void s##n##1(); virtual void s##n##2(); \
virtual void s##n##3();virtual void s##n##4();virtual void s##n##5();virtual void s##n##6();\
virtual void s##n##7();virtual void s##n##8();virtual void s##n##9();
IGUI_SLOTS10(0)IGUI_SLOTS10(1)IGUI_SLOTS10(2)IGUI_SLOTS10(3)IGUI_SLOTS10(4)
IGUI_SLOTS10(5)IGUI_SLOTS10(6)IGUI_SLOTS10(7)IGUI_SLOTS10(8)IGUI_SLOTS10(9)
#undef IGUI_SLOTS10
virtual void s100();virtual void s101();virtual void s102();virtual void s103();
virtual void addFloatingText(const UnicodeString&text,const Coord3D*pos,Color color);
};
extern InGameUI*TheInGameUI;
class TerrainLogic
{
public:
virtual void t00();virtual void t01();virtual void t02();virtual void t03();
virtual void t04();virtual void t05();
virtual Real getGroundHeight(Real x,Real y,Coord3D*normal=0)const;
virtual void t07();
virtual void getExtent(Region3D*extent)const;
virtual void t09();virtual void t10();virtual void t11();
virtual void getMaximumPathfindExtent(Region3D*extent)const;
virtual void t13();virtual void t14();virtual void t15();
virtual void t16();virtual void t17();virtual void t18();
virtual Bool isUnderwater(Real x,Real y,Real*waterZ=NULL,Real*terrainZ=NULL,Int unused=0);
PathfindLayerEnum getLayerForDestination(Object*obj,const Coord3D*pos);
PathfindLayerEnum getHighestLayerForDestination(const Coord3D*pos,Bool onlyHealthyBridges);
};
extern TerrainLogic*TheTerrainLogic;
class Pathfinder
{
public:
void AddObjectToPathfindMap(Object*object);
void GetCellType(int pos,void*isValid,void*isBlocked,void*cellType,int layer);
void*getObstacleID(int layer,int pos);
};
class AI
{
public:
Pathfinder*pathfinder(){return m_pathfinder;}
private:
unsigned char m_pad00[0x10];
Pathfinder*m_pathfinder;
};
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
class Rva000421C8
{
public:
Rva000421C8(): m_next(0){}
virtual ~Rva000421C8(){}
virtual Bool allow(Object*obj)=0;
virtual int getPlayerMask();
Rva000421C8*link(Rva000421C8*filter);
Rva000421C8*m_next;
};
class BfmeFixedStorage0004543D
{
public:
BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&other)throw();
private:
unsigned char m_bytes[28];
};
struct Rva00045411BitSet
{
Rva00045411BitSet(int unused,int bit)throw();
unsigned int m_bits[7];
};
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva0004584D : public Rva000421C8
{
public:
Rva0004584D(const BfmeFixedStorage0004543D&a,const BfmeFixedStorage0004543D&b)throw();
virtual Bool allow(Object*obj);
BfmeFixedStorage0004543D m_08;
BfmeFixedStorage0004543D m_24;
};
class Rva00261603Filter : public Rva000421C8
{
public:
Rva00261603Filter(const Coord3D&pos,const GeometryInfo&geom,Real angle,Bool desired)throw();
virtual Bool allow(Object*objOther);
private:
Coord3D m_position;
const GeometryInfo&m_geom;
Real m_angle;
Bool m_desiredCollisionResult;
};
class Rva0029439DModule
{
public:
virtual void slot000();
virtual void slot001();
virtual void slot002();
virtual void slot003();
virtual void slot004();
virtual void slot005();
virtual void slot006();
virtual void slot007();
virtual void slot008();
virtual void slot009();
virtual void slot010();
virtual void slot011();
virtual void slot012();
virtual void slot013();
virtual void slot014();
virtual void slot015();
virtual void slot016();
virtual void slot017();
virtual void slot018();
virtual void slot019();
virtual void slot020();
virtual void slot021();
virtual void slot022();
virtual void slot023();
virtual void slot024();
virtual void slot025();
virtual void slot026();
virtual void slot027();
virtual void slot028();
virtual void slot029();
virtual void slot030();
virtual void slot031();
virtual void slot032();
virtual void slot033();
virtual void slot034();
virtual void slot035();
virtual void slot036();
virtual void slot037();
virtual void slot038();
virtual void slot039();
virtual void slot040();
virtual void slot041();
virtual void slot042();
virtual void slot043();
virtual void slot044();
virtual void slot045();
virtual void slot046();
virtual void slot047();
virtual void slot048();
virtual void slot049();
virtual void slot050();
virtual void slot051();
virtual void slot052();
virtual void slot053();
virtual void slot054();
virtual void slot055();
virtual void slot056();
virtual void slot057();
virtual void slot058();
virtual void slot059();
virtual void slot060();
virtual void slot061();
virtual void slot062();
virtual void slot063();
virtual void slot064();
virtual void slot065();
virtual void slot066();
virtual void slot067();
virtual void slot068();
virtual void slot069();
virtual void slot070();
virtual void slot071();
virtual void slot072();
virtual void slot073();
virtual void slot074();
virtual void slot075();
virtual void slot076();
virtual void slot077();
virtual void slot078();
virtual void slot079();
virtual void slot080();
virtual void slot081();
virtual void slot082();
virtual void slot083();
virtual void slot084();
virtual void slot085();
virtual void slot086();
virtual void slot087();
virtual void slot088();
virtual void slot089();
virtual void slot090();
virtual void slot091();
virtual void slot092();
virtual void slot093();
virtual void slot094();
virtual void slot095();
virtual void slot096();
virtual void slot097();
virtual void slot098();
virtual void slot099();
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
virtual Bool slot114();
};
class Rva0026119DFilter : public Rva000421C8
{
public:
virtual Bool allow(Object*obj);
};
class Rva0026118BFilter : public Rva000421C8
{
public:
virtual Bool allow(Object*obj);
};
struct Rva0006EE7A
{
Rva0006EE7A(int unused,int b1,int b2,int b3,int b4)throw();
unsigned int m_bits[7];
};
class Rva00391D25Filter : public Rva000421C8
{
public:
Rva00391D25Filter(const Coord3D*pos,Real radius): m_pos(pos),m_radius(radius){}
virtual Bool allow(Object*obj);
private:
const Coord3D*m_pos;
Real m_radius;
};
struct BfmeResultA
{
void*m_value;
~BfmeResultA();
};
class BfmeResultForwardB
{
public:
BfmeResultA bfmeForwardResultB(int value);
};
struct BfmeCopyElementA
{
BfmeCopyElementA*bfmeAssign(BfmeCopyElementA*source);
};
Real GetGameLogicRandomValueReal(Real low,Real high,char*file,Int line);
#define BUILDASSISTANT_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\System\\BuildAssistant.cpp"
#define PI 3.14159265359f
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
class DrawableList : public _STL::list<Drawable*>
{
public:
~DrawableList()throw();
};
class PickAndPlayInfo;
class GameMessage
{
public:
enum Type
{
MSG_BFME2_0x7DA=0x7DA
};
};
bool pickAndPlayUnitVoiceResponse(const DrawableList*list,GameMessage::Type messageType,
PickAndPlayInfo*info);
class Rva0028CBFD
{
public:
void rva0028CBFD();
};
struct ProductionCountData
{
UnsignedInt count;
const ThingTemplate*type;
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
struct SampleBuildData
{
const ThingTemplate*build;
Bool requireWaterOrLand;
Region3D mapRegion;
Bool terrainRestricted;
Real hiZ;
Real loZ;
Real waterSamples;
Real landSamples;
Coord3D waterSum;
Coord3D landSum;
Int playerIndex;
};
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
if(obj==NULL || obj->getTemplate()->isKindOf(KINDOF_INERT))
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
class Rva00293330{public: void*rva00293330(UnsignedInt key);};
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
struct Rva003920F7Src{int a,b,c;};
class Rva003920F7{public: void rva003920F7(UnsignedInt index,const Rva003920F7Src*pos);};
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
if(!builder->getTemplate()->isKindOfByte(KINDOF_156))return false;
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
Real hubHalf=hubTemplate->getTemplateGeometryInfo().getBoxMinorRadius();
if(nearObject){
nearRadius=nearObject->getGeometryInfo().getMajorRadius();
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
if(!segment)segment=builder->getTemplate();
Real half=segment->getTemplateGeometryInfo().getBoxMinorRadius();half-=1.f;
if(progress+half*2.f > remaining){
segment=module->getEnd();
if(!segment)segment=builder->getTemplate();
half=segment->getTemplateGeometryInfo().getBoxMinorRadius();half-=1.f;
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
if(!hub)hub=builder->getTemplate();
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
return slot21(out,builder,nearObject,key,false);
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
