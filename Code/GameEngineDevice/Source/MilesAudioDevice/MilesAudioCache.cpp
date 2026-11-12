// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <set>
#include <list>
#include "ascii_string.h"
// Keep this /G7 unit's STL helpers out of the link: every comparison and
// int construction is inlined here, and retail keeps one copy of each
// (_List_iterator_base::operator!= 0x006CFE40, the set<AsciiString>
// insert_unique 0x00057F2A rowed in stlport_rb_tree_hint_asciistring_set.cpp).
namespace _STL {
template <class T, class TraitsA, class TraitsB>
static inline bool operator!=(const _List_iterator<T, TraitsA>& a,
                              const _List_iterator<T, TraitsB>& b)
{ return a._M_node != b._M_node; }
template <class T, class TraitsA, class TraitsB>
static inline bool operator!=(const _Rb_tree_iterator<T, TraitsA>& a,
                              const _Rb_tree_iterator<T, TraitsB>& b)
{ return a._M_node != b._M_node; }
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
template <> pair<_Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::iterator, bool>
_Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::insert_unique(const AsciiString &);
}
#include "../../../GameEngine/Include/Common/File.h"
#include "../../../GameEngine/Include/Common/FileSystem.h"
extern FileSystem *TheFileSystem;
#include "../../Include/MilesAudioDevice/MilesMutexGuard.h"
class Rva0010ECB5 {public: bool rva0010ECB5();};
class OpenAudioFile {
public:
 AsciiString m_name;
 void setFileReady(int,int *,int,bool);
};
struct Rva000A7E9EInput;
class AudioFileCache;
struct Rva000A89E3Ready { virtual bool check(int); };
class Gen0002857E {
public:
 Gen0002857E(AudioFileCache *,const AsciiString &);
 char pad00[0x34];
 int m_count;
 char pad38[4];
 int m_priority;
 char pad40[4];
 Rva000A89E3Ready m_ready;
 char pad48[0xC];
};
class Rva0010ED3D {public: void rva0010ED3D(int);};
class Rva00691110Handle {public: Rva00691110Handle(const Rva00691110Handle &); private: void *target;};
#include "../../../GameEngine/Include/Common/AudioFileContainer.h"
class Rva00690FF0Handle {
public:
 // Built through the AudioFileContainer pointer ctor 0x000A8A1F, as retail calls it. A template
 // keeps this view's inline COMDAT off the out-of-line Rva00690FF0Handle(Gen0002857E *) that
 // Rva00690FF0Handle.cpp defines (an exclusive definition: link.exe would report the pair).
 template<class Target> Rva00690FF0Handle(Target *target) { ((AudioFileContainer *)this)->AudioFileContainer::AudioFileContainer(target); }
 Rva00690FF0Handle(const Rva00690FF0Handle &other) {
  ((Rva00691110Handle *)this)->Rva00691110Handle::Rva00691110Handle(*(const Rva00691110Handle *)&other);
 }
 ~Rva00690FF0Handle();
private: void *target;
};
struct AudioCacheFileNode { AudioCacheFileNode *m_next; AsciiString m_name; Gen0002857E *m_file; };
class Rva00056F61;
struct Rva0041534BIter {
 AudioCacheFileNode *m_node;
 Rva00056F61 *m_table;
 Rva0041534BIter(AudioCacheFileNode *audioCacheFileNode,Rva00056F61 *t) : m_node(audioCacheFileNode), m_table(t) {}
 Rva0041534BIter() {}
};
// Find returning an iterator over the AsciiString-keyed bucket table owned
// by Rva00056F61 (rowed find 0x00056F61): this plus key in, hidden-pointer
// out {node table}, ret 8. Other callers at 0x00223D02 (add ecx 0x48) and
// 0x002AE98B (add ecx 0x294) read node at out+0 and use payload at node+8;
// shape matches STLport hashtable find 0x00620DD0. The 0x56F61 lookup only
// hashes and compares existing bytes (callees 0x55041 -> 0x2BA61 and 0x69D6
// -> 0x6733 -> memcmp): no allocation, callbacks or C++ throws.
#include "../../../GameEngine/Include/GameClient/Rva00056F61.h"
// ?rva0041534B@Rva00056F61@@QAE?AURva0041534BIter@@PBVAsciiString@@@Z 0x0041534B 27B
// Inline (a selectany COMDAT, kept out of line) like the other units that
// compile this find (MilesAudioManagerRva00059EAE.cpp,
// ParticleSystemManagerRva001FCF11.cpp): an ordinary definition here made
// link.exe report their identical copies as duplicates.
__declspec(nothrow) __declspec(noinline) inline Rva0041534BIter Rva00056F61::rva0041534B(const AsciiString *key)
{
 return Rva0041534BIter((AudioCacheFileNode *)rva00056F61(key), this);
}
#include "../../../GameEngine/Include/GameLogic/Rva000427195.h"
class AudioFileCacheMap {
public:
 Rva0041534BIter find(const AsciiString &key) { return ((Rva00056F61 *)this)->rva0041534B(&key); }
};
extern "C" __declspec(dllimport) int __stdcall AIL_WAV_info(const void *,int *);
extern "C" __declspec(dllimport) int __stdcall AIL_decompress_ADPCM(const int *,void **,unsigned int *);
typedef _STL::list<int,_STL::allocator<int> > AudioFileCacheList;
class AudioFileCache {
public:
 void freeUnusedSamples();
 void eraseFromUnusedList(const Rva000A7E9EInput &);
 Rva00690FF0Handle requestFile(const AsciiString &filename,int priority);
 void readAudioFile(OpenAudioFile *entry);
private:
 char pad00[0x14];
 AudioFileCacheList m_lists[3];
 char pad20[0xC];
 _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > m_failed;
 unsigned int m_activeBytes, m_unusedBytes, m_budget;
 Rva00690FF0Handle m_emptyFile;
 void *m_thread;
 bool m_quit;
 void *m_mutex;
};
// Retail 0x000A7EFA,430B RET12; WorldBuilder 0x008E51A0 names
// AudioFileCache::requestFile (the by-name overload; the event overload
// 0x000A8241 calls it). Priority clamp 0..2, guard of mutex50, empty name
// returns the empty-file handle44, the name table find 0x0041534B, an existing
// entry's sample reload 0x000A7E9E, re-queue from its old priority list
// into the requested one, the priority setter 0x0010ED3D; else the failed-name
// set2C, a new 0x54 entry 0x0010ED4C, the name table slot 0x000A7B3C and the
// pending list. The find must be defined in this unit: cl then knows it keeps
// no pointer to the iterator return buffer and coalesces the buffer with the
// iterator local (retail's 0x18 frame).
Rva00690FF0Handle AudioFileCache::requestFile(const AsciiString &filename,int priority)
{
 if (priority < 0) priority = 0;
 else if (priority >= 3) priority = 2;
 MilesMutexGuard guard(m_mutex,0);
 if (((const StringBase<char> *)&filename)->isEmpty()) return m_emptyFile;
 Rva0041534BIter it; it = ((AudioFileCacheMap *)this)->find(filename);
 if (it.m_node) {
  Gen0002857E *file = it.m_node->m_file;
  if (file->m_count == 0) eraseFromUnusedList(*(const Rva000A7E9EInput *)file);
  if (!file->m_ready.check(0) && file->m_priority < priority) {
   AudioFileCacheList &list = m_lists[file->m_priority];
   AudioFileCacheList::iterator i = list.begin();
   bool done = false;
   while (!done && i != list.end()) {
    if ((Gen0002857E *)*i == file) {
     i = list.erase(i);
     m_lists[priority].push_back(*(int *)&file);
     done = true;
    } else ++i;
   }
  }
  ((Rva0010ED3D *)file)->rva0010ED3D(priority);
  return Rva00690FF0Handle(file);
 }
 if (m_failed.find(filename) != m_failed.end()) return m_emptyFile;
 Gen0002857E *file = new Gen0002857E(this,filename);
 Rva00690FF0Handle handle(file);
 *(Gen0002857E **)((Rva000427195 *)this)->rva000A7B3C(&filename) = file;
 m_lists[priority].push_back(*(int *)&file);
 ((Rva0010ED3D *)file)->rva0010ED3D(priority);
 return handle;
}
// Retail 0x000A82CA,365B; WorldBuilder names AudioFileCache::readAudioFile.
// Native filename field0, File size/readEntireAndClose slots2C/34,
// cache fields38/40/4C/50 and failed-name set2C establish the accessed ABI.
// Miles calls are imported APIs; info is the nine-word native WAV record.
// setFileReady and the whole131B eviction loop are separately byte-verified.
// ?readAudioFile@AudioFileCache@@QAEXPAVOpenAudioFile@@@Z 0x000A82CA 365B
void AudioFileCache::readAudioFile(OpenAudioFile *entry)
{
 File *file = TheFileSystem->openFile(entry->m_name.str(),0x41,0);
 bool failed;
 unsigned int size;
 char *data;
 if (!file) { failed = true; }
 else { size = file->size(); data = file->readEntireAndClose(); failed = false; }
 MilesMutexGuard guard(m_mutex,1);
 for (;;) {
  if (m_quit) return;
  if (!guard.rva00041037(500)) continue;
  if (failed) {
   ((Rva0010ECB5 *)entry)->rva0010ECB5();
   m_failed.insert(entry->m_name);
   guard.rva00041055();
   break;
  }
  int info[9];
  bool allocated;
  AIL_WAV_info(data,info);
  if (info[0]==17) {
   unsigned int decompressedSize; void *decompressed;
   AIL_decompress_ADPCM(info,&decompressed,&decompressedSize);
   size=decompressedSize; allocated=true;
   delete[] data;
   data=(char *)decompressed;
   AIL_WAV_info(data,info);
  } else if (info[0]==1) { allocated=false; }
  else {
   ((Rva0010ECB5 *)entry)->rva0010ECB5();
   m_failed.insert(entry->m_name);
   guard.rva00041055();
   delete[] data;
   break;
  }
  entry->setFileReady((int)data,info,size,allocated);
  m_activeBytes += size;
  if (m_activeBytes > m_budget) freeUnusedSamples();
  break;
 }
}
