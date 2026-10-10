// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include
// Native 0x000E0584..0x000E07F4 (624B), the 0xE07F4 object callback's receiver.
// Target evidence: parent BaseHeightMap +0x3868 allocates the same 0x26C owner;
// 0xE0AE2 initializes its four SegmentedLineClass objects and coordinate vector.
// WB 0x87D140/0x87D6E0 supplies the constructor/lifetime relationship, not an API name.
// Native list traversal, virtual position/transform slots, split keys and edge deduplication
// are measured here. STLport vector operations and existing ZH WW3D/SegmentedLine
// source guide the library calls. The original owner/order payload names remain unknown.
// Existing ArmorTemplate-returning manager pins are storage ABI spellings only;
// no assertion is made that these order records are ArmorTemplate objects.
// The insertion result is two dwords plus a byte: its natural alignment is required.
// Coordinate argument evaluation completes before storing the callback/render temporary.
// stlport
#include <vector>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "Lib/Coord3D.h"
struct CoordCopy {Coord3D value; __forceinline CoordCopy(float x,float y,float z){_ReadWriteBarrier();value.x=x;value.y=y;value.z=z;}};
class ArmorTemplate;
enum NameKeyType { NativeNameKeyUnknown=0 };
class Rva0035516C {public:const ArmorTemplate*rva0035516C(NameKeyType)const;};
class Rva00355B61 {public:const ArmorTemplate*rva00355155(NameKeyType)const;};
class AiOrdersManager;extern AiOrdersManager*TheAiOrdersManager;
struct NativeListNode {NativeListNode*next,*prev;int value;};
struct NativeOrders {int unknown;NativeListNode*head;int split0,split1,split2;};
class NativeOrder {public:
virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual Coord3D *position(Coord3D*);
};
class Rva000E07F4Obj {public:char prefix[0x38];Coord3D position;char unknown44[0x30];int id;};
class RenderObjClass {public:
virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22(const Coord3D&);
};
class SegmentedLineClass;
class RenderInfoClass;
class WW3D {public:static bool Render(RenderObjClass&,RenderInfoClass&);};
class Rva000E04CE {public:void rva000E04CE(SegmentedLineClass*);};
struct Rva000E007DPair {int m00,m04;};
struct NativeNode {NativeNode*next;Rva000E007DPair key;};
class Rva000E01B0 {public:NativeNode*rva000E01B0(const Rva000E007DPair*);};
class Rva000E0536 {public:void rva000E055A(void*,unsigned);};
namespace _STL {
template<> void vector<Coord3D>::push_back(const Coord3D&);
template<> Coord3D *vector<Coord3D>::erase(Coord3D*,Coord3D*);
}
class Rva000E07F4Host {public:
void rva000E0584(Rva000E07F4Obj*);
RenderObjClass*hint;SegmentedLineClass*lines[4];char unknown14[8];RenderInfoClass*info;char unknown20[0x228];int previousID;_STL::vector<Coord3D> points;char hashHeader[20];
};
void Rva000E07F4Host::rva000E0584(Rva000E07F4Obj *obj) {
 if(!obj)return;
 NativeOrders *orders=(NativeOrders*)((Rva0035516C*)TheAiOrdersManager)->rva0035516C((NameKeyType)obj->id);
 if(!orders||orders->head->next==orders->head)return;
 previousID=0;
 Coord3D previous={obj->position.x,obj->position.y,obj->position.z};
 {_STL::vector<Coord3D>&v=points;v.erase(v.begin(),v.end());Coord3D p={previous.x,previous.y,previous.z};v.push_back(p);}
 SegmentedLineClass*line=lines[0];int prior=0;
 int split1=orders->split1;int split2=orders->split2;
 NativeListNode *it=orders->head->next;
 for(;it!=orders->head;it=it->next) {
  if(it->value==orders->split0) {
   if(prior) {
    NativeOrder*n=(NativeOrder*)((Rva00355B61*)TheAiOrdersManager)->rva00355155((NameKeyType)prior);
    if(n) {Coord3D*pos=n->position(&previous);Coord3D p={pos->x,pos->y,pos->z};points.push_back(p);}
   }
   prior=0;
   ((Rva000E04CE*)this)->rva000E04CE(line);
   line=lines[1];
  }
  if(it->value==split1) {prior=split1;((Rva000E04CE*)this)->rva000E04CE(line);line=lines[2];}
  if(it->value==split2) {prior=split1;((Rva000E04CE*)this)->rva000E04CE(line);line=lines[3];}
  NativeOrder*n=(NativeOrder*)((Rva00355B61*)TheAiOrdersManager)->rva00355155((NameKeyType)it->value);
  if(n) {
   Coord3D *position=n->position(&previous);
   if(previousID) {
    Rva000E007DPair key={previousID,it->value};
    if(!((Rva000E01B0*)hashHeader)->rva000E01B0(&key)) {
     struct Receipt {int m00,m04;unsigned char m08;} out;((Rva000E0536*)hashHeader)->rva000E055A(&out,(unsigned)&key);
    }else {
     ((Rva000E04CE*)this)->rva000E04CE(line);
     points.clear();
    }
   }
   {CoordCopy p(position->x,position->y,position->z);points.push_back(p.value);hint->s22(p.value);}
   WW3D::Render(*hint,*info);
   previous=*position;
  }
  previousID=it->value;
 }
 if(points.size()>1)((Rva000E04CE*)this)->rva000E04CE(line);
}
