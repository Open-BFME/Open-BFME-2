// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native ping family: vftable 0x00C02C1C has scalar-delete/release/move/fade
// at RVAs 2D579A/2D3D2A/2D4AEF/2D4BA5. The base vftable 0x00C02A84
// has scalar-delete 2D3556 then three pure virtual slots. WB Palantir radar
// ping source corroborates the list membership, ID and fade purpose; the
// original target class name remains unknown, so retain the established RVA owner.
// Target ctor [2D3CA5,2D3D2A): refcount4 owner8 iteratorC AsciiString10
// displayed14 closed15 id18 x1C y20. The list iterator's copy constructor
// preserves native load/store order. Owner+144 is the wrapping next ID and
// owner+148 its pointer list. Release [2D3D2A,2D3D61) erases that cursor,
// invokes slot0 with flag0, then frees the returned object.
// Existing fade/dtor/scalar-delete rows are rehomed without increasing credit.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <list>
class Rva002D4FDB;
class Rva002D5333;
typedef _STL::list<Rva002D5333*> PingList;
typedef PingList::iterator PingIterator;
class Rva002D3556 {public:__forceinline Rva002D3556():references(0){}virtual~Rva002D3556(){}virtual void rva002D3D2A()=0;virtual void rva002D4AEF(float,float)=0;virtual void rva002D4BA5()=0;int references;};
class Rva002D5333:public Rva002D3556 {public:Rva002D5333(Rva002D4FDB*,PingIterator,const AsciiString&);virtual~Rva002D5333();virtual void rva002D3D2A();virtual void rva002D4AEF(float,float);virtual void rva002D4BA5();__declspec(noinline) void rva005CB265();private:Rva002D4FDB*owner;PingIterator position;AsciiString name;bool displayed,closed;int id;float x,y;};
class RadarEventRefSlot;
class Rva002D4FDB {public:RadarEventRefSlot rva002D4FDB(const char*);char unknown0[0x5C];void*aptOwner;char unknown60[0x144-0x60];int nextId;PingList pings;};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget*,void*,const char*,const int&);
struct PingOwnerView {char gap[0x5C];void*aptOwner;};

Rva002D5333::Rva002D5333(Rva002D4FDB*parent,PingIterator pos,const AsciiString&input):owner(parent),position(pos),name(input),displayed(false),closed(false),id(parent->nextId++),x(0),y(0){*position=this;if(parent->nextId>=0xffff)parent->nextId=0;}

void Rva002D5333::rva002D4BA5(){if(closed)return;if(displayed&&owner)Rva002D4531Invoke((Rva00222A8BTarget*)g_bfmeAptWindowManager,(void*)owner->aptOwner,"FadeOutRadarPing",id);closed=true;}
Rva002D5333::~Rva002D5333(){if(!closed)rva002D4BA5();}

namespace _STL {
template<> list<Rva002D5333*>::_Node *list<Rva002D5333*>::_M_create_node(Rva002D5333*const&);
template<> list<Rva002D5333*>::iterator list<Rva002D5333*>::erase(list<Rva002D5333*>::iterator);
}

class PingScalarDestroyView {public:virtual void*destroy(unsigned);};
void Rva002D5333::rva002D3D2A(){if(owner)owner->pings.erase(position);::operator delete(((PingScalarDestroyView*)this)->destroy(0));}

// Native [2D4FDB,2D508B),176B; WB Palantir Impl CreateRadarPing confirms
// insert end/null, allocate36, construct with string temporary, add-reference.
// Use the complete STLport insert definition: a declaration alone changes the
// iterator temporary's store order even though the out-of-line call is identical.
class RadarEventRef {public:void release();virtual ~RadarEventRef();int references;};
class RadarEventRefSlot {public:RadarEventRefSlot(RadarEventRef*p):ptr(p){if(ptr)++ptr->references;}RadarEventRefSlot(const RadarEventRefSlot&s):ptr(s.ptr){if(ptr)++ptr->references;}~RadarEventRefSlot(){if(ptr)ptr->release();}RadarEventRefSlot&operator=(const RadarEventRefSlot&);RadarEventRef*ptr;};
RadarEventRefSlot Rva002D4FDB::rva002D4FDB(const char*text){PingIterator pos=pings.insert(pings.end(),(Rva002D5333*)0);return RadarEventRefSlot((RadarEventRef*)new Rva002D5333(this,pos,AsciiString(text)));}

class RadarWindowOverrideSource {public:RadarEventRefSlot rva002D508B(const char*);char unknown[0x10];Rva002D4FDB*impl;};
// Native [2D508B,2D50A8),29B, RET8; outer+10 forwards hidden-return/string.
RadarEventRefSlot RadarWindowOverrideSource::rva002D508B(const char*text){return impl->rva002D4FDB(text);}

// Move [2D4AEF,2D4BA5),182B: target half-pixel test and view scales; the
// second native fabs input is zero, despite the donor's Y-difference test.
// The 205B formatting provider is visible in this TU as in the original
// shared family. With only its declaration, MSVC schedules the sx store
// before the owner push; the implementation restores the native order.
extern "C" double __cdecl fabs(double);
#define inline static inline
#include <math.h>
#undef inline

static __forceinline float PingAbs(float v){return fabs(v);}
AsciiString Rva00222834Get(int val);
AsciiString Rva002228E8Get(float val);

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int kind, const char *value, void *a4, void *a5, void *a6, void *a7);
};

int Rva002D4464Fire(Rva00222A8BTarget *target, void *level, const char *name,
                    int *intParam, float *float1, float *float2)
{
	return target->invoke(level, name, 3, Rva00222834Get(*intParam).str(),
	    (void *)Rva002228E8Get(*float1).str(),
	    (void *)Rva002228E8Get(*float2).str(), 0, 0);
}

class PingAptView {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual const float*getViewInfo();};

void Rva002D5333::rva002D4AEF(float newX,float newY){if(PingAbs(newX-x)>=0.5f||PingAbs(0.0f)>=0.5f){if(displayed&&owner){const float*scale=((PingAptView*)g_bfmeAptWindowManager)->getViewInfo();const float sy=newY*scale[1];const float sx=newX*scale[0];Rva002D4464Fire((Rva00222A8BTarget*)g_bfmeAptWindowManager,(void*)owner->aptOwner,"MoveRadarPing",&id,(float*)&sx,(float*)&sy);}x=newX;y=newY;}}

// Native5CB265 is the shared five-byte tail dispatch through vslot3.
// This typed ping view uses the proven fade slot of C02C1C.
void Rva002D5333::rva005CB265(){rva002D4BA5();}
