// cl: /O1 /G7 /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// BFME 1 donor f98983a7d; retail startThread allocates 0x4B0 bytes.
// Native table C1989C identifies PeerThreadClass; teardown fixes its layout.
// Unnamed fields and payloads retain their target-supported storage views.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <string>
#include <map>
#include <string.h>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> _Rb_tree<basic_string<char, char_traits<char>, allocator<char> >, pair<basic_string<char, char_traits<char>, allocator<char> > const, int>, _Select1st<pair<basic_string<char, char_traits<char>, allocator<char> > const, int> >, less<basic_string<char, char_traits<char>, allocator<char> > >, allocator<pair<basic_string<char, char_traits<char>, allocator<char> > const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_terminate_string(); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::~basic_string(); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBHH@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_base<pair<int const ,int>,allocator<pair<int const ,int> > >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@_STL@@@_STL@@QBEXPAU?$_Rb_t:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<_Rb_tree_node<pair<int const ,int> > >::deallocate(_Rb_tree_node<pair<int const ,int> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t) const; }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
class MutexClass;
#include "../../../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"
struct BfmeOpaqueOwnedRecord492{BfmeOpaqueOwnedRecord492();~BfmeOpaqueOwnedRecord492();char bytes[492];};
typedef std::map<int, int> WorkerMap;
namespace _STL {template<> map<int,int>::map();template<> map<string,int>::map();}
class Rva00388EAE:public WorkerMap{public:~Rva00388EAE();void rva00389129();};
class PeerThreadClass:public ThreadClass{public:PeerThreadClass(MutexClass*);virtual ~PeerThreadClass();virtual void Thread_Function();
 bool isConnecting,isConnected;char pad52[2];std::string loginName,originalName,password,email;
 int profileID,groupRoomID;bool sawComplete;char pad8d[3];int unknown90;bool unknown94;char pad95[3];
 std::map<std::string,int> groupStats,stagingStats;
 bool isHosting,hasPassword;char padb2[2];std::string mapName;int unknownC0;std::string openStaging,names[8];
 int crcWords[4],unknown140,unknown144,otherWords[4],unknown158;bool useStats;char pad15d[3];std::string ping,ladderIP;unsigned short ladderPort;char pad17a[2];
 int wins[8],profiles[8],unknownPlayers[8],colors[8],factions[8],losses[8];int numPlayers,maxPlayers,numObservers,unknown248[10],unknown270,nextServer;
 Rva00388EAE servers;std::wstring serverName;int roomID,qmStatus;BfmeOpaqueOwnedRecord492 record;
 bool roomJoined;char pad485[3];void*peer;bool sawEnd,sawBot;char pad48e[2];std::string botName;
 bool unknown49c;char pad49d[3];int unknown4a0,unknown4a4;bool unknown4a8;char pad4a9[3];MutexClass*lock;
};
typedef char WorkerExtent[sizeof(PeerThreadClass)==0x4b0?1:-1];
PeerThreadClass::PeerThreadClass(MutexClass*p):ThreadClass(0),lock(p){
 hasPassword=false;useStats=false;roomJoined=false;
 memset(crcWords,0,sizeof crcWords);unknown144=0;unknown140=0;memset(otherWords,0,sizeof otherWords);
 unknown158=0;ladderPort=0;roomID=0;numObservers=0;numPlayers=1;maxPlayers=8;peer=0;
 sawEnd=sawBot=false;sawComplete=false;qmStatus=0;isConnecting=isConnected=false;unknown90=0;groupRoomID=profileID=0;
 nextServer=1;servers.rva00389129();ping="";mapName="";ladderIP="";isHosting=false;unknownC0=0;openStaging="openstaging";
 for(int i=0;i<8;++i){names[i]="";colors[i]=0;factions[i]=0;losses[i]=0;profiles[i]=0;unknownPlayers[i]=0;wins[i]=0;}
 unknown49c=false;unknown4a0=0;unknown4a4=0;unknown4a8=false;memset(unknown248,0,sizeof unknown248);unknown270=0;unknown94=false;
}

// The empty map constructor call reads 0x0033C432 from retail, the shared 25-byte tree ctor whose
// canonical row is the map<int,void*> one. Retail's derived destructor (0x0038ADE2) finishes by
// calling ThreadClass::~ThreadClass (0x00610480) directly, so the intermediate thread object has
// no destructor of its own there; bind it to the base's.
