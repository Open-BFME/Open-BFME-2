// ?rva006F7720Sub@AptAnimationPoolData@@QAEXPAXH@Z
// partial score=0.8 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /MD
// Native 6F7720..6F79A3 is 643B through RET8 (served636 extent cuts epilogue).
// Display-list visitor uses the owned112B/395B rendering callbacks, sorted
// 32-entry mask stack (owned7570/7600) and native AptDisplayList assertions.
// Layout and clipping-key comparisons are target evidence, not donor names.
// Flags storage is native .bss at RVA A17718; bit4 chooses clip-stack path.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#define DISPLAY_ASSERT(test,text,line) if(!(test)){g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDisplayList.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
unsigned int g_aptDisplayListRenderFlags;
class BfmeAptValue006DCD20 {public:bool isUndefined()const;};
class Rva006DBB30SarDwordField {public:int get()const;};
struct AptMaskInfo {int unknown00;int clipDepth;};
struct AptDisplayNode {char unknown00[0x4C];AptMaskInfo *info;AptDisplayNode *prev,*next; signed int depth:17;unsigned int flags:15;};
struct Rva006F7570Item;
class Rva006F7600 {
public:
 Rva006F7600():count(0){}
 ~Rva006F7600(){DISPLAY_ASSERT(count==0,"nElements == 0",0x537);}
 void rva006F7570(Rva006F7570Item*);
 void rva006F7600(int);
 AptDisplayNode *get(int i){DISPLAY_ASSERT(i>=0 && i<count,"i >= 0 && i < nElements",0x555);return items[i];}
 __forceinline void removeFront(){DISPLAY_ASSERT(count>0,"i >= 0 && i < nElements",0x54A);int i=0;int last=count-1;if(i<last){do{items[i]=items[i+1];++i;}while(i<count-1);}--count;}
 AptDisplayNode *items[32];int count;
};
void rva006F7330(void*,void*,int);
void *rva006F73A0(void*,void*,int);
typedef void (__cdecl *AptDisplayVisitor)(void*,void*,int);
struct AptDisplayHead {AptDisplayNode *head;};
class AptAnimationPoolData {public:AptDisplayHead *list;void rva006F7720Sub(void*,int);};
void AptAnimationPoolData::rva006F7720Sub(void *context,int mode)
{
 AptDisplayNode *item=list->head->next;
 Rva006F7600 masks;
 int maskCount=0;
 // Both visitors have the same native three-argument stack ABI; the clip
 // visitor's pointer result is discarded by this type-erased visitor API.
 AptDisplayVisitor visit;
 if(g_aptDisplayListRenderFlags&4)visit=(AptDisplayVisitor)rva006F73A0;else visit=rva006F7330;
 while(item){
  if(!((BfmeAptValue006DCD20*)item)->isUndefined()){
   if(!item){g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xD8);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
   if(((Rva006DBB30SarDwordField*)item)->get()!=19 || ((BfmeAptValue006DCD20*)item)->isUndefined()){
    if(item->info->clipDepth>=0){masks.rva006F7570((Rva006F7570Item*)item);visit(context,item,1);maskCount=masks.count;}
    else {
     while(maskCount>0){
      int last=maskCount-1;
      if(masks.get(last)->info->clipDepth>=item->depth)break;
      visit(context,masks.get(last),-1);
      masks.rva006F7600(last);maskCount=masks.count;
     }
     visit(context,item,mode);
    }
   }
  }
  item=item->next;
 }
 while(maskCount>0){visit(context,masks.get(0),-1);masks.removeFront();maskCount=masks.count;}
}
