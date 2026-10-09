// ?rva005476C8@MoveToGroupOrder@@QAEPAUCoord3D@@W4ObjectID@@@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfmealloc /Ireference/shims/stlp_nodealloc /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// Xfer of the two MoveTo group orders (vftable slot 3 of 0x00C6A478 /
// 0x00C6A4CC) and of their hash_map<ObjectID, Coord3D> member (see
// MoveToGroupOrderCtor.cpp for the layouts).
//
// ?xfer@MoveToGroupOrder@@UAEXPAVXfer@@@Z @0x00547805 (112B): GroupOrder xfer
//   0x00548AC2, version {1,2}, the +0x18 Coord3D (Xfer slot 0x60), bool +0x24
//   (slot 0x90), the map, then bool +0x25 from version 2 on (cleared when an
//   older save loads).
// ?xfer@MoveToFormationGroupOrder@@UAEXPAVXfer@@@Z @0x00547DE9 (115B):
//   version {1,1}, int +0x18 (slot 0x7C), Coord3D +0x1C, float +0x28 (slot
//   0x70), bool +0x2C, the map at +0x30, bool +0x44.
// 0x0054755B (241B): the map xfer, the hash_map twin of the rowed
//   map<int,int> xfer Rva00470222Xfer: version {1,1}, type name
//   "std::hash_map" (0x00C14DF4), count, then per-pair xfer on save; on load
//   it throws "Map must be empty on load" for a non-empty map, else reads
//   count pairs and stores each value through operator[] (0x005474E7).
// 0x00547245 (30B): the pair xfer, XferObjectID 0x003060B2 on the key, then
//   the Coord3D slot on the value through the Xfer XferObjectID returns
//   (retail reuses its eax rather than reloading the xfer).
// Callees that are ICF-folded STLport bodies resolve through pins: begin
// 0x00427195, iterator ++ 0x0041E832, the converting pair copy 0x0004254E and
// the default pair ctor 0x00326BE6.

#include <hash_map>
#include <cstddef>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int Int;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_LONG = 0x7fffffff
};

namespace rts
{

// ZH's identity hash (STLTypedefs.h): retail's _M_insert 0x00547430 hashes
// the key inline as its own value.
template <typename T> struct hash
{
	size_t operator()(const T &value) const
	{
		return (size_t)value;
	}
};

}

// The WWMath Coord3D shape (Libraries/Source/WWVegas/WWMath/coord3d.cpp):
// empty default ctor and dtor plus a memberwise copy ctor.
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~Coord3D() {}

	float x;
	float y;
	float z;
};

typedef std::hash_map<
	ObjectID,
	Coord3D,
	rts::hash<ObjectID>,
	std::equal_to<ObjectID> > ObjectCoord3DMap;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
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
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void xferReal(Real *value);
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void xferBool(Bool *value);
};

extern Xfer &XferObjectID(Xfer *xfer, ObjectID *id);

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")

typedef _STL::pair<ObjectID, Coord3D> ObjectCoord3DPair;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class ThingTemplate;
class AIUpdateInterface;
class Object
{
public:
	char pad0[4]; ThingTemplate *theTemplate;
 char pad08[0x38-8]; Coord3D position;float angle;
 char pad48[0x258-0x48];AIUpdateInterface *ai;
 char pad25C[0x274-0x25C];void *physics;
 char pad278[0x31C-0x278];
 float GetRelativeAngle(const Coord3D*)const;
 void rva0028AD00(int,float,int);
 void rva0028ACEE(const Coord3D*,int);
	int m_31C; // +0x31C float bits
	int m_320; // +0x320 float bits
};

class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *pos, int maxShots, int source);
};

class AICommandInterface
{
public:
	void aiMoveToPositionAmphibious(const Coord3D *position, CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad0[0x20];
	AICommandInterface m_commands; // +0x20
};

void Rva00547245Xfer(Xfer *xfer, ObjectCoord3DPair *pair)
{
	XferObjectID(xfer, &pair->first).xferCoord3D(&pair->second);
}

Xfer *Rva0054755BXfer(Xfer *xfer, ObjectCoord3DMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = map->size();
	xfer->xferTypeName("std::hash_map").xferUnsignedInt(&count);

	if (xfer->isSaving()) {
		for (ObjectCoord3DMap::iterator it = map->begin(); it != map->end(); ++it) {
			ObjectCoord3DPair item(*it);
			Rva00547245Xfer(xfer, &item);
		}
	} else {
		if (map->size() != 0) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		ObjectCoord3DPair item;
		while (count != 0) {
			--count;
			Rva00547245Xfer(xfer, &item);
			(*map)[item.first] = item.second;
		}
	}
	return xfer;
}

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x18 - 4];
};

class MoveToGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);
	bool rva00547188(Object *obj, int dummy);
	void rva0054764C(Object *obj, AIUpdateInterface *aiUpdate, Coord3D *pos);
 Coord3D *rva005476C8(ObjectID);

private:
	Coord3D m_destination;             // +0x18
	Bool m_flag24;                     // +0x24
	Bool m_flag25;                     // +0x25
	ObjectCoord3DMap m_positions;      // +0x28
	Int m_value3C;                     // +0x3C
};

class MoveToFormationGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);

private:
	Int m_value18;                     // +0x18
	Coord3D m_destination;             // +0x1C
	Real m_angle;                      // +0x28
	Bool m_flag2C;                     // +0x2C
	ObjectCoord3DMap m_positions;      // +0x30
	Bool m_flag44;                     // +0x44
};

void MoveToGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;
	GroupOrder::xfer(xfer);
	xfer->xferVersion(&version);
	xfer->xferCoord3D(&m_destination);
	xfer->xferBool(&m_flag24);
	Rva0054755BXfer(xfer, &m_positions);
	if (version.m_currentVersion >= 2)
		xfer->xferBool(&m_flag25);
	else if (xfer->isLoading())
		m_flag25 = false;
}

void MoveToFormationGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	xfer->xferVersion(&version);
	xfer->xferInt(&m_value18);
	xfer->xferCoord3D(&m_destination);
	xfer->xferReal(&m_angle);
	xfer->xferBool(&m_flag2C);
	Rva0054755BXfer(xfer, &m_positions);
	xfer->xferBool(&m_flag44);
}

// ?rva0054764C@MoveToGroupOrder@@QAEXPAVObject@@PAVAIUpdateInterface@@PAUCoord3D@@@Z, retail 0x0054764C 124B.
// Chain from 0x00547188: if destination check passes copy x/y to obj+0x31C and
// issue aiMoveToPositionAmphibious else branch on m_flag24 to Rva00295A0FCommand or aiMoveToPosition.
// Evidence: this+0x18/+0x24 MoveTo layout plus caller 0x005478B5 (slot 4) passing
// Object+AIUpdate+Coord3D plus rowed callees.
void MoveToGroupOrder::rva0054764C(Object *obj, AIUpdateInterface *aiUpdate, Coord3D *pos)
{
	if (rva00547188(obj, (int)pos)) {
		float xy[2];
		xy[0] = m_destination.x;
		xy[1] = m_destination.y;
		obj->m_31C = *(int *)&xy[0];
		obj->m_320 = *(int *)&xy[1];
		aiUpdate->m_commands.aiMoveToPositionAmphibious(&m_destination, CMD_FROM_PLAYER);
	} else {
		if (m_flag24)
			((Rva00295A0FCommands *)&aiUpdate->m_commands)->Rva00295A0FCommand(pos, 0x7FFFFFFF, 0);
		else
			aiUpdate->m_commands.aiMoveToPosition(pos, (CommandSourceType)0);
	}
}

class ThingTemplate { public: char pad[0x11C]; unsigned kindHigh; };
enum PathfindLayerEnum {LAYER_GROUND=1};
class TerrainLogic {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();

 virtual float slot7(float,float,PathfindLayerEnum,Coord3D*,bool);
 PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
class LocomotorSet;
class Pathfinder {public: bool adjustDestination(Object*,const LocomotorSet&,Coord3D*,const Coord3D*);};
struct AIView {char pad[16];Pathfinder *pathfinder;};extern AIView *TheAI;
class GameLogic {public:Object *findObjectByID(ObjectID);};extern GameLogic *TheGameLogic;
class MoveAIUpdateView {public:
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

 virtual bool slot137();
};
class Rva00547223 {public: unsigned words[4];};
Rva00547223 *Rva00547297Init(Rva00547223*,int*,int*);
Coord3D *MoveToGroupOrder::rva005476C8(ObjectID id)
{
 Object *obj=TheGameLogic->findObjectByID(id);
 Coord3D result;
 const Coord3D *position;
 if(obj) {
  AIUpdateInterface *ai=obj->ai;
  if((ai && reinterpret_cast<MoveAIUpdateView*>(ai)->slot137()) || obj->physics) {
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(obj,&m_destination);
   result.z=TheTerrainLogic->slot7(m_destination.x,m_destination.y,layer,0,true);
   result.x=m_destination.x;result.y=m_destination.y;
   if(!TheAI->pathfinder->adjustDestination(obj,*reinterpret_cast<LocomotorSet*>(reinterpret_cast<char*>(ai)+0x1CC),&result,&m_destination))result=m_destination;
   if(obj->theTemplate->kindHigh & 0x04000000) {float angle=obj->angle; obj->rva0028AD00((int)&result,obj->GetRelativeAngle(&result)+angle,layer);}
   else obj->rva0028ACEE(&result,layer);
   position=&result;
   goto insert;
  }
 }
 position=&m_destination;
insert:
 return &m_positions.insert(_STL::make_pair(id,*position)).first->second;
}
