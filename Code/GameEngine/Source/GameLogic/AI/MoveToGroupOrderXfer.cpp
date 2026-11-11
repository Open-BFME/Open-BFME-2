// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
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

#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// Inline-only STLport bodies preserve mod/ref visibility without emitting
// non-retail copies of the shared vector accessors. No import is called.
namespace _STL {
template<> __declspec(dllimport) inline void **vector<void*>::begin(){return this->_M_start;}
template<> __declspec(dllimport) inline void *const *vector<void*>::begin()const{return this->_M_start;}
template<> __declspec(dllimport) inline void **vector<void*>::end(){return this->_M_finish;}
template<> __declspec(dllimport) inline size_t vector<void*>::size()const{return this->_M_finish-this->_M_start;}
template<> __declspec(dllimport) inline void *&vector<void*>::operator[](size_t n){return *(begin()+n);}
template<> __declspec(dllimport) inline void *const &vector<void*>::operator[](size_t n)const{return *(begin()+n);}
}





// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}


typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int Int;

#include "../../Common/GameLogicObjectLookupView.h"

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
// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"
// Keep bucket construction and allocator behavior visible, as in FXListStoreParse.
namespace _STL {
template <> _STLP_alloc_proxy<void **,void *,allocator<void *> >::~_STLP_alloc_proxy();
template <> __declspec(dllimport) __forceinline void swap<void **>(void **&a, void **&b) { void **tmp=a; a=b; b=tmp; }
template <> inline void swap(_STLP_alloc_proxy<void **,void *,allocator<void *> > &a,_STLP_alloc_proxy<void **,void *,allocator<void *> > &b) { swap(a._M_data,b._M_data); }
template <> __declspec(dllimport) __forceinline _Vector_base<void *,allocator<void *> >::~_Vector_base() { if(_M_start) _M_end_of_storage.deallocate(_M_start,_M_end_of_storage._M_data-_M_start); }
template <> __forceinline vector<void *,allocator<void *> >::~vector() { _Destroy(this->_M_start,this->_M_finish); }
template <> allocator<void *> vector<void *,allocator<void *> >::get_allocator()const;
}

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

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"

extern Xfer &XferObjectID(Xfer *xfer, ObjectID *id);

#include "../../../Include/Common/XferException.h"

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
	bool rva002931BA();
	float GetRelativeAngle(const Coord3D*)const;
	void rva0028AD00(int,float,int);
	void rva0028ACEE(int,int);
	int m_31C; // +0x31C float bits
	int m_320; // +0x320 float bits
};
#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/Common/Rva00295A0FCommands.h"

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
enum PathfindLayerEnum {LAYER_GROUND=1};
#include "../../../Include/GameLogic/TerrainLogic.h"
class LocomotorSet;
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
extern GameLogic *TheGameLogic;

void Rva00547245Xfer(Xfer *xfer, ObjectCoord3DPair *pair)
{
	XferObjectID(xfer, &pair->first).operator==((Coord3DBase &)pair->second);
}

Xfer *Rva0054755BXfer(Xfer *xfer, ObjectCoord3DMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == (Xfer::Version &)version;

	UnsignedInt count = map->size();
	xfer->operator==("std::hash_map").operator==(count);

	if (xfer->IsStoring()) {
		for (ObjectCoord3DMap::iterator it = map->begin(); it != map->end(); ++it) {
			ObjectCoord3DPair item(*it);
			Rva00547245Xfer(xfer, &item);
		}
	} else {
		if (map->size() != 0) {
			throw XferException(4, "Map must be empty on load");
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

#include "../../../Include/GameLogic/GroupOrder.h"

class MoveToGroupOrder : public GroupOrder
{
public:
	virtual void xfer(Xfer *xfer);
	bool rva00547188(Object *obj, int dummy);
	void rva0054764C(Object *obj, AIUpdateInterface *aiUpdate, Coord3D *pos);
	Coord3D *rva005476C8(ObjectID);
	virtual void rva005478B5(ObjectID);

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
	*xfer == (Xfer::Version &)version;
	*xfer == (Coord3DBase &)m_destination;
	*xfer == m_flag24;
	Rva0054755BXfer(xfer, &m_positions);
	if (version.m_currentVersion >= 2)
		*xfer == m_flag25;
	else if (xfer->IsLoading())
		m_flag25 = false;
}

void MoveToFormationGroupOrder::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	GroupOrder::xfer(xfer);
	*xfer == (Xfer::Version &)version;
	*xfer == m_value18;
	*xfer == (Coord3DBase &)m_destination;
	*xfer == m_angle;
	*xfer == m_flag2C;
	Rva0054755BXfer(xfer, &m_positions);
	*xfer == m_flag44;
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

class Rva00547223;
Rva00547223 *Rva00547297Init(Rva00547223 *,int *,int *);

// Native5476C8..547805,317B. WB control flow keeps separate insertion
// returns; target proves the cached ObjectID/coordinate map at +28 and
// terrain/pathfinder adjustment. The original method name is unresolved.
// The shared four-word temporary is the existing pair factory's output
// storage; its key/three coordinate words are all written before use.
Coord3D *MoveToGroupOrder::rva005476C8(ObjectID id)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	Coord3D result;
	struct PairStorage { int key; float x, y, z; } pair;
	if (obj) {
		AIUpdateInterface *ai = (AIUpdateInterface *)obj->ai;
		if ((ai && reinterpret_cast<MoveAIUpdateView *>(ai)->slot137()) || obj->physics) {
			PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &m_destination);
			result.z = TheTerrainLogic->getLayerHeight(m_destination.x, m_destination.y, layer, 0, true);
			result.x = m_destination.x;
			result.y = m_destination.y;
			if (!TheAI->pathfinder()->AdjustDestination(obj,
				*reinterpret_cast<LocomotorSet *>(reinterpret_cast<char *>(ai) + 0x1CC),
				&result, &m_destination))
				result = m_destination;
			if (obj->theTemplate->m_kindof[5] & 0x04000000) {
				float angle = obj->angle;
				float rel = obj->GetRelativeAngle(&result) + angle;
				obj->rva0028AD00((int)&result, rel, layer);
			} else {
				obj->rva0028ACEE((int)&result, layer);
			}
			return &m_positions.insert(*(ObjectCoord3DPair *)Rva00547297Init(
				(Rva00547223 *)&pair, (int *)&id, (int *)&result)).first->second;
		}
	}
	return &m_positions.insert(*(ObjectCoord3DPair *)Rva00547297Init(
		(Rva00547223 *)&pair, (int *)&id, (int *)&m_destination)).first->second;
}

class Rva00352F9D
{
public:
	void rva0035300B(const void *object, const Coord3D &position, CommandSourceType source);
};

namespace _STL {
typedef pair<const ObjectID, Coord3D> MoveToPositionPair;
template __declspec(noinline) _Hashtable_node<MoveToPositionPair> *
    hashtable<MoveToPositionPair, ObjectID, rts::hash<ObjectID>,
              _Select1st<MoveToPositionPair>, equal_to<ObjectID>,
              allocator<MoveToPositionPair> >::_M_find<ObjectID>(const ObjectID &) const;
}

// Native5478B5..547944,143B; vftable C6A478 slot4, following xfer slot3.
// The target probes the +28 ObjectID/coordinate map, copies its result, then
// dispatches through Object AI+258 and physics+274. Keep the two coordinate
// copies in their branches: merging the source pointer changes register saves.
void MoveToGroupOrder::rva005478B5(ObjectID id)
{
	Coord3D local;
	ObjectCoord3DMap *map = &m_positions;
	ObjectCoord3DMap::const_iterator it = map->find(id);
	if (it == map->end())
		local = *rva005476C8(id);
	else
		local = it->second;
	Object *object = TheGameLogic->findObjectByID(id);
	if (object && !object->rva002931BA()) {
		AIUpdateInterface *ai = object->ai;
		if (ai) {
			if (object->physics)
				((Rva00352F9D *)&ai->m_commands)->rva0035300B(object->physics, local, CMD_FROM_PLAYER);
			else
				rva0054764C(object, ai, &local);
		}
	}
}
