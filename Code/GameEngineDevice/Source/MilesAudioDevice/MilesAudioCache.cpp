// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <set>
#include "ascii_string.h"
class File {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1C(); virtual void slot20();
 virtual void slot24(); virtual void slot28();
 virtual int size(); virtual void slot30(); virtual char *readEntireAndClose();
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
 void setFileReady(int,int *,int,bool);
};
class Rva000A7E9E {public: void freeUnusedSamples();};
extern "C" __declspec(dllimport) int __stdcall AIL_WAV_info(const void *,int *);
extern "C" __declspec(dllimport) int __stdcall AIL_decompress_ADPCM(const int *,void **,unsigned int *);
class AudioFileCache {
public:
 void readAudioFile(OpenAudioFile *entry);
private:
 char pad00[0x2C];
 _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > m_failed;
 unsigned int m_activeBytes, m_unusedBytes, m_budget;
 void *m_badHandle, *m_thread;
 bool m_quit;
 void *m_mutex;
};
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
  if (m_activeBytes > m_budget) ((Rva000A7E9E *)this)->freeUnusedSamples();
  break;
 }
}
