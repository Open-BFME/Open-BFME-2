// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva000A8437@AudioFileCache@@QAEKXZ @0x000A8437 238B: Miles cache loader thread. Under the cache mutex it takes the next
// pending file by priority 2..0, makes its sample resident (rva000A7E9E when its count is 0), keeps a handle to it, pops the
// list entry, then reads it with readAudioFile (separate row, MilesAudioCache.cpp) and sleeps 1 ms until quit.
// Own TU: a second EH function inside MilesAudioCache.cpp renumbers its unwind funclet labels.
// Codegen: the count read in a named int local keeps the native compare-against-zero form.
#include <set>
#include <list>
#include "ascii_string.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class File {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28();
 virtual int size(); virtual void slot30(); virtual char *readEntireFile();
};
class FileSystem { public: File *openFile(const char *,int,int); };
extern FileSystem *TheFileSystem;
class MilesMutexGuard {
public:
 MilesMutexGuard(void *,int); ~MilesMutexGuard();
 bool rva00041037(int); bool rva00041055();
private: void *m_mutex; bool m_flag;
};
class Rva0010ECB5 {public: bool rva0010ECB5();};
class OpenAudioFile {
public:
 AsciiString m_name;
 char pad04[0x30];
 volatile int m_count;
 void setFileReady(int,int *,int,bool);
};
struct Rva000A7E9EInput;
class Rva000A7E9E {public: void freeUnusedSamples(); void rva000A7E9E(const Rva000A7E9EInput &);};
class Gen0002857E;
class AudioFileContainer {
public:
 AudioFileContainer(); AudioFileContainer(Gen0002857E *); ~AudioFileContainer();
private: Gen0002857E *m_target;
};
class Rva00691040Handle {
public: Rva00691040Handle &operator=(const Rva00691040Handle &);
private: Gen0002857E *m_target;
};
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

extern "C" __declspec(dllimport) int __stdcall AIL_WAV_info(const void *,int *);
extern "C" __declspec(dllimport) int __stdcall AIL_decompress_ADPCM(const int *,void **,unsigned int *);
class AudioFileCache {
public:
 void readAudioFile(OpenAudioFile *entry);
 unsigned long rva000A8437();
private:
 char pad00[0x14];
 _STL::list<int,_STL::allocator<int> > m_pending[3];
 char unusedTree20[12];
 _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > m_failed;
 unsigned int m_activeBytes, m_unusedBytes, m_budget;
 void *m_badHandle, *m_thread;
 bool m_quit;
 void *m_mutex;
};
unsigned long AudioFileCache::rva000A8437()
{
 while (!m_quit) {
  register OpenAudioFile *entry=0;
  AudioFileContainer keep;
  {
   MilesMutexGuard guard(m_mutex,1);
   if (guard.rva00041037(500)) {
    for (int priority=2; !entry && priority>=0; --priority) {
     _STL::list<int,_STL::allocator<int> > &pending = m_pending[priority];
     _STL::list<int,_STL::allocator<int> >::iterator it = pending.begin();
     if (it != pending.end()) {
      entry=(OpenAudioFile *)*it;
      int _z = (int)(entry->m_count);
      if (_z == 0) ((Rva000A7E9E *)this)->rva000A7E9E(*(const Rva000A7E9EInput *)entry);
      ((Rva00691040Handle &)keep)=(const Rva00691040Handle &)AudioFileContainer((Gen0002857E *)entry);
      pending.pop_front();
     }

    }
   }
  }
  if (entry) readAudioFile(entry);
  Sleep(1);
 }
 return 0;
}
