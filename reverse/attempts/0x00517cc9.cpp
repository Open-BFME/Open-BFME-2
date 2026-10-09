// ?rva00517CC9@Rva00517048@@QAEXABVBuddyInviteGameInfo@@@Z
// partial score=0.98 date=2026-10-09
// cl: /vmg /vmm /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native517CC9..517EA0 RET4, invite prompt. WB145D1B0 provides the debug
// sibling; its yes callback WB145D6E0 is AptOnlineShell::OnYesToInvite.
// Neutral receiver name preserves the unreconciled shell class spelling.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"
struct TargetRef00217D4C {void *vtbl;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void(FunctorTarget::*FunctorMethod)();
struct FunctorBinding {FunctorBinding(FunctorMethod m,FunctorTarget *t):target(t),method(m){} FunctorTarget *target;unsigned pad;FunctorMethod method;};
struct Rva0057BC63FunctorHolder {Rva0057BC63FunctorHolder(const FunctorBinding &);Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &o):ptr(o.ptr){if(ptr)++ptr->references;}TargetRef00217D4C *ptr;};
struct Rva004F6986Member : Rva0057BC63FunctorHolder {
 __forceinline Rva004F6986Member(const FunctorBinding &binding):Rva0057BC63FunctorHolder(binding){}
 __forceinline Rva004F6986Member(const Rva004F6986Member &other):Rva0057BC63FunctorHolder(other){}
 ~Rva004F6986Member(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
struct Rva004C5DD0Pair {TargetRef00217D4C *a,*b;};
class Rva004C5DD0 {public:Rva004C5DD0 &set(const Rva004C5DD0Pair *);TargetRef00217D4C *a,*b;};
struct Rva0044BA4E {
 Rva0044BA4E(Rva004F6986Member,Rva004F6986Member);~Rva0044BA4E();
 __forceinline Rva0044BA4E(const Rva0044BA4E &other){((Rva004C5DD0 *)this)->set((const Rva004C5DD0Pair *)&other);}
 TargetRef00217D4C *a,*b;
};
struct Rva0044BF40 {Rva0044BF40 *rva0044BF40(Rva0044BA4E);TargetRef00217D4C *ptr;};
struct Rva0051732A {TargetRef00217D4C *ptr;Rva0051732A *rva0051732A(TargetRef00217D4C *);~Rva0051732A(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}Rva0051732A(const Rva0051732A &o):ptr(o.ptr){if(ptr)++ptr->references;}Rva0051732A(){} };
struct Rva00517547 {Rva00517547 *rva00517547(Rva0051732A);TargetRef00217D4C *ptr;};
class Rva0023E8D8 {public:TargetRef00217D4C *ptr;
 Rva0023E8D8(const Rva0023E8D8 &o):ptr(o.ptr){if(ptr)++ptr->references;}
 __forceinline Rva0023E8D8(const Rva0044BA4E &pair){((Rva0044BF40 *)this)->rva0044BF40(pair);}
 __forceinline Rva0023E8D8(const Rva0051732A &single){((Rva00517547 *)this)->rva00517547(single);}
 ~Rva0023E8D8(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0023E8D8);
struct Rva00516F3F {
 int profile,word4,word8;AsciiString textC,text10;int mode;
 void rva00516F3F();Rva00516F3F *rva00516F63(const Rva00516F3F &);
};
class BuddyInviteGameInfo {public:int profile,word4,word8;AsciiString textC,text10;int mode;};
class InviteInput {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual bool blocked();};
struct Rva00517048 {
 char prefix[0x27c];bool online;char pad27d[0x290-0x27d];InviteInput *input;char pad294[4];
 Rva00516F3F invite;int inviteState;
 void rva00517CC9(const BuddyInviteGameInfo &);
 void rva005177EB();
};
class AptOnline {public:void rva005170B4();};
static __forceinline FunctorBinding bind(FunctorMethod method,FunctorTarget *target){FunctorBinding result(method,target);return result;}
class GameSpyInfoInterface {public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)
#undef V
 virtual _STL::map<int,int> *getBuddyMap();};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameTextInterface {public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)
 virtual UnicodeString fetch(const char *,bool *exists=0);V(16)virtual const UnicodeString *fetchFormat(const char *,bool *exists=0);
#undef V
};
extern GameTextInterface *TheGameText;
extern Rva00517048 *g_Va00A04904;
void Rva00517048::rva00517CC9(const BuddyInviteGameInfo &info)
{
 if(!online)return;
 if(inviteState)return;
 _STL::map<int,int> *map=TheGameSpyInfo->getBuddyMap();
 int profile=info.profile;_STL::map<int,int>::iterator sender=map->find(profile);
 if(sender==map->end())return;
 if(input&&!input->blocked())return;
 invite.rva00516F63(*(const Rva00516F3F *)&info);inviteState=1;
 UnicodeString nick(*(AsciiString *)((char *)&sender->second+4));
 UnicodeString text;
 if(invite.mode==1)text.format(TheGameText->fetchFormat("APT:BuddyInviteTextStrategic"),nick.str());
 else text.format(TheGameText->fetchFormat("APT:BuddyInviteTextOpenPlay"),nick.str());
 Rva00437F61(2,TheGameText->fetch("APT:BuddyInviteTitle"),text,Rva0023E8D8(Rva0044BA4E(
  Rva004F6986Member(bind(reinterpret_cast<FunctorMethod>(&Rva00517048::rva005177EB),(FunctorTarget *)this)),
  Rva004F6986Member(bind(reinterpret_cast<FunctorMethod>(&AptOnline::rva005170B4),(FunctorTarget *)this)))));
}
