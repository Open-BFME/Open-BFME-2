// ?rva00547CB6@MoveToFormationGroupOrder@@QAEXXZ
// partial score=0.8183079482499636 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /I.
// stlport
// NEW 00547CB6..00547DE9, 307B: populate formation group-order positions.
#include <list>
#include <hash_map>
#include <string>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class Object{public:char pad[0x74];ObjectID id;};
class Rva001EB769{public:void rva001EB769();};
namespace _STL{
template<> inline _List_base<Object*,allocator<Object*> >::~_List_base(){((Rva001EB769*)this)->rva001EB769();}
}
extern GameLogic*TheGameLogic;
namespace rts{template<class T>struct hash{size_t operator()(const T&v)const{return(size_t)v;}};}
typedef _STL::hash_map<ObjectID,Coord3D,rts::hash<ObjectID>,_STL::equal_to<ObjectID> > ObjectCoord3DMap;
struct Rva00424E77Slot{int unknown0;ObjectID id;char unknown8[16];float x,y;};
class Rva00424E77Result{public:void rva0042245F(float);void rva0042550E(const Coord3D*);Rva00424E77Slot*begin,*end;};
class Rva00424E77Manager{public:Rva00424E77Result*rva00424E77(int,const _STL::list<Object*>*,const Coord3D*);};
class Rva0022AD10Subsystem;
struct Rva00423FBDReceiverView {};
extern Rva0022AD10Subsystem*TheFormationAssistant;
// The existing scalar-delete provider ignores ECX and has RET4. Retail
// passes the singleton in ECX anyway; retain that observed caller ABI via
// a thiscall function-pointer view of the same kept provider.
void __stdcall Rva00423FBDDelete(_STL::basic_string<char>*);
class MoveToFormationGroupOrder{public:void rva00547CB6();
 char pad0[4];ObjectID*first,*last;char padC[0x18-0xc];int kind;Coord3D origin;float angle;bool flag2C;char pad2D[3];ObjectCoord3DMap positions;bool flag44;
};
void MoveToFormationGroupOrder::rva00547CB6(){
 _STL::list<Object*>objects;
 for(ObjectID*p=first;p!=last;++p){Object*object=TheGameLogic->findObjectByID(*p);if(object)objects.insert(objects.end(),object);}
 if(!objects.empty()){
  Rva00424E77Result*formation=((Rva00424E77Manager*)TheFormationAssistant)->rva00424E77(kind,&objects,&origin);
  if(formation){
   formation->rva0042245F(angle);formation->rva0042550E(&origin);
   for(Rva00424E77Slot*p=formation->begin;p!=formation->end;++p){
    Object*object=TheGameLogic->findObjectByID(p->id);
    if(object){Coord3D position={origin.x+p->x,origin.y+p->y,origin.z};ObjectID id=object->id;positions[id]=position;}
   }
   union DestroyAdapter {void(__stdcall*provider)(_STL::basic_string<char>*);void(Rva00423FBDReceiverView::*member)(Rva00424E77Result*);};
   DestroyAdapter destroy;destroy.provider=&Rva00423FBDDelete;
   (((Rva00423FBDReceiverView*)TheFormationAssistant)->*destroy.member)(formation);
  }
 }
}
