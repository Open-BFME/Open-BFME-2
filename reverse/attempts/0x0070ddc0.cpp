// ?Rva0070DDC0Remove@@YAXPAUStringNode0070D9F0@@@Z
// partial score=0.8830409357 date=2026-10-09
// cl: /O2 /G6 /DNDEBUG /MD /EHsc
// StringPool::GetFromPool identified by WB17722F0 and native assertions.
// Native node {vptr flags string next} is independently established by
// the existing shutdown provider at70D9F0. Reuse its table and counters.
// Metrics offsets are native facts; descriptive names below do not claim
// recovered original identifiers. The four counts start at zero; max saved bytes starts at INT_MIN.
// Explicit EAStringC temporary lifetime plus direct saved-memory updates
// reproduce all527 bytes. No donor C++ was found in the committed BFME1 tree.
extern void(__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class Rva006DB270 {
public:
  void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;

class AptValue {
public:
  virtual void AddRef();
  virtual void Release();
  virtual void ForceDelete();
  unsigned int getRefCount() const;
};

class BfmeAptValue006DCD20 {
  virtual void slot0();

public:
  unsigned int getGCRootCount() const;
  void incrementGCRootCount();
  void decrementGCRootCount();
};

class AptValueVector {
public:
  void ReleaseValues();
};
extern AptValueVector *g_releaseVectorAtE17710;

class EAStringC {
  void *m_pData;

public:
  EAStringC(const char *);
  ~EAStringC();
  EAStringC &operator=(const EAStringC &);
  unsigned short rva006D2F40() const;
  bool rva006D3490(const char *) const;
  void rva006D3BA0() const;
  unsigned int GetInternalRefCount() const;
  unsigned int rva006D3750() const;
  void rva006D3470();
};

struct StringNode0070D9F0 {
  void *m_vtbl;
  int m_flags;
  EAStringC m_str;
  StringNode0070D9F0 *m_next;
};
extern int g_00E1836C;
// g_00E1836C: matched references place it at VA 0xe1836c (zero-filled .bss).
extern int g_00E1836C;
// g_00E18368: matched references place it at VA 0xe18368 (retail .data initial
// value 0).
extern StringNode0070D9F0 **g_00E18368;
extern int g_00E18374;
// g_00E18374: matched references place it at VA 0xe18374 (zero-filled .bss).
extern int g_00E18374;
extern EAStringC saConstantAtE18388[];
// g_00E18650: matched references place it at VA 0xe18650 (zero-filled; a
// plain-data view).
extern EAStringC g_00E18650;

class AptString {
public:
  static AptString *Create();
};
unsigned short hashLower(const char *);
int sStringPoolCurrentUsers, sStringPoolMaxUsers, sStringPoolCurrentStrings,
    sStringPoolMaxStrings;
int sStringPoolMaxMemorySaved=(-2147483647-1);
#define STRING_POOL_FILE                                                       \
  "C:"                                                                         \
  "\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\St" \
  "ringPool.cpp"
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
static __forceinline int poolSavedSize(StringNode0070D9F0 *node) {
  return ((node->m_str.rva006D3750() + 10) & ~3) + 8;
}
static __forceinline void poolUpdateSaved(int delta) {
  g_00E18374 += delta;
  if (g_00E18374 > sStringPoolMaxMemorySaved)
    sStringPoolMaxMemorySaved = g_00E18374;
}
StringNode0070D9F0 *Rva0070DBB0Intern(const char *text) {
  unsigned short hash = (unsigned short)hashLower(text);
  unsigned short bucket = (unsigned short)((int)hash % g_00E1836C);
  ++sStringPoolCurrentUsers;
  if (sStringPoolCurrentUsers > sStringPoolMaxUsers)
    sStringPoolMaxUsers = sStringPoolCurrentUsers;
  for (StringNode0070D9F0 *node = g_00E18368[bucket]; node;
       node = node->m_next) {
    EAStringC *s = &node->m_str;
    if (s->rva006D2F40() == hash && s->rva006D3490(text)) {
      BfmeAptValue006DCD20 *v = (BfmeAptValue006DCD20 *)node;
      if (v->getGCRootCount() != 0x7f)
        v->incrementGCRootCount();
      g_00E18374 += poolSavedSize(node);
      if (g_00E18374 > sStringPoolMaxMemorySaved)
        sStringPoolMaxMemorySaved = g_00E18374;
      return node;
    }
  }
  StringNode0070D9F0 *node = (StringNode0070D9F0 *)AptString::Create();
  {
    EAStringC temp(text);
    node->m_str = temp;
  }
  node->m_str.rva006D3BA0();
  if (hash != node->m_str.rva006D2F40())
    poolAssert("uHash == pString->str.GetHashValue()", 0x1ca);
  node->m_next = g_00E18368[bucket];
  g_00E18368[bucket] = node;
  ((AptValue *)node)->AddRef();
  BfmeAptValue006DCD20 *v = (BfmeAptValue006DCD20 *)node;
  if (v->getGCRootCount() != 0)
    poolAssert("pString->getGCRoot() == 0", 0x1d1);
  v->incrementGCRootCount();
  g_00E18374 -= poolStringSize(node);
  if (g_00E18374 > sStringPoolMaxMemorySaved)
    sStringPoolMaxMemorySaved = g_00E18374;
  ++sStringPoolCurrentStrings;
  if (sStringPoolCurrentStrings > sStringPoolMaxStrings)
    sStringPoolMaxStrings = sStringPoolCurrentStrings;
  return node;
}

void Rva0070DDC0Remove(StringNode0070D9F0 *node){
 unsigned short bucket=(unsigned short)((int)node->m_str.rva006D2F40()%g_00E1836C);
 bool found=false;
 for(StringNode0070D9F0 *n=g_00E18368[bucket];n;n=n->m_next){if(n==node){found=true;break;}}
 if(!found)poolAssert("bFound",0x20a);
 --sStringPoolCurrentUsers;
 BfmeAptValue006DCD20*v=(BfmeAptValue006DCD20*)node;
 unsigned roots=v->getGCRootCount();
 if(roots==0x7f)poolUpdateSaved(-poolSavedSize(node));
 else{
 v->decrementGCRootCount();
 if(roots!=1)poolUpdateSaved(-poolSavedSize(node));
 else{
 unsigned short bucket=(unsigned short)((int)node->m_str.rva006D2F40()%g_00E1836C);
 StringNode0070D9F0 *local=g_00E18368[bucket];
 poolUpdateSaved(poolStringSize(node));--sStringPoolCurrentStrings;
 if(local==node){g_00E18368[bucket]=node->m_next;((AptValue*)node)->Release();}
 else{
 while(local->m_next!=node){local=local->m_next;if(!local)poolAssert("pLocalString != NULL",0x24d);}
 local->m_next=node->m_next;((AptValue*)node)->Release();
 }
 }
 }
}
