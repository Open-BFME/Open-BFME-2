// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Include /I.
// stlport
// Native4CE700..4CEA8E,910B RETC. Target/WB11E0BA0 independently establish
// NotifyTargetsOfImminentProbableCrushingMux::doNotifyTargets purpose and
// Object/rate-record/sleep-out ABI. Existing address-derived class spelling
// is retained so matched update callers share one provider.
// No clean BFME1/ZH mux source at committed874e38488. Geometry/filter/result
// dependencies reuse established native views, not a whole inferred layout.
// Object position38 and geometryA8; rate record unsigned interval00,ahead04,
// height08,width0C are witnessed retail accesses. Target motion provider404B
// outputs12B; original name stays unproved. ZH partition-filter semantics are
// the structural lead; native C600A0 slot1 calls the rowed Object29493F bool.
// Explicit member copies avoid memcpy lowering; a local selected maxZ keeps
// native SSE operand order. Bounds depth is Z, width X. The four-int query is
// the existing native625690 wrapper; pointer/int spelling is its ABI view.
#include "Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"

struct NotifyCoord:Coord3D{
 __forceinline NotifyCoord(){}
 __forceinline NotifyCoord(const Coord3D&r){x=r.x;y=r.y;z=r.z;}
 __forceinline NotifyCoord(const NotifyCoord&r){x=r.x;y=r.y;z=r.z;}
 __forceinline ~NotifyCoord(){}
 __forceinline void scale(float s){x*=s;y*=s;z*=s;}
 __forceinline void add(const Coord3D&r){x+=r.x;y+=r.y;z+=r.z;}
 float estimate()const{return GetLengthEstimate2D();}
};
struct Region2D{float x1,y1,x2,y2;};
struct Rva0087E650Bounds{NotifyCoord lo,hi;};
enum GeometryType{GEOMETRY_SPHERE,GEOMETRY_CYLINDER,GEOMETRY_BOX};
class GeometryInfo{public:
 GeometryInfo(GeometryType,bool,float,float,float);virtual ~GeometryInfo();
 float getMaxHeightAbovePosition()const;void rva0087E650(Rva0087E650Bounds*);
 char opaque[0x58];
};
class Rva0087E370{public:void method(const Coord3D&,float,Region2D&)const;};
class Rva0008BB38FloatField{public:float get()const;};
struct Rva0028AC4EEntry;
class Rva0028CECFOwner{public:bool rva0028CECF();};
class Rva0028FC7F{public:void rva0028FC7F(const void*);};
class Object{public:
 char pad0[0x38];NotifyCoord position;char pad44[0xa8-0x44];GeometryInfo geometry;
 const Rva0028AC4EEntry *rva0028AC4E()const;char rva00294815();
 void rva0028E8FD(Coord3D*);void rva0028EC68(int,void*,int);
};
class Rva000421C8{public:
 Rva000421C8():next(0){}virtual ~Rva000421C8(){}virtual bool allow(Object*)=0;virtual int getPlayerMask();
 Rva000421C8 *link(Rva000421C8*);Rva000421C8*next;
};
struct FilterPosition:Coord3D{FilterPosition(const Coord3D&r){x=r.x;y=r.y;z=r.z;}};
class Rva00261603Filter:public Rva000421C8{public:Rva00261603Filter(const Coord3D&,const GeometryInfo&,float,bool);virtual bool allow(Object*);FilterPosition pos;const GeometryInfo&geom;float angle;bool desired;};
class Rva0026119DFilter:public Rva000421C8{public:virtual bool allow(Object*);};
class Rva0026156C:public Rva000421C8{public:
 Rva0026156C(Object*o,int v):object(o),value(v){}virtual ~Rva0026156C(){}virtual bool allow(Object*);
 Object*object;int value;
};
struct NotifyRegion3D{NotifyCoord lo,hi;};
class BfmeWideForwardB{public:BfmeWideResult bfmeForwardWideB(int,int,int,int);};
extern PartitionManager *ThePartitionManager;
int GetGameLogicRandomValue(int,int,char*,int);
double __cdecl Rva000422A0Atan2(float,float);
enum UpdateSleepTime{UPDATE_SLEEP_NONE=1};
class Rva004CE700Notifier{public:bool rva004CE700(Object*,const int*,UpdateSleepTime*);};
template<class T>inline const T& nmin(const T&a,const T&b){return a<b?a:b;}
template<class T>inline const T& nmax(const T&a,const T&b){return a>b?a:b;}
bool Rva004CE700Notifier::rva004CE700(Object*object,const int*data,UpdateSleepTime*sleep){
 *sleep=(UpdateSleepTime)GetGameLogicRandomValue(data[0],(unsigned)(data[0]*3)/2,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\NotifyTargetsOfImminentProbableCrushingMux.cpp",63);
 const Rva0028AC4EEntry*entry=object->rva0028AC4E();
 if(!entry || ((const Rva0008BB38FloatField*)entry)->get()==0.0f)return false;
 if(object->rva00294815()<=0 || !((Rva0028CECFOwner*)object)->rva0028CECF())return false;
 const int *settings=data;int ahead=settings[1];if(!ahead)return false;
 NotifyCoord velocity;object->rva0028E8FD(&velocity);velocity.scale((float)ahead);
 if(velocity.estimate()<1.0f)return false;
 NotifyCoord position(object->position),end(position);end.add(velocity);
 NotifyCoord center(position);center.add(end);center.scale(0.5f);
 float angle=(float)Rva000422A0Atan2(velocity.y,velocity.x);
 float height=((const float*)settings)[2];if(height<=0.0f)height=object->geometry.getMaxHeightAbovePosition()*3.0f;
 center.z-=height/3.0f;
 float width=((const float*)settings)[3];Rva0087E650Bounds bounds;object->geometry.rva0087E650(&bounds);
 if(width<=0.0f)width=bounds.hi.z-bounds.lo.z;
 float length=bounds.hi.x-bounds.lo.x;
 GeometryInfo projected(GEOMETRY_BOX,false,height,(velocity.estimate()+length)*0.5f,width*0.5f);
 Region2D xy;((const Rva0087E370*)&projected)->method(center,angle,xy);
 NotifyRegion3D query;query.lo.x=xy.x1;query.lo.y=xy.y1;query.lo.z=nmin(position.z,end.z);query.hi.x=xy.x2;query.hi.y=xy.y2;float maxz=nmax(position.z,end.z);query.hi.z=maxz+height;
 Rva00261603Filter collision(center,projected,angle,true);
 Rva0026156C source(object,2);Rva0026119DFilter alive;
 ((Rva000421C8*)&source)->link(&collision)->link(&alive);
 BfmeWideResult result=reinterpret_cast<BfmeWideForwardB *>(ThePartitionManager)->bfmeForwardWideB((int)&query,1,(int)&source,0);
 struct Entry{void *p;float d;};Entry **payload=(Entry**)result.m_value;
 if((unsigned)(payload[1]-payload[0])>0) object->rva0028EC68(11,0,1);
 Object*target;while((target=result.next())!=0)((Rva0028FC7F*)target)->rva0028FC7F(object);
 return true;
}
