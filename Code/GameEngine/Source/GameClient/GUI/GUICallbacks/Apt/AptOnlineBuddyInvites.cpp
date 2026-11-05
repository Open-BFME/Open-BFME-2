// cl: /vmg /vmm /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native5177EB..51795C RET0. WB145D6E0 identifies
// AptOnlineShell::OnYesToInvite; target callers bind this answer callback.
// Neutral receiver name preserves the unreconciled shell class spelling.
#include <new>
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &m_00, const int &m_04) const
{ return m_00 < m_04; }
}
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void(FunctorTarget::*FunctorMethod)();
struct FunctorBinding {FunctorBinding(FunctorMethod m,FunctorTarget *t):target(t),method(m){} FunctorTarget *target;unsigned pad;FunctorMethod method;};
class FunctorWrapperHead { public: FunctorWrapperHead():m_refCount(0) {} virtual void anchor(); int m_refCount; };
class Rva0057BC63FunctorWrapper:public FunctorWrapperHead { public: Rva0057BC63FunctorWrapper(const FunctorBinding&binding):m_binding(binding) {} void invoke(); FunctorBinding m_binding; };
struct Rva0057BC63FunctorHolder {__declspec(noinline) Rva0057BC63FunctorHolder(const FunctorBinding &binding) { Rva0057BC63FunctorWrapper *p=new Rva0057BC63FunctorWrapper(binding);ptr=(TargetRef00217D4C*)p;if(p)++p->m_refCount; }Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &o):ptr(o.ptr){if(ptr)++ptr->references;}TargetRef00217D4C *ptr;};
struct Rva004F6986Member : Rva0057BC63FunctorHolder {
 __forceinline Rva004F6986Member(const FunctorBinding &binding):Rva0057BC63FunctorHolder(binding){}
 __forceinline Rva004F6986Member(const Rva004F6986Member &other):Rva0057BC63FunctorHolder(other){}
 ~Rva004F6986Member(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
struct Rva0051732A {TargetRef00217D4C *ptr;~Rva0051732A(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}Rva0051732A(const Rva0051732A &o):ptr(o.ptr){if(ptr)++ptr->references;}Rva0051732A(Rva004F6986Member value); };
struct Rva00517547 {Rva00517547 *rva00517547(Rva0051732A);TargetRef00217D4C *ptr;};
class Rva0023E8D8 {public:TargetRef00217D4C *ptr;
 Rva0023E8D8(const Rva0023E8D8 &o):ptr(o.ptr){if(ptr)++ptr->references;}
 __forceinline Rva0023E8D8(const Rva0051732A &single){((Rva00517547 *)this)->rva00517547(single);}
 ~Rva0023E8D8(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0023E8D8);
// Pair holder for the two-callback prompts: Rva004C5DD0 is the pair root
// (rowed copy ctor 0x0044BD00, no dtor in the callers' view), the owning temp
// is the derived Rva0044BA4E (ctor over two members, dtor 0x0044BA4E); the
// outer holder is built by the rowed ctor 0x0044BF40 taking the root by value.
class Rva004C5DD0
{
public:
	Rva004C5DD0(const Rva004C5DD0 &o);
	TargetRef00217D4C *m_00; // +0x00
	TargetRef00217D4C *m_04; // +0x04
};
struct Rva0044BA4E : Rva004C5DD0
{
public:
	Rva0044BA4E(Rva004F6986Member,Rva004F6986Member);
	~Rva0044BA4E();
};
struct Rva0044BF40 {TargetRef00217D4C *ptr;Rva0044BF40(Rva004C5DD0 pair);
 Rva0044BF40(const Rva0044BF40 &o):ptr(o.ptr){if(ptr)++ptr->references;}
 ~Rva0044BF40(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}};
namespace n0044BF40 {extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0044BF40);}
struct Rva00516F3F {
 int profile,word4,word8;AsciiString textC,text10;int mode,state;
 void rva00516F3F();Rva00516F3F *rva00516F63(const Rva00516F3F &);
};
class BuddyInviteGameInfo {public:int profile,word4,word8;AsciiString textC,text10;int mode;};
class InviteInput {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual bool blocked();};
struct Rva00517048 {
 char prefix[0x27c];bool online;char pad27d[0x290-0x27d];InviteInput *input;char pad294[4];
 Rva00516F3F invite;
 void rva005177EB();
 void rva00517CC9(const BuddyInviteGameInfo &);
};
class AptOnline {public:void rva005170B4();};
static __forceinline FunctorBinding bind(FunctorMethod method,FunctorTarget *target){FunctorBinding result(method,target);return result;}
#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;
#include "../../../../../Include/GameClient/GameText.h"
extern Rva00517048 *g_Va00A04904;
// WB145D6E0 identifies OnYesToInvite; native5177EB..51795C RET0.
void Rva00517048::rva005177EB()
{
 if(!g_Va00A04904)return;
 invite.state=invite.mode==1?3:2;
 _STL::map<int,int> *map=(_STL::map<int,int> *)TheGameSpyInfo->getBuddyMap();
 Rva00516F3F &pending=invite;
 int profile=pending.profile;
 _STL::map<int,int>::iterator sender=map->find(profile);
 if(sender==map->end()){pending.state=0;pending.rva00516F3F();return;}
 UnicodeString nick(*(AsciiString *)((char *)&sender->second+4));
 UnicodeString text;
 text.format(TheGameText->fetchPtr("APT:BuddyInviteJoiningText"),nick.str());
 Rva00437F61(3,TheGameText->fetch("APT:BuddyInviteTitle"),text,Rva0023E8D8(Rva0051732A(
 Rva004F6986Member(bind(reinterpret_cast<FunctorMethod>(&AptOnline::rva005170B4),(FunctorTarget *)this)))));
}

// Native517CC9..517E9A: a buddy invite arrives; accept it into the pending
// slot and ask with the YesNo prompt (accept 0x5177EB, decline 0x5170B4).
void Rva00517048::rva00517CC9(const BuddyInviteGameInfo &info)
{
 if(!online)return;
 if(invite.state)return;
 _STL::map<int,int> *map=(_STL::map<int,int> *)TheGameSpyInfo->getBuddyMap();
 int profile=info.profile;_STL::map<int,int>::iterator sender=map->find(profile);
 if(sender==map->end())return;
 if(input&&!input->blocked())return;
 invite.rva00516F63(*(const Rva00516F3F *)&info);invite.state=1;
 UnicodeString nick(*(AsciiString *)((char *)&sender->second+4));
 UnicodeString text;
 if(invite.mode==1)text.format(TheGameText->fetchPtr("APT:BuddyInviteTextStrategic"),nick.str());
 else text.format(TheGameText->fetchPtr("APT:BuddyInviteTextOpenPlay"),nick.str());
 n0044BF40::Rva00437F61(2,TheGameText->fetch("APT:BuddyInviteTitle"),text,Rva0044BF40(Rva0044BA4E(
  Rva004F6986Member(bind(reinterpret_cast<FunctorMethod>(&Rva00517048::rva005177EB),(FunctorTarget *)this)),
  Rva004F6986Member(bind(reinterpret_cast<FunctorMethod>(&AptOnline::rva005170B4),(FunctorTarget *)this)))));
}
