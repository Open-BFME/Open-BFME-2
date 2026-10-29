// ?updateInterestZones@TacticalAI@@QAEXXZ
// ?updateInterestZones@TacticalAI@@QAEXXZ
// ?updateInterestZones@TacticalAI@@QAEXXZ
// ?updateInterestZones@TacticalAI@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /GX /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/objectdlink
// stlport
// Target 0x002C63A1..0x002C64D0, 303 bytes. WB TacticalAI::DoXfer name lead
// is independently retained by its SkirmishAI caller at +0x164. Native reads
// player+8, chooser+C, generator+10 and the interest-zone vector+20.
// Xfer slots and the two serializer providers agree with matched siblings.
// The 32-byte zone's existing serializer retains its address-derived name.
// Its constructor signature follows complete target 0x002C6234..0x002C6354:
// coordinate address, float, player; member initialization proves 32 bytes.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include <list>
class AsciiString;
struct Coord3DBase;
// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


struct Coord3DBase
{
public:
	Coord3DBase() { x=0.0f; y=0.0f; z=0.0f; }
	// Native retains a temporary cleanup state with no destructor instruction.
	~Coord3DBase() {}
	Coord3DBase(const Coord3DBase &coord3DBase):x(coord3DBase.x),y(coord3DBase.y),z(coord3DBase.z){}
	Coord3DBase &Sub(const Coord3DBase &coord3DBase) {x-=coord3DBase.x; y-=coord3DBase.y; z-=coord3DBase.z; return *this;}
	float GetLengthSqrd2D() const {return x*x+y*y;}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};
class Player;
class __multiple_inheritance Team;
class Rva002C5EF0
{
public:
    Rva002C5EF0(const Coord3DBase &,float,Player *);
    void rva002C5EF0(Xfer *);
public:
    unsigned int id;
    float position[3];
    unsigned int state;
    float radius,value;
    unsigned int frame;
};
class Rva002C589B;
class AITargetChooser
{
public:
	void xfer(Xfer *);
	void rva00505911();
	Rva002C589B *getBestTarget();
	Rva002C589B *rva00505408(int index); // 0x00505408
	AITargetChooser(void *p);
	~AITargetChooser();
	char m_pad[0x20]; // +0x00
};
class AITacticsGenerator
{
public:
	void DoXfer(Xfer *);
	void Register(Team *);
	void UnRegister(Team *);
	void rva005069B4();
	bool activateTactic(struct Rva00506909Request*,void*);
	AITacticsGenerator(void *p);
	~AITacticsGenerator();
	void xfer(Xfer *);
	void rva005059A1(Team *);
	void rva00505A56(Team *);
	bool rva005069CE(struct Rva00506909Request*,void*);
	char m_pad[0x64]; // +0x00
};
class Rva002C5FE8
{
public:
	void rva002C60A9(unsigned int);
	void *rva002C5FE8(int key);
	char m_lead[0x20]; // +0x00
	void **m_begin; // +0x20
	void **m_end; // +0x24
};

class Rva00506A52 { public: void rva00506AFA(); };
class Object;
class TacticalAI
{
public:
	bool checkEnemyForAttackMove(Object *,Object *);
	void DoXfer(Xfer *);
	void updateInterestZones();
	void rva002C6779();
	void rva002C64D0(const Coord3DBase *, int);
	__declspec(noinline) void Register(Team *);
	__declspec(noinline) void UnRegister(Team *);
private:
	char prefix00[8]; // +0x00
	Player *player; // +0x08
	AITargetChooser *chooser; // +0x0C
	AITacticsGenerator *generator; // +0x10
	Rva002C589B *target; // +0x14
	Rva002C589B *fallback; // +0x18
	Rva00506A52 *tail; // +0x1C
	_STL::vector<Rva002C5EF0 *> interestZones; // +0x20
};
// DoXfer (0x002C63A1), Register/UnRegister (0x002C5FAA/0x002C5FB2) and the
// interest-zone merge rva002C64D0 are rowed in TacticalAI.cpp, and
// rva002C6779 in TacticalAIInterestZones.cpp. This unit only declares them;
// copies here duplicated those definitions at link time.
#include "ObjectDlinkPmf.h"
template<class T> class DLINK_ITERATOR {
public:
 typedef T *(T::*GetNextFunc)() const;
 DLINK_ITERATOR(T *cur,GetNextFunc next):current(cur),next(next) {}
 void advance() {if(current) current=(current->*next)();}
 bool done() const{return current==0;} T*cur()const{return current;}
private: T *current; GetNextFunc next;
};
template<> void DLINK_ITERATOR<Object>::advance();
class Rva002C6607Base0 {}; class Rva002C6607Base1 {};
class Team : public Rva002C6607Base0, public Rva002C6607Base1 { public:
 DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
 Team *dlink_next_TeamInstanceList() const {return *(Team**)((char*)this+0x40); }
};
class TeamPrototype { public: char pad[0x334]; Team *head;
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const {return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList);}
};
struct Rva002C6607PlayerView { char pad[0x2ec]; Team *excluded; char gap[0x3c]; _STL::list<TeamPrototype *> prototypes; };
class GameLogic; extern GameLogic *TheGameLogic;
struct Rva002C6607LogicView { char pad[0x40]; unsigned frame; };
extern int g_00DFEFCC;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
struct Rva002C6607ObjectView {
 int unknown; char *tmpl; char pad30[0x30]; Coord3DBase position;
 char pad258[0x258-0x44]; AIUpdateInterface *ai;
};
void TacticalAI::updateInterestZones() {
 for(_STL::vector<Rva002C5EF0*>::iterator z=interestZones.begin();z!=interestZones.end();) {
  if(((Rva002C6607LogicView*)TheGameLogic)->frame - (*z)->frame >= (unsigned)g_00DFEFCC) {
   if(*z) delete *z;
   z=interestZones.erase(z);
  } else ++z;
 }
 typedef _STL::list<TeamPrototype *> PrototypeList;
 PrototypeList &prototypes=((Rva002C6607PlayerView*)player)->prototypes;
 PrototypeList::iterator end=prototypes.end();
 PrototypeList::iterator begin=prototypes.begin();
 PrototypeList::iterator prototypeIt=begin;
 for(;prototypeIt._M_node!=end._M_node;++prototypeIt) {
  for(DLINK_ITERATOR<Team> teams=(*(TeamPrototype * volatile *)&*prototypeIt)->iterate_TeamInstanceList();!teams.done();(player ? teams.advance() : teams.advance())) {
   Team *team=teams.cur();
   if(team==((Rva002C6607PlayerView*)player)->excluded) continue;
   volatile bool found = false;
   DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();
   Rva002C6607ObjectView *obj;
   for(;(obj=(Rva002C6607ObjectView*)objects.cur())!=0 && !found;objects.advance()) {
    _ReadWriteBarrier();
    if(((unsigned char)obj->tmpl[0x108]&8) || ((unsigned char)obj->tmpl[0x113]&4)) {
    	_ReadWriteBarrier();
     Object *victim=obj->ai ? obj->ai->getCurrentVictim() : 0;
     if(victim) {
      Rva002C6607ObjectView *target=(Rva002C6607ObjectView*)victim;
      if(!((unsigned char)target->tmpl[0x108]&0x80) && *(int*)(target->tmpl+0x520)!=4) {
       Coord3DBase delta=target->position;
       delta.Sub(obj->position);
       if(delta.GetLengthSqrd2D() <= 90000.0f) {
        rva002C64D0(&obj->position,-1); found=true;
       }
      }
     }
    }
   }
  }
 }
}
