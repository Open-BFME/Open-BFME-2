// cl: /DNDEBUG /MD /GX
// ?rva00451EAC@Rva00451EAC@@QAEXXZ @0x00451EAC 153B
// Unlock: AI idle/face driver. Evidence: calls rowed findObjectByID 0x00049DC5,
// isKindOf 0x0006F039, aiIdle 0x001E8A38, aiFaceObject 0x003C771D,
// aiFacePosition 0x003C7782; TheGameLogic extern; caller 0x00451FA2.
class Object;
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
enum KindOfType
{
	KIND_81 = 0x81
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
struct Coord3D
{
	float x;
	float y;
	float z;
};
class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class Object
{
public:
	bool isKindOf(KindOfType kind) const;
};
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiFaceObject(Object *target, CommandSourceType cmdSource);
	void aiFacePosition(const Coord3D *pos, int cmdSource);
};
class Rva00451EAC
{
public:
	void rva00451EAC();
private:
	char m_pad00[8];
	Object *m_obj; // +8
	char m_pad0C[0x40 - 0x0C];
	ObjectID m_id; // +0x40
	Coord3D m_coord; // +0x44
	char m_pad50[0x7E - 0x50];
	bool m_flag7E; // +0x7E
};
void Rva00451EAC::rva00451EAC()
{
	Object *obj = m_obj;
	if (obj == 0)
		return;
	Object *found = TheGameLogic->findObjectByID(m_id);
	char *holder = *(char **)((char *)obj + 0x258);
	if (holder == 0)
		return;
	if (obj->isKindOf(KIND_81))
		return;
	AICommandInterface *ai = (AICommandInterface *)(holder + 0x20);
	ai->aiIdle(CMD_FROM_AI);
	m_flag7E = true;
	if (found != 0)
		ai->aiFaceObject(found, CMD_FROM_AI);
	else if (m_coord.x != 0.0f || m_coord.y != 0.0f || m_coord.z != 0.0f)
		ai->aiFacePosition(&m_coord, 2);
}
