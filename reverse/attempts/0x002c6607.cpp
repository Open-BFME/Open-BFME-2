// ?updateInterestZones@TacticalAI@@QAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /GX /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/reference/shims/objectdlink
// stlport
// Target 0x002C63A1..0x002C64D0, 303 bytes. WB TacticalAI::DoXfer name lead
// is independently retained by its SkirmishAI caller at +0x164. Native reads
// player+8, chooser+C, generator+10 and the interest-zone vector+20.
// Xfer slots and the two serializer providers agree with matched siblings.
// The 32-byte zone's existing serializer retains its address-derived name.
// Its constructor signature follows complete target 0x002C6234..0x002C6354:
// coordinate address, float, player; member initialization proves 32 bytes.
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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

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
    Coord3DBase(const Coord3DBase &v):x(v.x),y(v.y),z(v.z){}
    // Native retains a temporary cleanup state with no destructor instruction.
    ~Coord3DBase() {}
    float x,y,z;
    Coord3DBase &Sub(const Coord3DBase &b) {x-=b.x; y-=b.y; z-=b.z; return *this;}
    float GetLengthSqrd2D() const {return x*x+y*y;}
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
class AITargetChooser { public: void xfer(Xfer *); void rva00505911(); Rva002C589B *getBestTarget(); };
class Rva00506909
{
public:
    void xfer(Xfer *);
    void rva005059A1(Team *);
    void rva00505A56(Team *);
    void rva005069B4();
    bool rva005069CE(struct Rva00506909Request*,void*);
};
class Rva002C5FE8 { public: void rva002C60A9(unsigned int); };

class Rva00506A52 { public: void rva00506AFA(); };
class TacticalAI
{
public:
    void DoXfer(Xfer *);
    void updateInterestZones();
    void rva002C6779();
    void rva002C64D0(const Coord3DBase *, int);
    __declspec(noinline) void Register(Team *);
    __declspec(noinline) void UnRegister(Team *);
private:
    char prefix00[8];
    Player *player;
    AITargetChooser *chooser;
    Rva00506909 *generator;
    Rva002C589B *target;
    Rva002C589B *fallback;
    Rva00506A52 *tail;
    _STL::vector<Rva002C5EF0 *> interestZones;
};
void TacticalAI::DoXfer(Xfer *xfer)
{
    Xfer::Version version(1,1);
    *xfer==version;
    bool hasChooser=chooser!=0;
    *xfer==hasChooser;
    if(chooser) chooser->xfer(xfer);
    generator->xfer(xfer);
    unsigned int count=interestZones.size();
    *xfer==count;
    if(xfer->IsStoring())
    {
        Rva002C5EF0 **end=interestZones.end();
        for(Rva002C5EF0 **i=interestZones.begin();i!=end;++i)
            (*i)->rva002C5EF0(xfer);
    }
    else if(xfer->IsLoading())
    {
        for(unsigned int i=0;i<count;++i)
        {
            Rva002C5EF0 *zone=new Rva002C5EF0(Coord3DBase(),0.0f,player);
            zone->rva002C5EF0(xfer);
            interestZones.push_back(zone);
        }
    }
}

// Complete eight-byte generator forwarding tails, formerly in SkirmishAI.cpp.
void TacticalAI::Register(Team *team)
{
    generator->rva005059A1(team);
}

void TacticalAI::UnRegister(Team *team)
{
    generator->rva00505A56(team);
}

// Complete native 002C64D0..002C65EB, 283 bytes. Caller 002C677E uses an
// object's coordinate and -1; recursion preserves an existing zone's id.
// Native constants bound the vector to 20 zones, merge within 600 squared,
// and initialize a newly allocated zone with radius 300. Purpose inferred.
void TacticalAI::rva002C64D0(const Coord3DBase *position, int id)
{
    if (interestZones.size() >= 20)
    {
        Rva002C5EF0 *old=*interestZones.begin();
        if(old) delete old;
        interestZones.erase(interestZones.begin());
    }
    int nearestId=-1;
    float nearestDistance=-1.0f;
    Rva002C5EF0 **end=interestZones.end();
    for(Rva002C5EF0 **i=interestZones.begin();i!=end;++i)
    {
        float dx=(*i)->position[0]-position->x;
        float dy=(*i)->position[1]-position->y;
        float distance=dx*dx+dy*dy;
        if(distance<nearestDistance || nearestDistance<0.0f)
        {
            nearestDistance=distance;
            nearestId=(*i)->id;
        }
    }
    if(!(nearestDistance>=360000.0f || nearestDistance==-1.0f))
    {
        if(nearestId!=-1)
        {
            reinterpret_cast<Rva002C5FE8 *>(this)->rva002C60A9(nearestId);
            rva002C64D0(position,nearestId);
        }
    }
    else
    {
        Rva002C5EF0 *zone=new Rva002C5EF0(*position,300.0f,player);
        if(id!=-1) zone->id=id;
        interestZones.push_back(zone);
    }
}
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
 PrototypeList::iterator p=prototypes.begin();
 PrototypeList::iterator end=prototypes.end();
 for(;p!=end;++p) {
  for(DLINK_ITERATOR<Team> teams=(*p)->iterate_TeamInstanceList();!teams.done();teams.advance()) {
   Team *team=teams.cur();
   if(team==((Rva002C6607PlayerView*)player)->excluded) continue;
   bool found=false;
   DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();
   for(;!objects.done() && !found;objects.advance()) {
    Rva002C6607ObjectView *obj=(Rva002C6607ObjectView*)objects.cur();
    if(((unsigned char)obj->tmpl[0x108]&8) || ((unsigned char)obj->tmpl[0x113]&4)) {
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
void TacticalAI::rva002C6779() {
 updateInterestZones();
 if(chooser) chooser->rva00505911();
 generator->rva005069B4();
 Rva002C589B *request;
 if(chooser) target=request=chooser->getBestTarget();
 else request=fallback;
 if(request) generator->rva005069CE((Rva00506909Request*)request,player);
 tail->rva00506AFA();
}
