// ?rva005478B5@MoveToGroupOrder@@UAEXW4ObjectID@@@Z
// partial score=0.9 date=2026-10-09
// cl: /Ob2 /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include/Lib /I.
//
// Small virtual slots of the two MoveTo group orders (vftables 0x00C6A478 /
// 0x00C6A4CC; layouts in MoveToGroupOrderCtor.cpp). No Zero Hour or BFME 1
// counterpart; slot names follow the AttackObjectGroupOrder precedent
// (getDestination, isNearDestination and clone are named from what the bodies
// return; slot07Set and slot11Command keep slot-derived names).
//
//   slot  MoveTo      Formation   body
//   7     0x005471DF  0x00547B10  sets the +0x24 / +0x2C flag
//   8     0x0054719D  0x00547AAE  returns the destination Coord3D
//   9     0x005471A3  0x00547AD4  2D squared distance of a point to the
//                                 destination below 200.0f (0x00BCE190)
//   11    0x005471E6  0x00547AB4  fills a command: type id (0x430, else 0x442
//                                 / 0x42F by +0x25; Formation 0x464) and the
//                                 destination at +0x14; returns true
//   13    0x00547A77  0x005480B1  new copy (0x40 / 0x48 bytes) through the
//                                 copy ctor 0x00547A18 / 0x0054804C

#include "Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include <hash_map>
// stlport
namespace rts {
template <typename T> struct hash {
    size_t operator()(const T &value) const { return (size_t)value; }
};
}
typedef _STL::hash_map<ObjectID, Coord3D, rts::hash<ObjectID>,
                      _STL::equal_to<ObjectID> > ObjectCoord3DMap;
extern GameLogic *TheGameLogic;

// The three native calls target the rowed predicate in Rva0028ECDB.cpp
// at 0x0028ECDB, passing the complete Object as this and the unchanged
// destination pointer. Its byte-verified view reads the template at +4
// and the containment word at +0x250. Keep that provider ABI; the body
// name and the position test remain unnamed.
class Rva0028ECDBHost
{
public:
	bool rva0028ECDB(void *position);
};

class Object;class AIUpdateInterface;

struct GroupOrderCommand
{
	unsigned char m_pad00[0x14];
	Coord3D m_position; // +0x14
};

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void rva00547F37(ObjectID id);
	virtual void slot05();
	virtual void slot06();
	virtual void slot07Set(int unused) = 0;
	virtual Coord3D *getDestination(int unused) = 0;
	virtual bool isNearDestination(const Coord3D *pos) = 0;
	virtual void slot10();
	virtual bool slot11Command(int *outType, GroupOrderCommand *command) = 0;
	virtual void slot12();
	virtual GroupOrder *clone() = 0;

private:
	unsigned char m_pad04[0x18 - 4];
};

class MoveToGroupOrder : public GroupOrder
{
public:
	MoveToGroupOrder(const MoveToGroupOrder &other);

	virtual void slot07Set(int unused);
	virtual Coord3D *getDestination(int unused);
	virtual bool isNearDestination(const Coord3D *pos);
	virtual bool slot11Command(int *outType, GroupOrderCommand *command);
	virtual GroupOrder *clone();
	bool rva00547188(Object *obj, int dummy);
 void rva0054764C(Object*,AIUpdateInterface*,Coord3D*);
 Coord3D *rva005476C8(ObjectID);
 virtual void rva005478B5(ObjectID);

private:
	Coord3D m_destination;             // +0x18
	bool m_flag24;                     // +0x24
	bool m_flag25;                     // +0x25
	unsigned int m_map28[5];            // +0x28 hash_map<ObjectID, Coord3D>
	int m_value3C;                     // +0x3C
};

class MoveToFormationGroupOrder : public GroupOrder
{
public:
	MoveToFormationGroupOrder(const MoveToFormationGroupOrder &other);

	virtual void rva00547F37(ObjectID id);
	void rva00547CB6();
	void rva00547E5C(Object *object, const Coord3D *position);
	virtual void slot07Set(int unused);
	virtual Coord3D *getDestination(int unused);
	virtual bool isNearDestination(const Coord3D *pos);
	virtual bool slot11Command(int *outType, GroupOrderCommand *command);
	virtual GroupOrder *clone();

private:
	int m_value18;                     // +0x18
	Coord3D m_destination;             // +0x1C
	float m_angle;                     // +0x28
	bool m_flag2C;                     // +0x2C
	ObjectCoord3DMap m_map30;            // +0x30 hash_map<ObjectID, Coord3D>
	bool m_flag44;                     // +0x44
};

void MoveToGroupOrder::slot07Set(int)
{
	m_flag24 = true;
}

Coord3D *MoveToGroupOrder::getDestination(int)
{
	return &m_destination;
}

bool MoveToGroupOrder::isNearDestination(const Coord3D *pos)
{
	float dx = pos->x - m_destination.x;
	float dy = pos->y - m_destination.y;
	return dy * dy + dx * dx < 200.0f;
}

bool MoveToGroupOrder::slot11Command(int *outType, GroupOrderCommand *command)
{
	if (m_flag24)
		*outType = 0x430;
	else
		*outType = m_flag25 ? 0x442 : 0x42F;
	command->m_position = m_destination;
	return true;
}

GroupOrder *MoveToGroupOrder::clone()
{
	return new MoveToGroupOrder(*this);
}

// ?rva00547188@MoveToGroupOrder@@QAE_NPAVObject@@H@Z, retail 0x00547188 21B.
// MoveTo destination check used by 0x0054764C: passes &m_destination (+0x18)
// to the rowed predicate at 0x0028ECDB and normalises to bool. Evidence: this+0x18
// Coord3D plus caller 0x0054764C layout (+0x18/+0x24) matches MoveToGroupOrder.
bool MoveToGroupOrder::rva00547188(Object *obj, int)
{
	unsigned char tmp = reinterpret_cast<Rva0028ECDBHost *>(obj)->rva0028ECDB(&m_destination);
	return tmp;
}

void MoveToFormationGroupOrder::slot07Set(int)
{
	m_flag2C = true;
}

Coord3D *MoveToFormationGroupOrder::getDestination(int)
{
	return &m_destination;
}

bool MoveToFormationGroupOrder::isNearDestination(const Coord3D *pos)
{
	float dx = pos->x - m_destination.x;
	float dy = pos->y - m_destination.y;
	return dy * dy + dx * dx < 200.0f;
}

bool MoveToFormationGroupOrder::slot11Command(int *outType, GroupOrderCommand *command)
{
	*outType = 0x464;
	command->m_position = m_destination;
	return true;
}

GroupOrder *MoveToFormationGroupOrder::clone()
{
	return new MoveToFormationGroupOrder(*this);
}

// Native00547F37..00547F88 RET4, slot4 of MoveToFormationGroupOrder
// vtable00C6A4CC installed by the matched constructor. The established map
// at30 holds ObjectID/Coord3D; count40 controls lazy population307B547CB6.
// Lookup then GameLogic49DC5 supplies the Object to219B547E5C, which reads
// the mapped three-float position and configures the object's AI/movement.
void MoveToFormationGroupOrder::rva00547F37(ObjectID id)
{
    if (m_map30.empty())
        rva00547CB6();
    ObjectCoord3DMap *map = &m_map30;
    ObjectCoord3DMap::const_iterator it = map->find(id);
    if (it != map->end()) {
        Object *object = TheGameLogic->findObjectByID(id);
        if (object)
            rva00547E5C(object, &it->second);
    }
}

enum CommandSourceType {CMD_FROM_PLAYER=0};
class Rva00352F9D {public:void rva0035300B(const void*,const Coord3D&,CommandSourceType);};
class AIUpdateInterface {public:char prefix[0x20];Rva00352F9D commands;};
class Object {public:char prefix[0x258];AIUpdateInterface *ai;char gap[0x274-0x25C];void *physics;bool rva002931BA();};
struct OrderedPoint : Coord3D { OrderedPoint(const Coord3D &v){x=v.x;y=v.y;z=v.z;} };

namespace _STL {
typedef pair<const ObjectID,Coord3D> P;
template __declspec(noinline) _Hashtable_node<P>* hashtable<P,ObjectID,rts::hash<ObjectID>,_Select1st<P>,equal_to<ObjectID>,allocator<P> >::_M_find<ObjectID>(const ObjectID&) const;
}
void MoveToGroupOrder::rva005478B5(ObjectID id)
{
 ObjectCoord3DMap *map=reinterpret_cast<ObjectCoord3DMap*>(m_map28);
 ObjectCoord3DMap::const_iterator it=map->find(id);
 const Coord3D *position;
 if(it==map->end())position=rva005476C8(id);
 else position=&it->second;
 Coord3D local=*position;
 Object *object=TheGameLogic->findObjectByID(id);
 if(object && !object->rva002931BA()) {
  AIUpdateInterface *ai=object->ai;
  if(ai) {
   if(object->physics)ai->commands.rva0035300B(object->physics,local,CMD_FROM_PLAYER);
   else rva0054764C(object,ai,&local);
  }
 }
}
