// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Native 002A4E1F..002A57BD and WB 00DC0B00 establish the complete preview flow.
// Native selection/hash behavior and offsets differ from the debug-build body.
// Coord3D is retail's class with the empty user destructor, as WB's EH states around each position show.
#define _STLP_USE_STATIC_LIB
#define _STLP_USE_MALLOC
#define _CRTIMP
#define COORD2D_VIEW_DTOR
#define COORD3D_VIEW_DTOR
#include "../../../Libraries/Include/Lib/Coord2DCtorView.h"
#include "../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include <list>
#include <vector>
#include <string>
#include <math.h>

class Thing { public: void setOrientation(float); };
class Drawable {
public:
 void setPosition(const Coord3D *);
 char prefix[0xB0]; float opacity; char gapB4[0xFC-0xB4]; class Object *object;
 class Object *getObject() const {return object;}
};
struct ShadowView { char prefix[8]; Coord3D position; char gap14[12]; float angle; char gap24[0x58-0x24]; float width,height;
 __forceinline Coord2D getSize() const {return Coord2D(width,height);}
 __forceinline void setSize(float w,float h) {width=w;height=h;} };
class Rva0029A469 {
public:
 ShadowView *shadow;
 void rva0029A469(float);
 __forceinline float width() const { return shadow?shadow->width:0.0f; }
 __forceinline float height() const { return shadow?shadow->height:0.0f; }
 void setPosition(const Coord3D &p) { if(shadow)shadow->position=p; }
 void setOrientation(float a) { if(shadow)shadow->angle=a; }
 void setWidth(float w) { if(shadow)shadow->setSize(w,shadow->height); }
};
class ThingTemplate {public: char prefix[0x18]; float width;};
class Object {public:char p0[0x38];Coord3D position;char prefix[0x438-0x44];unsigned char flags; const Coord3D *getPosition() const {return &position;}};
#include "../../Include/Common/Player.h"
#include "../../Include/Common/PlayerList.h"
#include "../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
template<int N>class PreviewSlots:public PreviewSlots<N-1>{public:virtual void slot(char(*)[N]);};
template<>class PreviewSlots<0>{};
#include "../../Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;
extern int BfmeClientFramesPerSecond;

struct IdNode {IdNode *next,*prev;ObjectID id;};
class Rva0029FB3BMember {public: IdNode *head; void *init(void *);};
class PoolMember {public:void Rva00268902() throw();};
#include "../../Include/Common/Rva001EB984Member.h"
#include "../../Include/Common/Rva001EB769.h"
class SelectedIDs:public Rva0029FB3BMember {
public:
 SelectedIDs(const char &a){init((void*)&a);}
 ~SelectedIDs() throw(){reinterpret_cast<PoolMember*>(this)->Rva00268902();}
};
namespace _STL {
template<> list<Object*>::iterator list<Object*>::insert(list<Object*>::iterator,Object *const&);
}
#include "../../Include/Common/Rva001EB130Holder.h"
class ObjectList:public Rva001EB130Holder {
public:
 ObjectList(const char &a){reinterpret_cast<Rva001EB984Member*>(this)->init((void*)&a);}
 ~ObjectList() throw(){reinterpret_cast<Rva001EB769*>(this)->rva001EB769();}
 void push_back(Object *const&o){_STL::list<Object*> &l=*reinterpret_cast<_STL::list<Object*>*>(this);l.insert(l.end(),o);}
};
struct Rva00422544List;
class Rva004233F5 {public:int rva004233F5(Rva00422544List*,float);};
struct Placement32 {ThingTemplate **type;ObjectID object;char gap8[8];ICoord2D position;char tail[8];};
class Formation {public:Placement32 *first,*last,*limit;};
class FormationAssistant {
public:
 char prefix[0x10];ThingTemplate *templates[4];char gap20[0x2C-0x20];float threshold,delay;
 bool getValidSelectedObjectsForPlayer(Player*,Rva0029FB3BMember*);
 Formation *rva00424E77(int,Rva001EB130Holder*,const Coord3D*);
};
class Rva0022AD10Subsystem;
extern Rva0022AD10Subsystem *TheFormationAssistant;
class Rva00423FBDThis {public:void Delete(_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*);};
struct DrawableListNode {DrawableListNode *m_next;DrawableListNode *m_prev;Drawable *m_drawable;};
class DrawableList {public:DrawableListNode *m_head;};
class InGameUI : public PreviewSlots<51> {
public:
 class FormationPreviewPoolObject;
 virtual bool formationMode();
 virtual void slot52();
 virtual void updateFormationPreview();
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
 virtual const DrawableList *getAllSelectedDrawables();
 Coord2D rva0029D9F9();
 void rva002A3E24();
 void clearFormationPreviewDrawables();
 FormationPreviewPoolObject *rva002A3E5A(ThingTemplate*);
 void rva002A4BFC(Object*,ThingTemplate*,const ICoord2D*,RGBColor);
private:
 char prefix[0x59C-4];int selectionHash;
 struct BfmeE12View {int x,y;FormationPreviewPoolObject *pool;} *first,*last,*limit;
 unsigned expires;bool active;char gap5B1[3];FormationPreviewPoolObject *arrows[4];
 char gap5C4[0x98C-0x5C4];bool valid,directionValid;char gap98E[2];Coord3D start,end;Coord2D direction;int formation;
};
class InGameUI::FormationPreviewPoolObject {public:Drawable *drawable;Rva0029A469 *decal;bool assigned;};
struct BfmeE12 {int id;float key,z;};
namespace _STL {template<> void vector<BfmeE12>::reserve(unsigned);}
static __forceinline float sqr(float v){return v*v;}
struct C2 : Coord2D
{
public:
	__forceinline float GetLengthSqrd() const {return sqr(y)+x*x;}
	__forceinline float GetLength() const {return sqrt(sqr(y)+x*x);}
	__forceinline void Normalize() {float len=GetLength();float inv=1.0f/len;x*=inv;y*=inv;}
	__forceinline C2 &operator*=(float s) {x*=s;y*=s;return *this;}
	__forceinline void Scale(float s) {x*=s;y*=s;}
	__forceinline void Add(const Coord2D &other) {x+=other.x;y+=other.y;}
	__forceinline void Set(float ax,float ay) {x=ax;y=ay;}
};
#define C2R(v) static_cast<C2&>(v)
#define C2C(v) static_cast<const C2&>(v)
class Vector3 {
public:
 float X,Y,Z;
 __forceinline Vector3() {}
 __forceinline Vector3(float x,float y,float z) {X=x;Y=y;Z=z;}
 __forceinline float &operator[](int i) {return (&X)[i];}
 __forceinline const float &operator[](int i) const {return (&X)[i];}
};
#include "../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
// Keep these two helpers visible for native inlining, without emitting external
// copies that compete with the rowed Matrix3D providers.
class Matrix3D {
public:
 __declspec(dllimport) __forceinline Matrix3D(const Vector3 &axis,float angle) {Set(axis,angle);}
 __forceinline void Set(const Vector3 &axis,float angle) {
  float cosine = cosf(angle);
  float s = sinf(angle);
  Set(axis,s,cosine);
 }
 __forceinline void Set(const Vector3 &axis,float s,float c) {
  Row[0].Set(
   (float)(axis[0]*axis[0] + c*(1.0f - axis[0]*axis[0])),
   (float)(axis[0]*axis[1]*(1.0f - c) - axis[2]*s),
   (float)(axis[2]*axis[0]*(1.0f - c) + axis[1]*s),
   0.0f
  );
  Row[1].Set(
   (float)(axis[0]*axis[1]*(1.0f - c) + axis[2]*s),
   (float)(axis[1]*axis[1] + c*(1.0f - axis[1]*axis[1])),
   (float)(axis[1]*axis[2]*(1.0f - c) - axis[0]*s),
   0.0f
  );
  Row[2].Set(
   (float)(axis[2]*axis[0]*(1.0f - c) - axis[1]*s),
   (float)(axis[1]*axis[2]*(1.0f - c) + axis[0]*s),
   (float)(axis[2]*axis[2] + c*(1 - axis[2]*axis[2])),
   0.0f
  );
 }
 __forceinline Vector4 &operator[](int i) {return Row[i];}
 __forceinline const Vector4 &operator[](int i) const {return Row[i];}
 static __declspec(dllimport) __forceinline void Transform_Vector(const Matrix3D &A,const Vector3 &in,Vector3 *out) {
  Vector3 tmp;
  Vector3 *v;
  if (out == &in) {
   tmp = in;
   v = &tmp;
  } else {
   v = (Vector3 *)&in;
  }
  out->X = (A[0].X * v->X + A[0].Y * v->Y + A[0].Z * v->Z + A[0].W);
  out->Y = (A[1].X * v->X + A[1].Y * v->Y + A[1].Z * v->Z + A[1].W);
  out->Z = (A[2].X * v->X + A[2].Y * v->Y + A[2].Z * v->Z + A[2].W);
 }
private:
 Vector4 Row[3];
};

float ACos(float value);
inline float Coord2D::length() const { return (float)sqrt(x*x+y*y); }
inline float Coord2D::toAngle() const
{
    float len = length();
    if (len == 0.0f) {
        return 0.0f;
    }
    const float raw = x / len;
    float cosine;
    if (raw < -1.0f) {
        cosine = -1.0f;
    } else if (raw > 1.0f) {
        cosine = 1.0f;
    } else {
        cosine = raw;
    }
    if (y < 0.0f) {
        return -ACos(cosine);
    }
    return ACos(cosine);
}
__declspec(noinline) inline Coord2D InGameUI::rva0029D9F9() {
 Coord2D dir(end.x-start.x,end.y-start.y);
 if(C2R(dir).GetLengthSqrd()<reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold*reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold) {
  if(directionValid)return direction;
  C2R(dir).Set(0.0f,0.0f);
  const DrawableList *list=getAllSelectedDrawables();
  for(DrawableListNode *node=list->m_head->m_next;node!=list->m_head;node=node->m_next) {
   Object *obj=node->m_drawable->getObject();
   if(obj) {
    const Coord3D *pos=obj->getPosition();
    Coord2D delta(start.x-pos->x,start.y-pos->y);
    C2R(dir).Add(delta);
   }
  }
  C2R(dir).Normalize();
  C2R(dir).Scale(reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold/2.0f);
 } else {
  directionValid=true;
 }
 direction=dir;
 return dir;
}

void InGameUI::updateFormationPreview() {
 InGameUI *owner=this;
 if(!formationMode()) {
  if((unsigned)(last-first)>0) {
   unsigned now=TheGameClient->getFrame();
   if(expires>now) {if(expires-now>500)expires=now;return;}
   float alpha=1.0f-(float)(now-expires)*(1.0f/(BfmeClientFramesPerSecond*0.5f));
   if(alpha<=0.0f){owner->rva002A3E24();return;}
   alpha=_STL::min(1.0f,alpha);
   for(BfmeE12View *it=first;it!=last;++it) {
    Drawable *d=it->pool?it->pool->drawable:0;
    if(d)d->opacity=alpha;
    Rva0029A469 *decal=it->pool?it->pool->decal:0;
    if(decal)decal->rva0029A469(alpha);
   }
   for(int i=0;i<4;++i)if(arrows[i] && arrows[i]->decal)arrows[i]->decal->rva0029A469(alpha);
  }
  return;
 }
 const Coord2D facing=rva0029D9F9();
 float facingSq=C2C(facing).GetLengthSqrd();
 float distance=C2C(facing).GetLength();

 if(!active && facingSq<reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold*reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->threshold) {
  float delay=reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->delay;
  if((float)(TheGameClient->getFrame()-expires)/BfmeClientFramesPerSecond<delay)return;
 }
 active=true;
 char allocator;
 SelectedIDs ids(allocator);
 Player *player=ThePlayerList->m_local;
 reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->getValidSelectedObjectsForPlayer(player,&ids);
 ObjectList objects(allocator);
 int hash=0;
 for(IdNode *it=ids.head->next;it!=ids.head;it=it->next) {
  unsigned hi=hash&0xF8000000;
  unsigned rot=(hash<<5)^(hi>>27);
  ObjectID id=it->id;
  hash=rot^id;
  Object *obj=TheGameLogic->findObjectByID(id);
  if(obj && !(obj->flags&1))objects.push_back(obj);
 }
 if(hash!=selectionHash){owner->rva002A3E24();formation=-1;selectionHash=hash;}
 int type=reinterpret_cast<Rva004233F5*>(TheFormationAssistant)->rva004233F5(reinterpret_cast<Rva00422544List*>(&objects),distance);
 if(type!=formation) {
  formation=-1;
  Formation *plan=reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->rva00424E77(type,&objects,&start);
  if(plan) {
   owner->clearFormationPreviewDrawables();valid=true;formation=type;
   reinterpret_cast<_STL::vector<BfmeE12>*>(&first)->reserve(plan->last-plan->first);
   RGBColor color;color.setFromInt(ThePlayerList->m_local->m_color);
   for(Placement32 *it=plan->first;it!=plan->last;++it) {
    Object *obj=TheGameLogic->findObjectByID(it->object);
    if(obj)owner->rva002A4BFC(obj,it->type[1],&it->position,color);
   }
   reinterpret_cast<Rva00423FBDThis*>(TheFormationAssistant)->Delete(reinterpret_cast<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*>(plan));
  } else valid=false;
 }
 if((unsigned)(last-first)>0) {
  float angle=facing.toAngle();
  Matrix3D matrix(Vector3(0.0f,0.0f,1.0f),angle+1.5707964f);
  for(BfmeE12View *it=first;it!=last;++it) {
   Vector3 in((float)it->x,(float)it->y,0.0f);
   Vector3 out;
   Matrix3D::Transform_Vector(matrix,in,&out);
   Coord3D pos;pos.x=out.X+start.x;pos.y=out.Y+start.y;pos.z=start.z;
   Drawable *d=it->pool?it->pool->drawable:0;
   if(d){d->setPosition(&pos);reinterpret_cast<Thing*>(d)->setOrientation(angle);}
   Rva0029A469 *decal=it->pool?it->pool->decal:0;
   if(decal){decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);}
  }
  for(int i=0;i<4;++i)if(!arrows[i]) {
   FormationAssistant *fa=reinterpret_cast<FormationAssistant*>(TheFormationAssistant);
   ThingTemplate *thingTemplate=fa->templates[i];if(i==3)thingTemplate=fa->templates[2];
   if(thingTemplate)arrows[i]=owner->rva002A3E5A(thingTemplate);
  }
  float arrowWidth=0.0f,lineWidth=0.0f;
  if(arrows[2] && arrows[2]->decal)arrowWidth=arrows[2]->decal->width();
  if(arrows[1] && arrows[1]->decal)lineWidth=reinterpret_cast<FormationAssistant*>(TheFormationAssistant)->templates[1]->width;
  Coord2D unit(facing);C2R(unit).Normalize();
  Coord2D side(-facing.y,facing.x);
  if(C2R(side).GetLength()<arrowWidth/2.0f+lineWidth/2.0f){C2R(side).Normalize();C2R(side)*=lineWidth/2.0f+arrowWidth/2.0f;}
  float offset=30.0f,frontOffset=30.0f;
  if(arrows[1]) {
   offset=arrows[1]->decal->height()*0.5f+30.0f;
   frontOffset=arrows[1]->decal->height()+30.0f;
   Rva0029A469 *decal=arrows[1]->decal;
   if(decal) {
    Coord3D pos(start.x+offset*unit.x,start.y+offset*unit.y,start.z);
    decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);
    float width=C2R(side).GetLength()*2.0f-arrowWidth;
    decal->setWidth(width);
   }
  }
  Coord2D tip(side);
  float tipLength=C2R(tip).GetLength()-10.0f;
  C2R(tip).Normalize();C2R(tip)*=tipLength;
  if(arrows[2] && arrows[2]->decal) {
   Rva0029A469 *decal=arrows[2]->decal;
   Coord3D pos(start.x+offset*unit.x+tip.x,start.y+offset*unit.y+tip.y,start.z);
   decal->setPosition(pos);decal->setOrientation(angle+3.1415927f-1.5707964f);
  }
  if(arrows[3] && arrows[3]->decal) {
   Rva0029A469 *decal=arrows[3]->decal;
   Coord3D pos(start.x+offset*unit.x-tip.x,start.y+offset*unit.y-tip.y,start.z);
   decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);
  }
  if(arrows[0]) {
   frontOffset+=arrows[0]->decal->height()*0.5f;
   Rva0029A469 *decal=arrows[0]->decal;
   if(decal) {
    Coord3D pos(start.x+frontOffset*unit.x,start.y+frontOffset*unit.y,end.z);
    decal->setPosition(pos);decal->setOrientation(angle-1.5707964f);
   }
  }
 }
}
