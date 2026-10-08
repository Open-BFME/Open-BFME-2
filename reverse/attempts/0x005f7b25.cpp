// ??0QueuedIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAE@PAV123@H@Z
// partial score=0.88 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct AsciiStringRef { const AsciiString *m_string; };
struct AsciiStringPlusString : AsciiStringRef { AsciiStringRef m_second; };
struct AsciiStringPlusStringText : AsciiStringPlusString { const char *text; int length; };
AsciiStringPlusStringText __cdecl operator+(const AsciiStringPlusString&,const char*);
static __forceinline AsciiStringPlusString operator+(const AsciiString &a,const AsciiString &b) {
 AsciiStringPlusString r; r.m_string=&a; r.m_second.m_string=&b; return r;
}
struct Rva005EEFA9Src { int word[4]; };
struct Rva005EEFA9Dst { int word[5]; };
Rva005EEFA9Dst *__cdecl Rva005EEFA9Copy(Rva005EEFA9Dst*,const Rva005EEFA9Src*,int);
struct Rva005EF5CA : AsciiStringPlusStringText {
 AsciiStringRef fourth;
 __forceinline Rva005EF5CA(const AsciiStringPlusStringText &left,const AsciiString &right) {
  Rva005EEFA9Copy((Rva005EEFA9Dst*)this,(const Rva005EEFA9Src*)&left,(int)&right);
 }
 operator AsciiString();
};
struct DelegateDesc { void *object; void *method; };
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);};
class AptCommandMap;
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef {
public:
 AptRef(const DelegateDesc &desc) { ((Rva00579E47*)this)->Rva00579E47::Rva00579E47(desc); }
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}
private:T *ptr;
};
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);char storage[12];};
class Rva005F69F5 {
public:Rva005F69F5();virtual ~Rva005F69F5();
 void *listener; const void *portrait,*typeImage; int quantity,state; bool hovered;
};
namespace StrategicHUD { class BuildQueueDetailsMovieClip {public:class Impl;}; }
class StrategicHUD::BuildQueueDetailsMovieClip::Impl {
public:char prefix[4];unsigned int level;AsciiString name;char gap[8];AptCommandMapAdder maps;
 class QueuedIconSlot;
};
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot : public Rva005F69F5 {
public:
 QueuedIconSlot(Impl*,int);
 virtual ~QueuedIconSlot();
 void rva005F688B(void*);void rva005F6892(void*);
 void rva005F6A90(void*);void rva005F6A98(void*);
 void rva005F6AA0(void*);void rva005F6AA8(void*);void rva005F6AE8(void*);
 void SetQuantityString(int);void SetNumTurnsString(int);
private:Impl *owner;int index,turns;bool turnsHover;
};
#define QUEUED_BIND(SUFFIX,METHOD) \
 AsciiStringPlusStringText METHOD##Name = prefix+owner->name+SUFFIX; { \
 union {void (QueuedIconSlot::*member)(void*);void *address;} METHOD##Callback; \
 METHOD##Callback.member=&QueuedIconSlot::METHOD; DelegateDesc METHOD##Desc={this,METHOD##Callback.address}; \
 owner->maps.AddCommandMap(Rva005EF5CA(METHOD##Name,number),METHOD##Desc); }
StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::QueuedIconSlot(Impl *parent,int slot)
 : owner(parent),index(slot),turns(0),turnsHover(false) {
 AsciiString prefix;prefix.format("_level%u.",owner->level);
 AsciiString number;number.format("%d",index);
 QUEUED_BIND("_OnQueuedIconSlotClicked",rva005F6AE8);
 QUEUED_BIND("_OnQueuedIconSlotRollOver",rva005F6A98);
 QUEUED_BIND("_OnQueuedIconSlotRollOut",rva005F6A90);
 QUEUED_BIND("_OnQueuedIconSlotTurnsRemainingRollOver",rva005F6892);
 QUEUED_BIND("_OnQueuedIconSlotTurnsRemainingRollOut",rva005F688B);
 QUEUED_BIND("_OnQueuedIconSlotTypeRollOver",rva005F6AA8);
 QUEUED_BIND("_OnQueuedIconSlotTypeRollOut",rva005F6AA0);
 SetQuantityString(quantity);SetNumTurnsString(turns);
}


