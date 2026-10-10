// Rva005D19F8Child::Rva005D19F8Child, retail 0x005D18E2 (278 bytes): the strategic region
// award dialog's child. It loads StrategicRegionAward.swf with a delegate to the dialog's
// OnMovieClipLoaded, copies the award source's player list, finds the local player in it and
// rotates it to the front. Names are address-derived (original owner/child spellings unknown).
// The explicit specialization declaration of std::find<int*,int> that earlier banks carried is
// dropped: with it cl cannot see the STLport body and schedules the player vector differently.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "ascii_string.h"
class Rva005D19F8;
class ModuleData;
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
namespace StrategicInGameUI {class RegionAwardDialog {public:class Impl;};}
class __single_inheritance StrategicInGameUI::RegionAwardDialog::Impl {public:void OnMovieClipLoaded(int,const AsciiString&);};
typedef void(StrategicInGameUI::RegionAwardDialog::Impl::*AwardLoadMethod)(int,const AsciiString&);
struct DelegateDesc {DelegateDesc(void*o,AwardLoadMethod m):object(o),method(m){}void*object;AwardLoadMethod method;};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);void*ptr;};
struct TreeHintRef00217D4C:public Rva00579E47 {TreeHintRef00217D4C(DelegateDesc d):Rva00579E47(d){}~TreeHintRef00217D4C(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class Rva0057C394 {public:void rva0057C394(const AsciiString&,const TreeHintRef00217D4C&);};
struct AwardSource {int unknown0,unknown4;_STL::vector<const ModuleData*>players;};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
struct AwardWorld {char unknown[0x98];const ModuleData*localPlayer;};
namespace _STL {template<> int*rotate<int*>(int*,int*,int*);}
class Rva000AD6F4 {public:Rva000AD6F4():ptr(0){}~Rva000AD6F4();void*ptr;};
class Rva005D19F8Child {public:Rva005D19F8Child(Rva005D19F8*,int,int);Rva005D19F8*owner;int root,source;Rva000AD6F4 movie;_STL::vector<const ModuleData*>players;};
Rva005D19F8Child::Rva005D19F8Child(Rva005D19F8*o,int r,int a):owner(o),root(r),source(a) {
 ((Rva0057C394*)root)->rva0057C394(AsciiString("StrategicRegionAward.swf"),TreeHintRef00217D4C(DelegateDesc(this,&StrategicInGameUI::RegionAwardDialog::Impl::OnMovieClipLoaded)));
 const AwardSource*data=(AwardSource*)source;
 int count=data->players.size();
 players.reserve(count);
 for(int i=0;i<count;i++){const ModuleData*p=((AwardSource*)source)->players[i];players.push_back(p);}
 const ModuleData*local=((AwardWorld*)TheLivingWorldLogic)->localPlayer;
 const ModuleData**first=players.begin();
 _ReadWriteBarrier();const ModuleData**found=(const ModuleData**)_STL::find((int*)first,(int*)players.end(),(const int&)local);
 _STL::rotate((int*)first,(int*)found,(int*)(found+1));
}
