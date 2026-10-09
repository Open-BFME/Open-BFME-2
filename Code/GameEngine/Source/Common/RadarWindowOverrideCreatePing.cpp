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
class Rva002D5333:public Rva002D3556 {public:Rva002D5333(Rva002D4FDB*,PingIterator,const AsciiString&);virtual~Rva002D5333();virtual void rva002D3D2A();virtual void rva002D4AEF(float,float);virtual void rva002D4BA5();private:Rva002D4FDB*owner;PingIterator position;AsciiString name;bool displayed,closed;int id;float x,y;};
class Rva002D4FDB {public:char unknown0[0x5C];void*aptOwner;char unknown60[0x144-0x60];int nextId;PingList pings;};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget*,void*,const char*,const int&);
struct PingOwnerView {char gap[0x5C];void*aptOwner;};

Rva002D5333::Rva002D5333(Rva002D4FDB*parent,PingIterator pos,const AsciiString&input):owner(parent),position(pos),name(input),displayed(false),closed(false),id(parent->nextId++),x(0),y(0){*position=this;if(parent->nextId>=0xffff)parent->nextId=0;}

void Rva002D5333::rva002D4BA5(){if(closed)return;if(displayed&&owner)Rva002D4531Invoke((Rva00222A8BTarget*)g_bfmeAptWindowManager,(void*)owner->aptOwner,"FadeOutRadarPing",id);closed=true;}
Rva002D5333::~Rva002D5333(){if(!closed)rva002D4BA5();}

namespace _STL {
template<> list<Rva002D5333*>::iterator list<Rva002D5333*>::erase(list<Rva002D5333*>::iterator);
}

class PingScalarDestroyView {public:virtual void*destroy(unsigned);};
void Rva002D5333::rva002D3D2A(){if(owner)owner->pings.erase(position);::operator delete(((PingScalarDestroyView*)this)->destroy(0));}
