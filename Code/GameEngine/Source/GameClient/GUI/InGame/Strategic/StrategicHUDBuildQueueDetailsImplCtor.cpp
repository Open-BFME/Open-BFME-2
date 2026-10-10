// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /ICode/GameEngine/Source/Common
// Native5F7F21..5F830A RET20 is1001B. WB162FDE0 names
// StrategicHUD::BuildQueueDetailsMovieClip::Impl::Impl and the source file.
// Existing factory5F830A allocates68B and owns the established neutral
// Rva005F830AHeap constructor linker key; preserve its five borrowed ABI args.
// Retail construction and EH unwind establish owner0/level4/name8/titleC,
// image name list20/custom render list2C, progress pointer38, seven queued
// pointers3C, wide string58, sentinels5C/60, flags64..67. The rowed5F75C9
// destructor independently agrees with every owning member. Callback names
// remain the existing neutral addresses; their original argument is unknown.
// Reference-first: no applicable ZH/BF1 StrategicHUD implementation at575ba2b04;
// matched ArmyMember/ArmyCommandPoints/Checklist constructors guide counted
// strings, name lists and single-inheritance functor descriptors. Retail
// bytes and native unwind data prove the target-specific layout/lifetimes.
// Allocation can throw: throw() dropped native states4/8. Return a binding
// before constructing the counted argument to load its code pointer inEAX;
// direct explicit AptRef adds a copy/release, direct binding saves three bytes.
// Array callback2A79A5 is the4B default-argument constructor closure;
// the constructor argument defaults to null, letting MSVC emit the void-return
// closure used by its array iterator. The original generic type is unknown.
// No data addresses or lifted code.
#include "ascii_string.h"
#include "unicode_string.h"
void* __cdecl operator new(unsigned int);
class AptCommandTarget {};
struct DelegateDesc {template<class T> DelegateDesc(T*o,void(T::*m)(void*)):object((AptCommandTarget*)o),method(reinterpret_cast<void(AptCommandTarget::*)(void*)>(m)){} AptCommandTarget*object;void(AptCommandTarget::*method)(void*);};
class Rva00579E47{public:Rva00579E47(const DelegateDesc&);void*ptr;};
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class AptCommandMap;template<class T>class AptRef:public Rva00579E47{public:AptRef(const DelegateDesc&d):Rva00579E47(d){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMapAdder{public:AptCommandMapAdder();~AptCommandMapAdder();void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);char bytes[12];};
class Rva00524265{public:Rva00524265();~Rva00524265();char bytes[12];};
class Rva005242D7{public:Rva005242D7();~Rva005242D7();char bytes[12];};
struct AsciiStringRef{const AsciiString*m_string;};struct AsciiStringPlusString:AsciiStringRef{AsciiStringRef m_second;};
class Rva000B3F84Pair{public:Rva000B3F84Pair(){}Rva000B3F84Pair*init(const char*);const char*m_ptr;int m_len;};
struct AsciiStringPlusStringText:AsciiStringPlusString{operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString&a,const char*b){Rva000B3F84Pair p;p.init(b);AsciiStringPlusStringText r;static_cast<AsciiStringPlusString&>(r)=a;r.m_right=p;return r;}
struct Rva005F17C6S12{int m[3];};struct Rva005D2F96S16{int m[4];};struct Rva005F17C6S16:Rva005D2F96S16{};
class Rva005F1D06{public:AsciiString rva005F1D47();int m[6];};struct Rva005D2F96S24:Rva005F1D06{};
struct Rva002226E5TextPlusString:Rva005F17C6S12{};
Rva002226E5TextPlusString operator+(const char*,const AsciiString&);
Rva005F17C6S16 Rva005F17C6Build(const Rva005F17C6S12&,int);
Rva005D2F96S24 Rva005D2F96Build(const Rva005D2F96S16&,const char*);
class BfmeAptWindowManager{public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};extern BfmeAptWindowManager*g_bfmeAptWindowManager;
namespace StrategicHUD{class BuildQueueDetailsMovieClip{public:class Impl{public:class QueuedIconSlot;class InProgressIconSlot;void rva005F68FE(void*);void rva005F6916(void*);void rva005F691D(void*);};};}
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot{public:QueuedIconSlot(Impl*,int);char bytes[0x2c];};
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot{public:InProgressIconSlot(Impl*);char bytes[0x2c];};
struct Rva005F74BA{Rva005F74BA(void*p=0):ptr(p){}~Rva005F74BA();void*ptr;};

class Rva005F74A0{public:Rva005F74A0(StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot*p):ptr(p){}void clear();__forceinline ~Rva005F74A0(){clear();}void*ptr;};
class Rva005F74D4{public:void rva005F74D4(StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot*);};
class Rva005F830AHeap{public:Rva005F830AHeap(void*,void*,void*,void*,void*);void*owner;int level;AsciiString name;UnicodeString title;void*word10;AptCommandMapAdder maps;Rva005242D7 images;Rva00524265 renderers;Rva005F74A0 progress;Rva005F74BA queued[7];UnicodeString ptr58;int word5C,word60;bool f64,f65,f66,f67;};
template<class T>static __forceinline DelegateDesc MakeBinding(T*o,void(T::*m)(void*)){DelegateDesc d(o,m);return d;}
#define BIND(TEXT,METHOD) {const AsciiString&n=prefix+name+TEXT;maps.AddCommandMap(n,MakeBinding((StrategicHUD::BuildQueueDetailsMovieClip::Impl*)this,&StrategicHUD::BuildQueueDetailsMovieClip::Impl::METHOD));}
#define TEXT(KEY,VALUE) {const AsciiString&n=Rva005D2F96Build(Rva005F17C6Build("APT:"+prefix,(int)&name),KEY).rva005F1D47();g_bfmeAptWindowManager->bfmeSetText(n,VALUE,false);}
Rva005F830AHeap::Rva005F830AHeap(void*o,void*l,void*n,void*t,void*w):owner(o),level((int)l),name(*(AsciiString*)n),title(*(UnicodeString*)t),word10(w),progress(new StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot((StrategicHUD::BuildQueueDetailsMovieClip::Impl*)this)),word5C(-1),word60(-1),f64(false),f65(false),f66(false),f67(false){
for(int i=0;i<7;++i)((Rva005F74D4*)&queued[i])->rva005F74D4(new StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot((StrategicHUD::BuildQueueDetailsMovieClip::Impl*)this,i));
AsciiString prefix;prefix.format("_level%u.",level);
TEXT("_BuildingName",title);TEXT("_UnitName",UnicodeString::TheEmptyString);TEXT("_BuildTime",UnicodeString::TheEmptyString);TEXT("_CommandPoints",UnicodeString::TheEmptyString);
BIND("_OnBackButtonClicked",rva005F68FE);BIND("_OnBackButtonRollOver",rva005F6916);BIND("_OnBackButtonRollOut",rva005F691D);
}
