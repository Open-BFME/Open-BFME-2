// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include/Lib
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
#include "../../Common/GameLogicObjectLookupView.h"
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

class Object;

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

// Target 0x00547E5C is called by the rowed formation slot-4 dispatcher.
// Retail independently establishes Object template/AI/physics at +4/+258/+274,
// the template high kind word at +11C and AI query vslot 137. The query name
// remains unknown. Existing command providers establish the command ABI.
// The kind-26 branch places the object with angle +28; both paths then issue
// a facing move (or attack-move when +2C is set). No donor identity is asserted.
enum CommandSourceType {CMD_FROM_PLAYER=0};
enum PathfindLayerEnum {LAYER_GROUND=1};
class AICommandInterface {public:
 void aiMoveToPositionAndFaceDirection(const Coord3D*,CommandSourceType,float);
 void aiAttackMoveToPositionAndFaceDirection(const Coord3D*,int,CommandSourceType,float);
};
class AIUpdateInterface {public: char prefix[0x20];AICommandInterface commands;};
class FormationTemplateView {public:char prefix[0x11C];unsigned kindHigh;};
class Object {public:
 char prefix0[4];FormationTemplateView *info;char gap8[0x258-8];AIUpdateInterface *ai;char gap25C[0x274-0x25C];void *physics;
 void rva0028AD00(int,float,int);void rva0028ACEE(int,int);
};
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
class FormationAIQuery {public:
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
void MoveToFormationGroupOrder::rva00547E5C(Object *object,const Coord3D *position)
{
 AIUpdateInterface *ai=object->ai;
 if(!ai)return;
 if(reinterpret_cast<FormationAIQuery*>(ai)->slot137() || object->physics) {
  PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(object,position);
  Coord3D goal;
  goal.z=TheTerrainLogic->slot7(position->x,position->y,layer,0,true);
  goal.x=position->x;goal.y=position->y;
  if(object->info->kindHigh&0x04000000)object->rva0028AD00((int)&goal,m_angle,layer);
  else object->rva0028ACEE((int)&goal,layer);
 }
 if(m_flag2C)ai->commands.aiAttackMoveToPositionAndFaceDirection(position,0x7fffffff,CMD_FROM_PLAYER,m_angle);
 else ai->commands.aiMoveToPositionAndFaceDirection(position,CMD_FROM_PLAYER,m_angle);
}
