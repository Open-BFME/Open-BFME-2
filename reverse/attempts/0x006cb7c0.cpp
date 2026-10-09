// ?setString@PooledString@@AAEXPBD@Z
// partial score=0.9512195121951219 date=2026-10-09
// cl: /MD /EHsc 
// Target PooledString::setString at6CB7C0: Ghidra489 omits trailing RET4;
// full body ends6CB9AC (492B). Hash is owned at6CB780. Entry next0,
// folded-case alias4 and text8 are established by target comparisons.
// Lock36B is the existing target ABI at411C1; flags+20 and CS+8 are
// witnessed by Enter/LeaveCriticalSection imports. Original pool names unknown.
#define _DLL
#include <string.h>
#include "../../../Include/Common/Rva00041004Lock.h"
extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *);
__declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *);
}
namespace _STL {
template<class T> class allocator {public:static T *allocate(unsigned,const void*);};
}
struct PooledStringEntry {
 PooledStringEntry *next;
 PooledStringEntry *noCase;
 char text[1];
};
extern PooledStringEntry ThePooledStringEmptyEntry;
class PooledString {
private:
 void setString(const char *text);
private:
 unsigned getHash(const char *,int) const;
 PooledStringEntry *m_entry;
};
PooledStringEntry *PooledStringPoolBuckets[0x2B7B];
#define poolBuckets PooledStringPoolBuckets
char *PooledStringPoolBuffer;
#define poolBuffer PooledStringPoolBuffer
unsigned PooledStringPoolUsed;
#define poolUsed PooledStringPoolUsed
class PooledStringGuard {
public:
 Rva00041004 *lock;
 bool held;
 PooledStringGuard(Rva00041004 &l):lock(&l),held(false) {
  if(!lock->m_flag) EnterCriticalSection(&lock->m_cs);
  held=true;
 }
 ~PooledStringGuard() {
  if(!lock->m_flag) LeaveCriticalSection(&lock->m_cs);
 }
};
void PooledString::setString(const char *text)
{
 if(text && *text) {
  unsigned hash=getHash(text,strlen(text));
  static Rva00041004 poolLock(1);
  PooledStringGuard guard(poolLock);
  PooledStringEntry **bucket=&poolBuckets[hash%0x2B7B];
  PooledStringEntry *entry=*bucket;
  for(;entry;entry=entry->next)
   if(strcmp(text,entry->text)==0) {m_entry=entry;return;}
  unsigned bytes=(unsigned)(strlen(text)+sizeof(PooledStringEntry));
  int used=poolUsed;
  if((unsigned)(used+bytes)>0x40000) {
   poolBuffer=_STL::allocator<char>::allocate(0x40000,(const void*)0x737472);
   used=0;
  }
  entry=(PooledStringEntry*)(poolBuffer+used);
  poolUsed=used+bytes;
  strcpy(entry->text,text);
  PooledStringEntry *alias=*bucket;
  for(;alias;alias=alias->next)
   if(_stricmp(text,alias->text)==0) {
    if(alias->noCase)alias=alias->noCase;
    break;
   }
  entry->noCase=alias;
  entry->next=*bucket;
  *bucket=entry;
 } else m_entry=&ThePooledStringEmptyEntry;
}
