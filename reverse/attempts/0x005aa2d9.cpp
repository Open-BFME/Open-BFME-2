// ?rva005AA2D9@Rva0015334F@@QAEXPAURva005AA55DRecord@@PBUCoord3D@@1@Z
// partial score=0.72 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// The "FlankAttack" skirmish-AI tactic (vtable 0x00871EB0; ctor 0x005AA23E in
// Rva004ECECDTacticCtors.cpp, dtor 0x005AA55D in Rva005AA55DDtor.cpp, slot 9
// in Rva004ECECDTacticCreate.cpp). Base chain, all address-derived:
// AITacticOffensive (ctor 0x005DC722) over the AITactic.cpp object AITactic.
// +0x58 owns the flank route (Rva0015334F, 0x10 bytes): the index of the next
// point and a vector<Coord3D> of points, filled by 0x005AA2D9 and transferred
// by 0x005AA4C1.
//
//   0x005AA0D8  slot 1: never against a target sitting on its owner's
//               "Player_%d_Start" waypoint when that waypoint is of kind 5,
//               nor one closer than sqrt(2000000) to this owner's base
//               (0x004EBF4B), else the base test
//   0x005AA60F  slot 5: xfer: the AITactic's, then the route
//   0x005AA5AE  slot 6: with a team, plan the route from the team's centre
//               to the +0x20 record's point; otherwise stop
//   0x005AA1EA  slot 7 (not here yet): while running, once 0x004ED169 says so or the record
//               is flagged, head for the next route point, or stop (1, 0)
//               when the route is done
#include <vector>
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase {
 Coord3D() {}
 Coord3D(const Coord3D &) throw();
 void normalize();
 void scale(float f) { x*=f; y*=f; z*=f; }
 void add(const Coord3D *p) { x+=p->x; y+=p->y; z+=p->z; }
 static void crossProduct(const Coord3D *a,const Coord3D *b,Coord3D *r) {
 r->x=a->y*b->z-a->z*b->y; r->y=a->z*b->x-a->x*b->z; r->z=a->x*b->y-a->y*b->x;
 }
};

class Xfer;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameSlot
{
public:
	char m_pad00[0x10];
	int m_10;		// +0x10, the slot's start position index
};

struct Rva00506C82Arg;
GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

class Waypoint
{
public:
	char m_pad00[0x60];
	int m_60;		// +0x60
};
Waypoint *Rva00506CC3FindWaypoint(const AsciiString &name);

class Rva002C589B
{
public:
	Object *rva002C5DA6();
	char m_pad00[0x0C];
	Coord3D m_0C;		// +0x0C
};

class Rva004EBF4B
{
public:
	void rva004EBF4B(Coord3D *out);
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class Team
{
public:
	void rva0039DA2A(Coord3D *out) const;
};

struct Rva005AA55DRecord
{
	char m_pad00[0x0C];
	Coord3D m_point0C;	// +0x0C
	bool m_18;		// +0x18
};

class Rva0015334F
{
public:
	void rva005AA2D9(Rva005AA55DRecord *record, const Coord3D *from, const Coord3D *to);
	Coord3D getPivotPoint(Rva005AA55DRecord*,const Coord3D*,const Coord3D*);
	void xfer(Xfer *xfer);
	int m_next;			// +0x00
	_STL::vector<Coord3D> m_points;	// +0x04
};

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void initializeTeamTemplate();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	Team *rva004ECECD(int index);
	unsigned char rva004ED169();
	void rva004ED342(void *point);
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	unsigned char checkTarget(void *request);
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x20 - 0x11];
	Rva005AA55DRecord *m_record;	// +0x20
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIFlankAttackTactic : public AITacticOffensive
{
public:
	virtual ~AIFlankAttackTactic();
	virtual bool canRun(void *request);
	virtual void xfer(Xfer *xfer);
	virtual void run();
private:
	Rva0015334F *m_route;	// +0x58
};

bool AIFlankAttackTactic::canRun(void *request)
{
	Rva002C589B *target = (Rva002C589B *)request;
	Object *obj = target->rva002C5DA6();
	if (obj) {
		GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)obj->getControllingPlayer());
		if (slot) {
			int start = slot->m_10;
			AsciiString name;
			name.format("Player_%d_Start", start + 1);
			Waypoint *waypoint = Rva00506CC3FindWaypoint(name);
			if (waypoint && waypoint->m_60 == 5)
				return false;
		}
	}
	Coord3D base;
	Rva004EBF4B *record = (Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva004EBF4B(&base);
	base.x -= target->m_0C.x;
	base.y -= target->m_0C.y;
	base.z -= target->m_0C.z;
	if (base.x * base.x + base.y * base.y + base.z * base.z < 2000000.0f)
		return false;
	if (checkTarget(request))
		return true;
	return false;
}

void AIFlankAttackTactic::run()
{
	Team *team = rva004ECECD(0);
	if (team) {
		Coord3D from;
		team->rva0039DA2A(&from);
		Coord3D to;
		to.x = m_record->m_point0C.x;
		to.y = m_record->m_point0C.y;
		to.z = m_record->m_point0C.z;
		m_route->rva005AA2D9(m_record, &from, &to);
	} else {
		end(0, 0);
	}
}

void AIFlankAttackTactic::xfer(Xfer *xfer)
{
	AITactic::xfer(xfer);
	m_route->xfer(xfer);
}

float GetGameLogicRandomValueReal(float,float,char*,int);
int GetGameLogicRandomValue(int,int,char*,int);
void Rva0015334F::rva005AA2D9(Rva005AA55DRecord *record,const Coord3D *from,const Coord3D *to) {
 unsigned distance=GetGameLogicRandomValueReal(0.0f,400.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\OffensiveTactics\\AIFlankAttackTactic.cpp",78)+600.0f;
 Coord3D direction; direction.x=to->x-from->x; direction.y=to->y-from->y; direction.z=to->z-from->z;
 direction.normalize();
 Coord3D extended; extended.x=to->x; extended.y=to->y; extended.z=to->z;
 direction.scale((float)distance); extended.add(&direction);
 Coord3D pivot=getPivotPoint(record,from,to);
 Coord3D up; up.x=0.0f; up.y=0.0f; up.z=1.0f;
 if (GetGameLogicRandomValue(0,1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\OffensiveTactics\\AIFlankAttackTactic.cpp",91)==1) up.z=-1.0f;
 Coord3D side; Coord3D::crossProduct(&direction,&up,&side); side.normalize(); side.scale((float)distance); pivot.add(&side);
 m_points.push_back(*from); m_points.push_back(pivot); m_points.push_back(extended); m_points.push_back(*to);
}
