// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Include
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
struct VideoNode {VideoNode *next;AsciiString name;Rva0010EDC2 *entry;};
struct AudioCacheCursor {
 struct{void *first,*second;}s;
 AudioCacheCursor(void*a,void*b){s.first=a;s.second=b;}
 AudioCacheCursor(const AudioCacheCursor &v){s.first=v.s.first;s.second=v.s.second;}
};
struct VideoPair { struct {void *first,*second;}s;
 __forceinline VideoPair(const VideoPair&v) {s.first=v.s.first;s.second=v.s.second;}
};
class Rva000427195 {
 void *unused;
 _STL::vector<VideoNode*> buckets;
 unsigned count;
public:AudioCacheCursor rva00427195();void rva003A37DC(VideoPair);
};
AudioCacheCursor Rva000427195::rva00427195() {
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
class Gen0002857E;
class AudioFileContainer {Gen0002857E *target;public:~AudioFileContainer();};
class Rva000A77B3 {public:void rva000A77B3();};
class Rva000A8A6C {public:void rva000A8A6C();};
class MilesMutexGuard {void *mutex;bool flag;public:MilesMutexGuard(void*,int);~MilesMutexGuard();};
class AudioFileCache:public Rva000A7BB5 {
 Rva00200667 lists14[3];
 Rva000A79CE unused20;
 _STL::set<AsciiString> failed2C;
 unsigned active38,unused3C,budget40;
 AudioFileContainer sentinel44;
 void *thread48;
 bool quit4C;
 void *mutex50;
public:~AudioFileCache();
};
typedef char CacheSize[sizeof(AudioFileCache)==0x54?1:-1];
AudioFileCache::~AudioFileCache() {
 ((Rva000A77B3*)this)->rva000A77B3();
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
