// ??0Rva0052B278@@QAE@PAX00@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
class Vector3 {
public:
 Vector3() {}
 Vector3(float x,float y,float z):X(x),Y(y),Z(z){}
 float X,Y,Z;
};
class Rva0053947D {public:virtual ~Rva0053947D();};
class Rva00539411 {
public:
 Rva00539411(void *,const int *);
 __forceinline ~Rva00539411() {((Rva0053947D *)this)->Rva0053947D::~Rva0053947D();}
 unsigned m_vtable;
 char m_rest[0x28];
};
struct Arg1Host005C4280;
class Rva005C4230 {
public:
 Rva005C4230(void *,Arg1Host005C4280 *);
 virtual ~Rva005C4230();
 virtual void f01();virtual void f02();virtual void f03();
 virtual void f04();virtual void f05();virtual void f06();
 virtual void setPosition(const Vector3 *);
 char rest[0xc4];
};
struct IconSubTemplate {char pad[0x1c];float height;};
struct IconTemplate {void *name;_STL::vector<IconSubTemplate *> items;};
struct TargetRef00217D4C {void *vtable;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct IconHelpRef {
 TargetRef00217D4C *ptr;
 IconHelpRef():ptr(0){}
 ~IconHelpRef() {if(ptr) ReleaseTreeHintRef00217D4C(ptr);}
};
class Rva002BF4F3 {public:bool rva002BF5B0(const Vector3 *,Vector3 *);};
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class Rva005392C2 {public:void rva0052B045();};
class Rva0052B278:public Rva00539411 {
 _STL::vector<Rva005C4230 *> items;
 void *parent;int id;IconHelpRef help;
public:Rva0052B278(void *,void *,void *);
};
Rva0052B278::Rva0052B278(void *lookup,void *owner,void *point)
 :Rva00539411(lookup,(const int *)&Vector3()),items((m_vtable=0x00c685e0,_STL::allocator<Rva005C4230 *>())),parent(owner),id(-1)
{

 const Vector3 *xy=(const Vector3 *)point;
 Vector3 position;
 position.X=xy->X;position.Y=xy->Y;position.Z=0;
 ((Rva002BF4F3 *)g_00DFEF18)->rva002BF5B0(xy,&position);
 *(Vector3 *)((char *)this+0x18)=position;
 IconTemplate *source=(IconTemplate *)lookup;
 if(source) {
  items.reserve(source->items.size());
  IconSubTemplate **it=source->items.begin();
  IconSubTemplate **end=source->items.end();
  for(;it!=end;++it) {
   Rva005C4230 *part=new Rva005C4230(*it,(Arg1Host005C4280 *)this);
   items.push_back(part);
   Vector3 offset(position.X,position.Y,position.Z);
   offset.Z+=(*it)->height;
   items.back()->setPosition(&offset);
  }
 }
 ((Rva005392C2 *)this)->rva0052B045();
}
