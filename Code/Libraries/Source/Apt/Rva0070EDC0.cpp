// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail70EDC0..70EFE6 plus 8 switch entries through70F008: 584B.
// WB179D930 confirms frame0/count + frame4/eight-byte array and two-arg
// thiscall pointer relocation. Target independently proves cases1/2/3/8,
// item stride12 and nested offsets34/3c; other cases only slide the entry.
// Original class identity unknown. Existing forwarder6FD040 is opaque here;
// its three-word caller ABI is independently measured. Relocation macro must
// reevaluate lvalues: a T*& helper incorrectly caches the member address.
// Hash cleanup uses actual existing canonical GC provider and opaque dtor.
extern "C" void Rva006FD040(void *,void *,void *);
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva0070A840 {public:~Rva0070A840();};
class AptNativeHash {public:void DestroyGCPointers();};
struct Entry {int kind; char *p4; char *p8; char pad[0x28]; char *p34; char pad38[4]; struct Extra *extra;};
struct Item {int unused[2];char *p;};
struct Extra {int count;Item *items;};
struct Frame {int count;Entry **entries;};
class Rva0070EDC0 {public:int count;Frame *frames;Rva0070A840 *hash;void rva0070EDC0(int delta,void *context);};
template<class T> inline T *shift(T *p,int delta){return (T*)((char*)p-delta);}
#define SLIDE(p) if(p) p=shift(p,delta)
#define E frames[i].entries[j]
void Rva0070EDC0::rva0070EDC0(int delta,void *context) {
 for(int i=0;i<count;++i){
  for(int j=0;j<frames[i].count;++j){
   switch(E->kind){
    case 1:Rva006FD040(E->p4,(void*)delta,context);SLIDE(E->p4);break;
    case 8:Rva006FD040(E->p8,(void*)delta,context);SLIDE(E->p8);if((int)E->p4<0)E->p4=(char*)-(int)E->p4;break;
    case 3:{Extra *p=E->extra;if(p){for(int k=0;k<p->count;++k){Rva006FD040(p->items[k].p,(void*)delta,context);SLIDE(p->items[k].p);}SLIDE(p->items);}SLIDE(E->p34);SLIDE(E->extra);break;}
    case 2:SLIDE(E->p4);break;
   }
   SLIDE(E);
  }
  SLIDE(frames[i].entries);
 }
 SLIDE(frames);
 if(hash){((AptNativeHash*)hash)->DestroyGCPointers();Rva0070A840 *p=hash;if(p){p->~Rva0070A840();g_pChainBlockAllocator->freeBlock(p,20);}hash=0;}
}
