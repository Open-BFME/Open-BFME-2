// cl: /MD
// Source guide: audit94f4f7439c775c49-AptValueGCAllocator.cpp.
// Native independently establishes pool-manager first pointer at+4; pool
// next/size/unused at0/4/8 and payload+12. Bounds use unsigned addresses.
// The allocated-bit partial view and inline predicate repeat the existing
// verified Rva006D29E0Cluster declarations; its setter/size methods are reused.
// Rva006D2A60::freeBlock retains the existing address-qualified provider ABI;
// its receiver is only forwarded to the offset-zero base pool deallocator.
// It does not read the allocated-value fields through its pool receiver.
// Existing inline INT3 assertion barriers preserve the native cold paths.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern unsigned char g_00E177E0;
class Rva006D2A60 {
public:
 struct Bits {unsigned allocated:1;unsigned rest:31;};
 Bits first,second;
 __forceinline bool isAllocated(int mode) {
  if(mode==4)return second.allocated;
  if(mode==0)return first.allocated;
  g_bfmeAptAssertAtE17734("false","..\\..\\include\\apt\\AptValueGCAllocator.h",0xe2);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
  return false;
 }
 int rva006D2930(int mode);
 void rva006D28D0(int,bool);
 void freeBlock(void *,int);
};
class AptValue;
class AptValueGC_PoolManager {
public:
 struct Pool { Pool *next;unsigned int size,left;
  __forceinline bool contains(const void *p) {return (unsigned int)p >= (unsigned int)(this+1) && (unsigned int)p < (unsigned int)(this+1)+size-left;}
 };
 unsigned int unused;
 Pool *first;
 AptValue *GetFirstAptValue();
 AptValue *GetNextAptValue(const AptValue *);
};
// Native6D2CB0..6D2D3A:138B including both complete returns.
AptValue *AptValueGC_PoolManager::GetFirstAptValue()
{
 Pool *pool=first;
 do {
  char *item=(char *)(pool+1);
  while(pool->contains(item)) {
   Rva006D2A60 *value=(Rva006D2A60 *)item;
   unsigned int size;
   if(value->isAllocated(g_00E177E0))return (AptValue *)item;
   else size=value->rva006D2930(g_00E177E0);
   item+=size;
  }
 }while((pool=pool->next)!=0);
 return 0;
}

int Rva006CD3F0Get(void *);
// Native6D2B70..6D2CA3:307B. This older target lacks the donor's later
// outside-allocation fallback and size-rounding steps. Every pool transition
// and allocation-bit branch is independently present in the native body.
AptValue *AptValueGC_PoolManager::GetNextAptValue(const AptValue *previous)
{
 Pool *pool=first;
 do {if(pool->contains(previous))break;}while((pool=pool->next)!=0);
 char *item=(char *)previous;
 unsigned int size;
 if(((Rva006D2A60 *)item)->isAllocated(g_00E177E0))size=Rva006CD3F0Get(item);
 else size=((Rva006D2A60 *)item)->rva006D2930(g_00E177E0);
 item+=size;
 if(!pool->contains(item)) {
  pool=pool->next;
  if(pool)item=(char *)(pool+1);
 }
 while(pool) {
  while(pool->contains(item)) {
   unsigned int size;
   if(((Rva006D2A60 *)item)->isAllocated(g_00E177E0))return (AptValue *)item;
   else size=((Rva006D2A60 *)item)->rva006D2930(g_00E177E0);
   item+=size;
  }
  pool=pool->next;
  item=(char *)((unsigned int)pool+12);
 }
 return 0;
}

class Rva006DB270 {public:void freeBlock(void *,int);};
// Native6D2A60..6D2B62:258B, including the cold predicate failure branch.
// The donor notes removal of post-free processing in2007; retail still clears
// the allocated bit and checks the freed size, so preserve those native calls.
void Rva006D2A60::freeBlock(void *pNowFree,int nAllocatedSize)
{
 if(Rva006CD3F0Get(pNowFree)!=nAllocatedSize) {
  g_bfmeAptAssertAtE17734("AptGetSizeOfAptValue(pNowFree) == nAllocatedSize && \"MemFree was passed the wrong size for this object!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueGCAllocator.cpp",0x93);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 Rva006D2A60 *item=(Rva006D2A60 *)pNowFree;
 if(!item->isAllocated(g_00E177E0)) {
  g_bfmeAptAssertAtE17734("pItem->IsAllocated(snOffsetToStoreSize) && \"MemFree Was called on a value that was already deallocted!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueGCAllocator.cpp",0x94);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 ((Rva006DB270 *)this)->freeBlock(pNowFree,nAllocatedSize);
 item->rva006D28D0(g_00E177E0,false);
 int size=item->rva006D2930(g_00E177E0);
 if(size!=nAllocatedSize) {
  g_bfmeAptAssertAtE17734("nItemSize == nAllocatedSize","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueGCAllocator.cpp",0x9e);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
}
