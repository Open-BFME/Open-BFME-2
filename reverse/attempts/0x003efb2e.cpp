// ?Pathfind@LivingWorldPathFinder@@QAE_NPAVLivingWorldSearchCallback@@HPAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@PAHH@Z
// partial score=0.8541795666 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME1 donor9cbfb551 LivingWorldPathFinder.cpp guides the open/closed queues,
// zero-cost start and predecessor reconstruction. BFME2 adds callback slots8/C
// and the opaque two-word relaxation inputs; native3EFA0A/3EFB2E prove layouts.
#include <vector>
enum ObjectID { INVALID_ID=0 };
class Rva003C5890Item;
struct Rva003EF6A0Entry { int key; char pad04[0x18]; float f1c,f20,f24; Rva003EF6A0Entry *prev; };
struct Rva003EF6A0Span { Rva003EF6A0Entry **begin,**end; }; struct Rva003EF9DCNode; struct Rva003EF634Node;

void __stdcall Rva003EF9DCFill(Rva003EF9DCNode *,_STL::vector<ObjectID> *);
int __stdcall Rva003EF634Count(Rva003EF634Node *);
// Existing pointer-vector ABI facades. The donor slot-view name and wire
// vector specialization assert four-byte storage only, not native node identity.
class BfmeSlotVecG { public: void bfmeErase(void **,void **); void **begin,*end,*limit; };
class BfmeVecAG { public: void bfmeErase(int *); };
class LivingWorldSearchCallback { public: virtual void slot00(); virtual void slot04(); virtual void slot08(Rva003EF6A0Entry *); virtual bool slot0c(Rva003EF6A0Entry *,Rva003EF6A0Entry *); };
class LivingWorldPathFinder { public:
 Rva003EF6A0Entry *rva003EF6A0(Rva003EF6A0Span *,int);
 void rva003EF8E1(Rva003EF6A0Entry *,int,int);
 int FindShortestPath(LivingWorldSearchCallback *,int,int,int,_STL::vector<ObjectID> *,int);
 bool Pathfind(LivingWorldSearchCallback *,int,_STL::vector<ObjectID> *,int *,int);
 char prefix[0xc]; Rva003EF6A0Entry *start,*goal;
 _STL::vector<Rva003C5890Item *> open,closed;
 LivingWorldSearchCallback *callback;
};
bool LivingWorldPathFinder::Pathfind(LivingWorldSearchCallback *cb,int from,_STL::vector<ObjectID> *out,int *length,int flags) {
 callback=cb;
 ((BfmeSlotVecG *)&open)->bfmeErase((void **)open.begin(),(void **)open.end());
 ((BfmeSlotVecG *)&closed)->bfmeErase((void **)closed.begin(),(void **)closed.end());
 if(out) out->clear();
 Rva003EF6A0Entry *first=rva003EF6A0((Rva003EF6A0Span *)this,from);
 start=first;
 if(!first) return false;
 first->f1c=first->f20=first->f24=0.0f;
 start->prev=0;
 open.push_back((Rva003C5890Item *const &)start);
 while(open.size()) {
  Rva003EF6A0Entry *current=(Rva003EF6A0Entry *)open[0];
  ((BfmeVecAG *)&open)->bfmeErase((int *)open.begin());
  callback->slot08(current);
  if(callback->slot0c(current,goal)) {
   if(out) { Rva003EF9DCFill((Rva003EF9DCNode *)current,out); *length=out->size()-1; }
   else *length=Rva003EF634Count((Rva003EF634Node *)current);
   return true;
  }
  rva003EF8E1(current,-1,flags);
  closed.push_back((Rva003C5890Item *const &)current);
 }
 return false;
}
int LivingWorldPathFinder::FindShortestPath(LivingWorldSearchCallback *cb,int opaque,int from,int to,_STL::vector<ObjectID> *out,int flags) {
 callback=cb;
 if(from==to) { if(out) { out->clear(); out->push_back((ObjectID &)from); } return 0; }
 ((BfmeSlotVecG *)&open)->bfmeErase((void **)open.begin(),(void **)open.end());
 ((BfmeSlotVecG *)&closed)->bfmeErase((void **)closed.begin(),(void **)closed.end());
 if(out) out->clear();
 Rva003EF6A0Entry *first=rva003EF6A0((Rva003EF6A0Span *)this,from);
 start=first;
 goal=rva003EF6A0((Rva003EF6A0Span *)this,to);
 if(first && goal) {
  first->f1c=first->f20=first->f24=0.0f;
  start->prev=0;
  open.push_back((Rva003C5890Item *const &)start);
  while(open.size()) {
   Rva003EF6A0Entry *current=(Rva003EF6A0Entry *)open[0];
   ((BfmeVecAG *)&open)->bfmeErase((int *)open.begin());
   callback->slot08(current);
   if(callback->slot0c(current,goal)) {
    if(out) { Rva003EF9DCFill((Rva003EF9DCNode *)current,out); return out->size()-1; }
    return Rva003EF634Count((Rva003EF634Node *)current);
   }
   rva003EF8E1(current,opaque,flags);
   closed.push_back((Rva003C5890Item *const &)current);
  }
 }
 return -1;
}

// ?rva003EF6A0@LivingWorldPathFinder@@QAEPAURva003EF6A0Entry@@PAURva003EF6A0Span@@H@Z
Rva003EF6A0Entry *LivingWorldPathFinder::rva003EF6A0(Rva003EF6A0Span *span,int value) {
 unsigned i=0;
 unsigned count=(unsigned)(span->end-span->begin);
 for(;i<count;++i) if(value==span->begin[i]->key) return span->begin[i];
 return 0;
}
