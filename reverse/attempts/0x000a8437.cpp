// ?rva000A8437@AudioFileCache@@QAEKXZ
// partial score=0.983193277310924 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <set>
#include <list>
#include "ascii_string.h"
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
void AudioFileCache::readAudioFile(OpenAudioFile *entry)
{
 File *file = TheFileSystem->openFile(entry->m_name.str(),0x41,0);
 bool failed;
 unsigned int size;
 char *data;
 if (!file) { failed = true; }
 else { size = file->size(); data = file->readEntireFile(); failed = false; }
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
  if (m_activeBytes > m_budget) ((Rva000A7E9E *)this)->freeUnusedSamples();
  break;
 }
}

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
      if (entry->m_count==0) ((Rva000A7E9E *)this)->rva000A7E9E(*(const Rva000A7E9EInput *)entry);
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
