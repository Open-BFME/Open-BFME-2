// ?rva002D4FDB@Rva002D4FDB@@QAE?AVRadarEventRefSlot@@PBD@Z
// partial score=0.9840909 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include "ascii_string.h"
#include <list>
class Rva002D4FDB;
class Rva002D5333;
typedef _STL::list<Rva002D5333*> PingList;
typedef PingList::iterator PingIterator;
class Rva002D3556 {public:__forceinline Rva002D3556():references(0){}virtual~Rva002D3556(){}virtual void rva002D3D2A()=0;virtual void rva002D4AEF(float,float)=0;virtual void rva002D4BA5()=0;int references;};
class Rva002D5333:public Rva002D3556 {public:Rva002D5333(Rva002D4FDB*,PingIterator,const AsciiString&);virtual~Rva002D5333();virtual void rva002D3D2A();virtual void rva002D4AEF(float,float);virtual void rva002D4BA5();private:Rva002D4FDB*owner;PingIterator position;AsciiString name;bool displayed,closed;int id;float x,y;};
class RadarEventRefSlot;
class Rva002D4FDB {public:RadarEventRefSlot rva002D4FDB(const char*);char unknown[0x144];int nextId;PingList pings;};
class BfmeAptWindowManager;extern BfmeAptWindowManager*g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget*,void*,const char*,const int&);
struct PingOwnerView {char gap[0x5C];void*aptOwner;};

Rva002D5333::Rva002D5333(Rva002D4FDB*parent,PingIterator pos,const AsciiString&input):owner(parent),position(pos),name(input),displayed(false),closed(false),id(parent->nextId++),x(0),y(0){*position=this;if(parent->nextId>=0xffff)parent->nextId=0;}

void Rva002D5333::rva002D4BA5(){if(closed)return;if(displayed&&owner)Rva002D4531Invoke((Rva00222A8BTarget*)g_bfmeAptWindowManager,((PingOwnerView*)owner)->aptOwner,"FadeOutRadarPing",id);closed=true;}
Rva002D5333::~Rva002D5333(){if(!closed)rva002D4BA5();}

class RadarEventRef {public:void release();virtual ~RadarEventRef();int references;};
class RadarEventRefSlot {public:RadarEventRefSlot(RadarEventRef*p):ptr(p){if(ptr)++ptr->references;}RadarEventRefSlot(const RadarEventRefSlot&s):ptr(s.ptr){if(ptr)++ptr->references;}~RadarEventRefSlot(){if(ptr)ptr->release();}RadarEventRefSlot&operator=(const RadarEventRefSlot&);RadarEventRef*ptr;};
namespace _STL {
template<> list<Rva002D5333*>::iterator list<Rva002D5333*>::insert(list<Rva002D5333*>::iterator,Rva002D5333*const&);
template<> list<Rva002D5333*>::iterator list<Rva002D5333*>::erase(list<Rva002D5333*>::iterator);
}
RadarEventRefSlot Rva002D4FDB::rva002D4FDB(const char*text){PingIterator pos=pings.insert(pings.end(),(Rva002D5333*)0);return RadarEventRefSlot((RadarEventRef*)new Rva002D5333(this,pos,AsciiString(text)));}

extern "C" double __cdecl fabs(double);
int __cdecl Rva002D4464Fire(Rva00222A8BTarget*,void*,const char*,int*,float*,float*);
class PingAptView {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual void v15();virtual const float*getViewInfo();};
static const volatile float threshold=0.5f;
void Rva002D5333::rva002D4AEF(float newX,float newY){if(fabs(newX-x)>=threshold||fabs(0.0)>=threshold){if(displayed&&owner){const float*scale=((PingAptView*)g_bfmeAptWindowManager)->getViewInfo();float sy=newY*scale[1];float sx=newX*scale[0];Rva002D4464Fire((Rva00222A8BTarget*)g_bfmeAptWindowManager,((PingOwnerView*)owner)->aptOwner,"MoveRadarPing",&id,&sx,&sy);}x=newX;y=newY;}}
class PingScalarDestroyView {public:virtual void*destroy(unsigned);};
void Rva002D5333::rva002D3D2A(){if(owner)owner->pings.erase(position);::operator delete(((PingScalarDestroyView*)this)->destroy(0));}
