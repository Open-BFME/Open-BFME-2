// ?rva0070E900@Rva0070E900@@QAEXPAX00@Z
// partial score=0.841837 date=2026-10-09
// ?rva0070E900@Rva0070E900@@QAEXPAX00@Z
// partial score=0.9 date=2026-10-09
// cl: /O2 /MD /EHsc
// Target70E900..70ED98 is1176B, including the out-of-line frame-label
// switch case. The queue1169B boundary truncates the final destructor call
// and jump. AptMovie.cpp assertions prove frames/control/event-action fields;
// the receiver's original type/API spelling is unresolved. This is a local
// data-format view, not a claimed donor layout.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270 {public:void freeBlock(void *,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class EAStringC {void *data;public:EAStringC(const char *);~EAStringC();};
class AptValue;
class AptInteger {public:static AptValue *Create(int);};
class AptNativeHash {
 char data[20];
public:
 AptNativeHash(int);
 void Set(const EAStringC *const,AptValue *const);
 static void *operator new(unsigned int size) {return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void *p,unsigned int size) {g_pChainBlockAllocator->freeBlock(p,size);}
};
void Rva006FD060Forward(void *,void *,void *,void *);
struct MovieEventAction {unsigned eventFlags,unknown;void *aActionStream;};
struct MovieEventActions {int nEventActions;MovieEventAction *aEventActions;};
struct MovieControl {
 int type;
 union {
  struct {void *aActionStream;} action;
  struct {char *szLabel;} frameLabel;
  struct {char pad[0x30];char *szName;unsigned unknown;MovieEventActions *pActions;} placeObject2;
  struct {unsigned sprite;void *aActionStream;} initAction;
 };
};
struct MovieFrame {int nControls;MovieControl **apControls;};
class Rva0070E900 {
 int nFrames;
 MovieFrame *aFrames;
 AptNativeHash *phLabels;
public:
 void rva0070E900(void *pBase,void *pConstantFile,void *pCount);
};
#define MOVIE_ASSERT(test,text,line) do {if(!(test)){g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMovie.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}}while(0)
#define MOVIE_OFFSET(field,type) do {if(field)(unsigned &)(field)+=(unsigned)pBase;}while(0)
void Rva0070E900::rva0070E900(void *pBase,void *pConstantFile,void *pCount) {
 MOVIE_ASSERT(!phLabels,"!phLabels",0x1c);
 phLabels=new AptNativeHash(2);
 MOVIE_ASSERT((unsigned)aFrames<0xfffff,"(unsigned)aFrames < 0xfffff",0x1f);
 MOVIE_OFFSET(aFrames,MovieFrame *);
 for(int i=0;i<nFrames;++i) {
  MOVIE_ASSERT((unsigned)aFrames[i].apControls<0xfffff,"(unsigned)aFrames[i].apControls < 0xfffff",0x22);
  MOVIE_OFFSET(aFrames[i].apControls,MovieControl **);
  for(int j=0;j<aFrames[i].nControls;++j) {
   MOVIE_ASSERT((unsigned)aFrames[i].apControls[j]<0xfffff,"(unsigned)aFrames[i].apControls[j] < 0xfffff",0x25);
   MOVIE_OFFSET(aFrames[i].apControls[j],MovieControl *);
   switch(aFrames[i].apControls[j]->type) {
   case 1:
    MOVIE_ASSERT((unsigned)aFrames[i].apControls[j]->action.aActionStream<0xfffff,"(unsigned)aFrames[i].apControls[j]->action.actions.aActionStream < 0xfffff",0x2a);
    MOVIE_OFFSET(aFrames[i].apControls[j]->action.aActionStream,void *);
    Rva006FD060Forward(aFrames[i].apControls[j]->action.aActionStream,pBase,pConstantFile,pCount);
    break;
   case 2:
    MOVIE_ASSERT((unsigned)aFrames[i].apControls[j]->frameLabel.szLabel<0xfffff,"(unsigned)aFrames[i].apControls[j]->frameLabel.szLabel < 0xfffff",0x46);
    MOVIE_OFFSET(aFrames[i].apControls[j]->frameLabel.szLabel,char *);
    {
     EAStringC label(aFrames[i].apControls[j]->frameLabel.szLabel);
     phLabels->Set(&label,AptInteger::Create(i));
    }
    break;
   case 3:
    MOVIE_ASSERT((unsigned)aFrames[i].apControls[j]->placeObject2.szName<0xfffff,"(unsigned)aFrames[i].apControls[j]->placeObject2.szName < 0xfffff",0x36);
    MOVIE_OFFSET(aFrames[i].apControls[j]->placeObject2.szName,char *);
    MOVIE_ASSERT((unsigned)aFrames[i].apControls[j]->placeObject2.pActions<0xfffff,"(unsigned)aFrames[i].apControls[j]->placeObject2.pActions < 0xfffff",0x37);
    MOVIE_OFFSET(aFrames[i].apControls[j]->placeObject2.pActions,MovieEventActions *);
    {
     MovieEventActions *pActions=aFrames[i].apControls[j]->placeObject2.pActions;
     if(pActions) {
      MOVIE_ASSERT((unsigned)pActions->aEventActions<0xfffff,"(unsigned)pActions->aEventActions < 0xfffff",0x3b);
      MOVIE_OFFSET(pActions->aEventActions,MovieEventAction *);
      for(int k=0;k<pActions->nEventActions;++k) {
       MOVIE_ASSERT((unsigned)pActions->aEventActions[k].aActionStream<0xfffff,"(unsigned)pActions->aEventActions[k].actions.aActionStream < 0xfffff",0x3e);
       MOVIE_OFFSET(pActions->aEventActions[k].aActionStream,void *);
       Rva006FD060Forward(pActions->aEventActions[k].aActionStream,pBase,pConstantFile,pCount);
      }
     }
    }
    break;
   case 8:
    MOVIE_ASSERT((unsigned)aFrames[i].apControls[j]->initAction.aActionStream<0xfffff,"(unsigned)aFrames[i].apControls[j]->initAction.actions.aActionStream < 0xfffff",0x30);
    MOVIE_OFFSET(aFrames[i].apControls[j]->initAction.aActionStream,void *);
    Rva006FD060Forward(aFrames[i].apControls[j]->initAction.aActionStream,pBase,pConstantFile,pCount);
    break;
   case 4:case 5:case 6:case 7:default:break;
   }
  }
 }
}
