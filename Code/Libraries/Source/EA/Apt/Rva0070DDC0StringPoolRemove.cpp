// cl: /O2 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva0070DDC0Remove@@YAXPAUStringNode0070D9F0@@@Z retail 0x0070DDC0 405 bytes
// (Ghidra stops at 402 before the final tail jmp [edx+4]; extent ends 0x0070DF54).
// WB 1772580 identifies StringPool RemoveFromPool: the assert texts bFound
// (line 0x20A) and pLocalString != NULL (line 0x24D) name the StringPool.cpp
// source copied verbatim from retail. Follows the matched intern at 0x0070DBB0
// (Rva0070DBB0StringPool.cpp) and reuses its node view {vptr flags string
// next} and its counters: users 0x00E18384 strings 0x00E18380 saved bytes
// 0x00E18374 max saved 0x00DDCF4C. Looks the node up in its hash bucket then
// drops one user; a pinned root count 0x7F or a count above one only
// subtracts the saved bytes; the last root unlinks the node updates the saved
// bytes and the string count and releases it through vslot 1 (tail jmp).
// The shared max-saved tail comes from the chained assignment into a local
// in both subtract paths. Flags are the region default (/O2 /arch:SSE).
extern void(__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class AptValue {
public:
  virtual void AddRef();
  virtual void Release();
  virtual void ForceDelete();
};

class BfmeAptValue006DCD20 {
  virtual void slot0();

public:
  unsigned int getGCRootCount() const;
  void incrementGCRootCount();
  void decrementGCRootCount();
};

class EAStringC {
  void *m_pData;

public:
  unsigned short rva006D2F40() const;
  unsigned int rva006D3750() const;
};

struct StringNode0070D9F0 {
  void *m_vtbl;
  int m_flags;
  EAStringC m_str;
  StringNode0070D9F0 *m_next;
};
extern int g_00E1836C;
extern StringNode0070D9F0 **g_00E18368;
extern int g_00E18374;
extern int sStringPoolCurrentUsers;
extern int sStringPoolCurrentStrings;
extern int sStringPoolMaxMemorySaved;
#define STRING_POOL_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\StringPool.cpp"
static __forceinline void poolAssert(const char *test, int line) {
  g_bfmeAptAssertAtE17734(test, STRING_POOL_FILE, line);
  if (g_bfmeAptBreakOnAssertAtDDC01C) {
    __asm int 3
  }
}
static __forceinline int poolStringSize(StringNode0070D9F0 *node) {
  unsigned int a = (node->m_str.rva006D3750() + 12) & ~3;
  unsigned int b = (node->m_str.rva006D3750() + 10) & ~3;
  return a - b + 8;
}
void Rva0070DDC0Remove(StringNode0070D9F0 *node){
 unsigned short bucket=(unsigned short)((int)node->m_str.rva006D2F40()%g_00E1836C);
 bool found=false;
 for(StringNode0070D9F0 *n=g_00E18368[bucket];n;n=n->m_next){if(n==node){found=true;break;}}
 if(!found)poolAssert("bFound",0x20a);
 --sStringPoolCurrentUsers;
 BfmeAptValue006DCD20*v=(BfmeAptValue006DCD20*)node;
 unsigned roots=v->getGCRootCount();
 int saved;
 if(roots==0x7f){
  saved = g_00E18374 -= ((node->m_str.rva006D3750() + 10) & ~3) + 8;
 }
 else{
 v->decrementGCRootCount();
 if(roots!=1){
  saved = g_00E18374 -= ((node->m_str.rva006D3750() + 10) & ~3) + 8;
 }
 else{
 unsigned short bucket=(unsigned short)((int)node->m_str.rva006D2F40()%g_00E1836C);
 StringNode0070D9F0 *local=g_00E18368[bucket];
 g_00E18374 += poolStringSize(node);
 if (g_00E18374 > sStringPoolMaxMemorySaved) sStringPoolMaxMemorySaved = g_00E18374;
 --sStringPoolCurrentStrings;
 if(local==node){g_00E18368[bucket]=node->m_next;((AptValue*)node)->Release();}
 else{
 while(local->m_next!=node){local=local->m_next;if(!local)poolAssert("pLocalString != NULL",0x24d);}
 local->m_next=node->m_next;((AptValue*)node)->Release();
 }
 return;
 }
 }
 if (saved > sStringPoolMaxMemorySaved) sStringPoolMaxMemorySaved = saved;
}
