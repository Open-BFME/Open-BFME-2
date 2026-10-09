// ??0InProgressIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAE@PAV123@@Z
// partial score=0.9080120464351823 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);
struct DelegateDesc {
 template<class T,class M> DelegateDesc(T*object,M method):m_object(reinterpret_cast<AptDelegateTarget*>(object)),m_method(reinterpret_cast<AptDelegateMethod>(method)){}
 AptDelegateTarget *m_object; AptDelegateMethod m_method;
};
template<class T,class M> static __forceinline DelegateDesc MakeDelegate(T*object,M method) {DelegateDesc desc(object,method);return desc;}
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47&);~Rva00579E47();private:void *ptr;};
template<class T> class AptRef:public Rva00579E47 {public:AptRef(DelegateDesc d):Rva00579E47(d){}};
class AptCommandMap; class AptCustomRender; class AptCustomRenderAdder {public:void AddCustomRender(const AsciiString&,AptRef<AptCustomRender>);char pad[12];};
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);char unknown[12];};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*); const char *ptr; int len;};
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString:AsciiStringRef {AsciiStringRef m_second;};
struct AsciiStringPlusStringText:AsciiStringPlusString {operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_right=text;return result;}
struct Rva005EF5CA:AsciiStringPlusStringText {operator AsciiString();AsciiStringRef fourth;};
Rva005EF5CA operator+(const AsciiStringPlusStringText&,const AsciiString&);
class Rva005F6941 {public:Rva005F6941();~Rva005F6941();virtual void vslot10()=0;protected:void *at04;int at08,at0C,quantity,at14;bool hover;};
namespace StrategicHUD {
class BuildQueueDetailsMovieClip {public:class Impl;};
class BuildQueueDetailsMovieClip::Impl {public:class QueuedIconSlot;class InProgressIconSlot;char unknown00[4];unsigned level;AsciiString name;char unknown0C[8];AptCommandMapAdder commands;char unknown20[12];AptCustomRenderAdder renders;};
class BuildQueueDetailsMovieClip::Impl::QueuedIconSlot {public:void rva005F6AE8(void*);void rva005F6A98(void*);void rva005F6A90(void*);void rva005F6892(void*);void rva005F688B(void*);void rva005F6AA8(void*);void rva005F6AA0(void*);};
struct Coord2D;
class BuildQueueDetailsMovieClip::Impl::InProgressIconSlot:public Rva005F6941 {public:InProgressIconSlot(Impl*);void rva005F6899(const Coord2D*,const Coord2D*,void*,void*);void SetQuantityString(int);void SetProgressString(int,int);virtual void unknown1();private:Impl*owner;int total,remaining;bool turnsHover;};
BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::InProgressIconSlot(Impl*parent):owner(parent),total(0),remaining(0),turnsHover(false){
 AsciiString prefix;prefix.format("_level%u.",owner->level);
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotClicked",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F6AE8)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotRollOver",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F6A98)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotRollOut",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F6A90)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotTurnsRemainingRollOver",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F6892)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotTurnsRemainingRollOut",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F688B)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotTypeRollOver",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F6AA8)));
 owner->commands.AddCommandMap(prefix+owner->name+"_OnInProgressIconSlotTypeRollOut",AptRef<AptCommandMap>(MakeDelegate(this,&QueuedIconSlot::rva005F6AA0)));
 owner->renders.AddCustomRender(prefix+owner->name+"_ProgressOverlay",AptRef<AptCustomRender>(MakeDelegate(this,&InProgressIconSlot::rva005F6899)));
 SetQuantityString(quantity);SetProgressString(total,remaining);
}
}
