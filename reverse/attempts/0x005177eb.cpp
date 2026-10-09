// ?OnYesToInvite@AptOnlineShell@@QAEXXZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

class BuddyInfo {
public:
 int id; AsciiString name,email,countryCode;
 int status; UnicodeString statusText,locationText;
};
typedef _STL::map<int,BuddyInfo> BuddyInfoMap;
class GameSpyInfoInterface {
public:
#define SLOT(n) virtual void s##n();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
#undef SLOT
 virtual BuddyInfoMap *getBuddies();
};
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameTextInterface {
public:
#define SLOT(n) virtual void s##n();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
 virtual UnicodeString fetch(const char *,bool *exists=0);
 virtual void s16();
 virtual const UnicodeString *fetchForFormat(const char *,bool *exists=0);
};
extern GameTextInterface *TheGameText;
extern int g_Va00E04904;

struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding {
 FunctorBinding(FunctorMethod f,FunctorTarget *o):target(o),method(f){}
 FunctorTarget *target; unsigned unused; FunctorMethod method;
};
class Rva0057BC63FunctorHolder {
public:
 Rva0057BC63FunctorHolder(const FunctorBinding &);
 Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &r):m_ptr(r.m_ptr) {if(m_ptr)++m_ptr->references;}
 ~Rva0057BC63FunctorHolder() {if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
struct Rva0051732A {
 TargetRef00217D4C *m_ptr;
 __forceinline Rva0051732A(FunctorBinding binding) { rva0051732A(Rva0057BC63FunctorHolder(binding)); }
 Rva0051732A(const Rva0051732A &r):m_ptr(r.m_ptr) { if(m_ptr)++m_ptr->references; }
 ~Rva0051732A() { if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr); }
 Rva0051732A *rva0051732A(Rva0057BC63FunctorHolder);
};
struct Rva00517547 {
 TargetRef00217D4C *m_ptr;
 Rva00517547 *rva00517547(Rva0051732A);
};
class Rva0023E8D8 {
 TargetRef00217D4C *m_ptr;
public:
 __forceinline Rva0023E8D8(const Rva0051732A &r) { ((Rva00517547*)this)->rva00517547(r); }
 Rva0023E8D8(const Rva0023E8D8 &r):m_ptr(r.m_ptr) { if(m_ptr)++m_ptr->references; }
 ~Rva0023E8D8() { if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr); }
};
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0023E8D8);
struct Rva00516F3F {
 void rva00516F3F();
 int id,field04,field08; void *field0c,*field10; int mode14;
};
class GameWindow { public:virtual ~GameWindow(); private:unsigned char rest[0x218-4]; };
class Rva005248D0 { public:virtual ~Rva005248D0(); private:unsigned char rest[0x58-4]; };
class _bfme_AptGameWindow:public GameWindow,public Rva005248D0 {
public:virtual ~_bfme_AptGameWindow();
private:AsciiString filename270;
};
class AptOnline:public _bfme_AptGameWindow { public:void rva005170B4(); };
class AptOnlineShell {
public:
 void OnYesToInvite();
private:
 unsigned char prefix[0x298];
 struct Invite { Rva00516F3F info; int state; } invite;
};
void AptOnlineShell::OnYesToInvite()
{
 if(!g_Va00E04904)return;
 invite.state=invite.info.mode14==1?3:2;
 BuddyInfoMap *buddies=TheGameSpyInfo->getBuddies();
 int id=invite.info.id;
 BuddyInfoMap::iterator buddy=buddies->find(id);
 if(buddy==buddies->end()) {
  Invite *pending=&invite;
  pending->state=0;
  pending->info.rva00516F3F();
  return;
 }
 UnicodeString name(buddy->second.name);
 UnicodeString message;
 message.format(TheGameText->fetchForFormat("APT:BuddyInviteJoiningText"),name.str());
 Rva00437F61(3,TheGameText->fetch("APT:BuddyInviteTitle"),message,
  Rva0023E8D8(Rva0051732A(FunctorBinding(
   reinterpret_cast<FunctorMethod>(&AptOnline::rva005170B4),reinterpret_cast<FunctorTarget*>(this)))));
}
