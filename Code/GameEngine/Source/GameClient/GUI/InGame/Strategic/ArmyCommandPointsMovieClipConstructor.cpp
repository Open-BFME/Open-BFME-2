// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native5EF92D..5EFB05 RET12: constructor472B of the canonical
// RegionDetailsArmiesMovieClip::Impl. WB1616F10 has the same three callback
// strings and SetArmyNameString/SetCommandPointsString chain; the already
// named Show/Hide/Update bodies independently prove the caches and flags.
// Constructor stores prove color08, command-map0C and extern-list18 in the
// formerly opaque shared span. The existing93B destructor proves ownership.
// The existing RegistryAsciiPath source guides the string-node construction;
// the callback descriptor is the target-proven two-word SI binding.
// Real vector<Rva005EFD53Element> supplies the existing four-byte counted
// handle array; range-worker5EF5EF accepts an ABI view of the same handles.
// /EHs preserves native63B vector destruction, including allocator cleanup
// when range destruction throws. The three library folds recover zero bytes.
#include "ascii_string.h"
#include "unicode_string.h"
#include <stl/_alloc.h>
#include <vector>
#include "../../../../Common/RegionDetailsArmiesClipImplView.h"
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString : AsciiStringRef {AsciiStringRef m_second;};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*);const char *text;int length;};
struct AsciiStringPlusStringText : AsciiStringPlusString {operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b) {AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString&a,const char*b) {Rva000B3F84Pair p;p.init(b);AsciiStringPlusStringText r;static_cast<AsciiStringPlusString&>(r)=a;r.m_right=p;return r;}
class AptCommandTarget {};
struct DelegateDesc {
 template<class T> DelegateDesc(T*o,void(T::*m)(const char*)):object((AptCommandTarget*)o),method(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(m)){}
 template<class T> DelegateDesc(T*o,void(T::*m)(int,char*,bool)):object((AptCommandTarget*)o),method(reinterpret_cast<void(AptCommandTarget::*)(const char*)>(m)){}
 AptCommandTarget *object;void(AptCommandTarget::*method)(const char*);
};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);void*ptr;};
class AptCommandMap;class AptExternHandler;struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(const DelegateDesc&desc):Rva00579E47(desc){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);__forceinline void AddCommandMapDelegate(const AsciiString&n,DelegateDesc d){AddCommandMap(n,d);}char storage[12];};
class AptExternHandlerAdder {public:__declspec(noinline) AptExternHandlerAdder();~AptExternHandlerAdder();void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);__forceinline void AddExternHandlerDelegate(const AsciiString&n,DelegateDesc d){AddExternHandler(n,0,d);}private:_STL::vector<AsciiString>names;};


struct Rva005EF02FOuter;struct Rva005EF096Outer;
namespace StrategicHUD {void SetArmyNameString(int,Rva005EF02FOuter*,const UnicodeString&);void SetCommandPointsString(int,Rva005EF096Outer*,int,int);}
StrategicHUD::RegionDetailsArmiesMovieClip::Impl::Impl(int l,const AsciiString&n,unsigned c):m_level(l),m_name(n),m_color(c),m_a(0),m_b(0),m_armyNameShown(false),m_shown(false),m_3E(false){
 AsciiString prefix;prefix.format("_level%u.",m_level);
 reinterpret_cast<AptCommandMapAdder*>(&m_commandMaps)->AddCommandMapDelegate(prefix+m_name+"_OnRollOverCommandPoints",DelegateDesc(this,&Impl::OnRollOverCommandPoints));
 reinterpret_cast<AptCommandMapAdder*>(&m_commandMaps)->AddCommandMapDelegate(prefix+m_name+"_OnRollOutCommandPoints",DelegateDesc(this,&Impl::OnRollOutCommandPoints));
 reinterpret_cast<AptExternHandlerAdder*>(&m_externHandlers)->AddExternHandlerDelegate(prefix+m_name+"_PlayerColor",DelegateDesc(this,&Impl::PlayerColor));
 StrategicHUD::SetArmyNameString(m_level,reinterpret_cast<Rva005EF02FOuter*>(&m_name),m_cached30);
 StrategicHUD::SetCommandPointsString(m_level,reinterpret_cast<Rva005EF096Outer*>(&m_name),m_a,m_b);
}



struct Rva005F0647;
void __cdecl Rva005EF5EFClear(Rva005F0647*,Rva005F0647*);
namespace _STL {template<> vector<Rva005EFD53Element,allocator<Rva005EFD53Element> >::~vector(){Rva005EF5EFClear(reinterpret_cast<Rva005F0647*>(_M_start),reinterpret_cast<Rva005F0647*>(_M_finish));}}
StrategicHUD::RegionDetailsArmiesMovieClip::Impl::~Impl(){}
