// cl: /O1 /G7 /arch:SSE /MD /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Include
// NativeA7CF3..A7DCE complete219B destructor; WB8E4B30 and ZH
// AudioFileCache teardown provide identity and semantic source lead.
// BFME2 closes its worker, releases sentinel44 under guard of mutex50,
// repeatedly deletes first open-file entry and erases its node, then
// destroys four member groups and base hash. All offsets/cleanup calls
// below are target facts; original unused-tree/list payload types unknown.
// stlport
#include <set>
#include <vector>
#include "ascii_string.h"
#include "Common/Rva0010EDC2Resource.h"

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}
struct VideoNode {VideoNode *next;AsciiString name;Rva0010EDC2 *entry;};
struct AudioCacheCursor {
 struct{void *first,*second;}s;
 AudioCacheCursor(void*a,void*b){s.first=a;s.second=b;}
 AudioCacheCursor(const AudioCacheCursor &audioCacheCursor){s.first=audioCacheCursor.s.first;s.second=audioCacheCursor.s.second;}
};
struct VideoPair { struct {void *first,*second;}s;
 __forceinline VideoPair(const VideoPair&videoPair) {s.first=videoPair.s.first;s.second=videoPair.s.second;}
};
class Rva000427195 {
 void *unused;
 _STL::vector<VideoNode*> buckets;
 unsigned count;
public:AudioCacheCursor rva00427195();void rva003A37DC(VideoPair);
};
// Other retail-exact providers emit this helper as an inline COMDAT.
// Keep its call and whole body while allowing those identical copies to fold.
__declspec(noinline) inline AudioCacheCursor Rva000427195::rva00427195() {
 for(unsigned n=0;n<buckets.size();++n)
  if(buckets[n])return AudioCacheCursor(buckets[n],this);
 return AudioCacheCursor(0,this);
}
class Rva000A7BB5 {
 void *unused;
 void *buckets[3];
protected:unsigned count;
public:~Rva000A7BB5();
};
class Rva00200667 {void *header;public:~Rva00200667();};
class Rva000A79CE {void *header[3];public:~Rva000A79CE();};
// Native five-byte entries A7CE9/A7CEE forward the same receiver to the
// rowed hash/tree base destructors. These zero-storage derived ABI views
// preserve the parent-proven20B/12B widths and the native EH entry calls.
// Original container specializations and inheritance remain unproven.
class Rva000A7CE9:public Rva000A7BB5 {public:~Rva000A7CE9(){}};
class Rva000A7CEE:public Rva000A79CE {public:~Rva000A7CEE(){}};
typedef char AudioHashLifetimeSize[sizeof(Rva000A7CE9)==0x14?1:-1];
typedef char AudioTreeLifetimeSize[sizeof(Rva000A7CEE)==0x0c?1:-1];
class Gen0002857E;
#include "../../../GameEngine/Include/Common/AudioFileContainer.h"
class Rva000A8A6C {public:void rva000A8A6C();};
#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"
class AudioFileCache:public Rva000A7CE9 {
 Rva00200667 lists14[3];
 Rva000A7CEE unused20;
 _STL::set<AsciiString> failed2C;
 unsigned active38,unused3C,budget40;
 AudioFileContainer sentinel44;
 void *thread48;
 bool quit4C;
 void *mutex50;
public:~AudioFileCache();
 void rva000A77B3();
};
typedef char CacheSize[sizeof(AudioFileCache)==0x54?1:-1];
AudioFileCache::~AudioFileCache() {
 rva000A77B3();
 {
  MilesMutexGuard guard(mutex50,0);
  ((Rva000A8A6C*)&sentinel44)->rva000A8A6C();
  while(count){
   AudioCacheCursor it=((Rva000427195*)this)->rva00427195();
   delete ((VideoNode*)it.s.first)->entry;
   ((Rva000427195*)this)->rva003A37DC(reinterpret_cast<const VideoPair&>(it));
  }
 }
}
