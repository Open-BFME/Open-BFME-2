// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// QueuedIconSlot constructor (retail 0x005F7B25, 1020B), slot 7 of the
// BuildQueueDetails movie clip's queued icon slots; the sibling of the
// InProgressIconSlot constructor 0x005F775E (StrategicHUDBuildQueueInProgressIconSlotCtor.cpp).
// Native 5F7B25..5F7F21 (RET 8), WB 162EB00 names the queued constructor.
// Codegen: AptRef takes its DelegateDesc BY VALUE (as in the 5F775E TU); a
// const-reference parameter keeps cl's temp slots in a different order and left
// the body at 0.9504. The prefix/number AsciiStrings live in the dead formal
// homes [ebp+0xC]/[ebp+8], which cl only hands to block-scoped locals, so the
// whole body sits in a block. The fourth concat operand goes through the rowed
// 0x005EEFA9 operator+ and 0x005EF607 conversion.
#include "ascii_string.h"
class AptCommandTarget {};
struct DelegateDesc {
 template<class T> DelegateDesc(T*o,void(T::*m)(void*)):object((AptCommandTarget*)o),method(reinterpret_cast<void(AptCommandTarget::*)(void*)>(m)){}
 AptCommandTarget *object;void(AptCommandTarget::*method)(void*);
};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47&);void*ptr;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
// Link (AptRef lineage fork): the wrapper dtor copy (digest e67a72158686)
// lost to the majority inline-release copy (361dbf55f6ea, = rowed
// ??1Rva005F8F96 at 0x005F8F96 via the 0x7DEEF pin). Trivial base (no declared
// dtor; copy ctor kept declared) + inline release dtor emit retail's bytes.
template<class T> class AptRef:public Rva00579E47 {public:AptRef(DelegateDesc desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMap;
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);char unknown[12];};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*); const char *ptr; int len;};
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString:AsciiStringRef {AsciiStringRef m_second;};
struct AsciiStringPlusStringText:AsciiStringPlusString {Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_right=text;return result;}
struct Rva005EF5CA:AsciiStringPlusStringText {operator AsciiString();AsciiStringRef fourth;};
Rva005EF5CA operator+(const AsciiStringPlusStringText&,const AsciiString&);
class Rva005F69F5 {public:Rva005F69F5();~Rva005F69F5();virtual void vslot10()=0;protected:void *at04;int at08,at0C,quantity,at14;bool hover;};
namespace StrategicHUD {
class BuildQueueDetailsMovieClip {public:class Impl;};
class BuildQueueDetailsMovieClip::Impl {public:class QueuedIconSlot;char unknown00[4];unsigned level;AsciiString name;char unknown0C[8];AptCommandMapAdder commands;};
class BuildQueueDetailsMovieClip::Impl::QueuedIconSlot:public Rva005F69F5 {
public:
 QueuedIconSlot(Impl*,int);
 void rva005F6AE8(void*);void rva005F6A98(void*);void rva005F6A90(void*);void rva005F6892(void*);void rva005F688B(void*);void rva005F6AA8(void*);void rva005F6AA0(void*);
 void SetQuantityString(int);void SetNumTurnsString(int);
 virtual void unknown1();
private: Impl *owner;int index,turns;bool turnsHover;
};
BuildQueueDetailsMovieClip::Impl::QueuedIconSlot::QueuedIconSlot(Impl*parent,int slot):owner(parent),index(slot),turns(0),turnsHover(false){
 {AsciiString prefix;prefix.format("_level%u.",owner->level);
 AsciiString number;number.format("%d",index);
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotClicked"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F6AE8)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotRollOver"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F6A98)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotRollOut"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F6A90)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotTurnsRemainingRollOver"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F6892)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotTurnsRemainingRollOut"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F688B)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotTypeRollOver"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F6AA8)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnQueuedIconSlotTypeRollOut"+number,AptRef<AptCommandMap>(DelegateDesc(this,&QueuedIconSlot::rva005F6AA0)));
 SetQuantityString(quantity);SetNumTurnsString(turns);}
}
}
