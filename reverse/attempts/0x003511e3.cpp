// ?rva003511E3@Rva0033F6DA@@QAEHXZ
// partial score=0.95 date=2026-10-04
// cl: /O1 /MD /arch:SSE
// ?rva003511E3@Rva0033F6DA@@QAEHXZ, RVA 0x003511E3, 378 bytes.
// Slot 4 (offset 0x10) of vtable 0x00811740 (ctor 0x0033F6DA hash 0xEBE7A650,
// xfer 0x00341D9B slot 3, update 0x00341DFC slot 6). onEnter-style body:
// m_20 = machine slot 0x28 (createSnapshot), then AI discriminant slot
// 0x1EC (123) selects 0..4 work (guard-mode reset, terrain layer, team,
// object, position), tail publishes slot 0x1F4 (125) to +0x6C and returns
// m_20 slot 0x1C/0x20 chain with -2 early-out. Evidence: rowed
// AIUpdateInterface::rva00262D40 0x00262D40, Coord3D::GetLengthEstimate
// 0x00003ACE, GameLogic::findObjectByID 0x00049DC5, setters 0x0033F83D and
// 0x0033F852, Rva0028BBE1 0x0028BBE1, pins findInstance 0x0039F761 and
// TerrainLogic::getLayerForDestination 0x002802FE, globals TheTeamFactory
// 0x00A028BC TheGameLogic 0x009FE78C TheTerrainLogic 0x009FEC50, AI flag
// +0x3CD, owner angle +0x44 and AI +0x258, snapshot +0x44/+0x48/+0x54/
// +0x60/+0x64/+0x6C/+0x1C.
typedef bool Bool;
#define NULL 0
struct Coord3D
{
	float x, y, z;
	float GetLengthEstimate() const;
};
enum ObjectID
{
	INVALID_ID = 0
};
enum PathfindLayerEnum
{
	LAYER_0 = 0,
	LAYER_1 = 1
};
class Object;
class Team;
class Snapshot;
class Rva004DF2E2
{
public:
	void rva004DF3B0(void *p);
};
class Rva0028BBE1
{
public:
	void rva0028BBE1(void *p);
};
struct Source0033F852
{
	char m_pad00[0x34];
	int m_34;
};
class Rva0033F852
{
public:
	void rva0033F852(const Source0033F852 *src);
};
struct Source0033F83D
{
	char m_pad00[0x74];
	int m_74;
};
class Rva0033F83D
{
public:
	void rva0033F83D(const Source0033F83D *src);
};
class Rva0039F761Owner
{
public:
	Team *findInstance(void *key);
};
class TeamFactory
{
public:
	char m_pad[0x34];
	int m_34;
};
extern TeamFactory *TheTeamFactory;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AIUpdateInterface : public VSlots<118>
{
public:
	virtual const Coord3D *v118();
	virtual ObjectID v119();
	virtual void *v120();
	virtual int v121();
	virtual void v122();
	virtual int v123();
	virtual void v124();
	virtual int v125();
	void rva00262D40(int mode);
public:
	char m_pad04[0x3CD - 0x04];
	Bool m_3CD;
};
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual int s4();
	virtual void s5();
	virtual void s6();
	virtual int s7();
	virtual int s8(int v);
	char m_pad04[0x1C - 0x04];
	int m_1C;
	char m_pad20[0x3C - 0x20];
	int m_3C;
	int m_40;
	int m_44;
	Coord3D m_48;
	Coord3D m_54;
	unsigned char m_60;
	char m_pad61[0x64 - 0x61];
	float m_64;
	char m_pad68[0x6C - 0x68];
	int m_6C;
};
class StateMachine
{
public:
	virtual void sm0();
	virtual void sm1();
	virtual void sm2();
	virtual void sm3();
	virtual void sm4();
	virtual void sm5();
	virtual void sm6();
	virtual void sm7();
	virtual void sm8();
	virtual void sm9();
	virtual Snapshot *createSnapshot();
	Object *getOwner() const { return m_owner; }
private:
	char m_pad04[0x14 - 0x04];
	Object *m_owner;
};
class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos38;
	float m_angle44;
	char m_pad48[0x74 - 0x48];
	int m_id74;
	char m_pad78[0x23C - 0x78];
	Rva004DF2E2 *m_23C;
	char m_pad240[0x258 - 0x240];
	AIUpdateInterface *m_ai258;
};
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	Bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
class Rva0033F6DA : public State
{
public:
	int rva003511E3();
private:
	Snapshot *m_20;
};
// ?rva003511E3@Rva0033F6DA@@QAEHXZ present-unmatched
int Rva0033F6DA::rva003511E3()
{
	StateMachine *machine = m_machine;
	Object *owner = machine->getOwner();
	AIUpdateInterface *ai = owner->m_ai258;
	m_20 = machine->createSnapshot();
	int kind = ai->v123();
	if (kind == 4) {
		ai->rva00262D40(0);
		return -2;
	}
	switch (kind) {
	case 0: {
		float ang = owner->m_angle44;
		const Coord3D *p = ai->v118();
		Snapshot *snap = m_20;
		snap->m_48 = *p;
		snap->m_64 = ang;
		const Coord3D *p2 = ai->v118();
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(owner, p2);
		if (layer != LAYER_1)
			ai->m_3CD = true;
		break;
	}
	case 1: {
		ObjectID id = ai->v119();
		Object *obj = TheGameLogic->findObjectByID(id);
		((Rva0033F83D *)m_20)->rva0033F83D((const Source0033F83D *)obj);
		((Rva0028BBE1 *)owner)->rva0028BBE1(obj);
		break;
	}
	case 2: {
		void *key = ai->v120();
		Team *t = ((Rva0039F761Owner *)TheTeamFactory)->findInstance(key);
		((Rva0033F852 *)m_20)->rva0033F852((const Source0033F852 *)t);
		break;
	}
	case 3: {
		int v = ai->v121();
		m_20->m_44 = v;
		const Coord3D *p = ai->v118();
		float len = p->GetLengthEstimate();
		if (len <= 0.0f) {
		} else {
			const Coord3D *p2 = ai->v118();
			Snapshot *snap = m_20;
			snap->m_54 = *p2;
			snap->m_60 = 1;
		}
		break;
	}
	default:
		break;
	}
	int v125 = ai->v125();
	m_20->m_6C = v125;
	int r = m_20->s7();
	if (r == -2)
		return -2;
	int arg = m_20->m_1C;
	return m_20->s8(arg);
}
