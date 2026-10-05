// cl: /O2 /MD /EHsc
// Donor 5767d8d001ee10b1 AptMovie.cpp supplies two-pass init/dispatch semantics.
// Native 70F370 extent559 proves frame stride8, controls type1..8, initialization
// record16B and old PlaceObject2-only flow. Target has no later import fixups.
// Character parent+4 and animation array+16 are native data-use evidence.
// E176FC and E17738 are native zero-initialized background guard/callback slots.
// E17784 reuses the existing two-word cdecl external ABI; donor StartSound role
// conflicts with that older external's Free name, so no new semantic pin is made.
// Link backlog:700090/706950 setup cleanup;6E6B40 init;6F8EC0 place; existing globals.
class AptCIH;
struct Rva00700090Info { void *m_0; int m_4; const char *m_8; int m_c; };
class Rva00700090 {public:void *rva00700090(Rva00700090Info *);};
class Rva007002C0 {public:void rva007002C0(int,void *,int,void *);};
class Rva00706950 {public:void rva00706950(void *,Rva00700090Info *);};
class Rva006CD650 {public:void *rva006CD650();};
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
bool g_aptBackgroundSet = false;
void (__cdecl *g_aptBackgroundCallback)(int) = 0;
extern void (__cdecl *g_bfmeAptFreeAtE17784)(void *,int);
void AptDebuggerPrint(int,const char *,...);
#define CHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMovie.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
struct AptCharacter;
struct AptCharacterAnimation { char pad[16]; AptCharacter **characters; void ExecuteInitActions(AptCIH *,int); };
struct AptCharacter { int type; AptCharacter *parent; union { AptCharacterAnimation animation; void *sound; }; };
struct AptCharacterInst { char pad[12]; AptCharacter *character; int hash,unknown,frame; };
class AptCIH { public: char pad[0x4c]; AptCharacterInst *inst; const AptCIH *rva006E0CB0() const; bool IsSpriteInstBase() const;
 AptCharacterInst *Sprite() const {if(!IsSpriteInstBase()){g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}return inst;} };
struct AptPlaceControl {int flags,depth,character; float matrix[6]; int cxform[2]; float ratio; int unknown[2]; void *actions;};
struct AptControl {int type; union {struct {int sprite,stream;} init; AptPlaceControl place; int value;};};
struct AptFrame {int count; AptControl **controls;};
class AptDisplayList {public:void placeObject(AptPlaceControl *,AptCIH *); void removeObject(int *);};
class AptPseudoDisplayList;
class AptMovie {public:int nFrames;AptFrame *frames; void doFrameControls(AptDisplayList *,AptCIH *,int); void DoTemporaryFrameControls(AptPseudoDisplayList *,int);};
void AptMovie::doFrameControls(AptDisplayList *display,AptCIH *inst,int frame) {
 CHECK(frame>=0 && frame<nFrames,0x110,"nFrame >= 0 && nFrame < (int)nFrames");
 for(int i=0;i<frames[frame].count;++i) {
  AptControl *control=frames[frame].controls[i];
  if(control->type==8 && control->init.sprite>=0) {
   Rva00700090Info setup={inst,0,"AptDoFrameControls",0x100000};
   void *saved=((Rva00700090 *)&g_aptDateInterpreter)->rva00700090(&setup);
   int before=*(int *)&g_aptDateInterpreter;
   void *character=inst ? ((Rva006CD650 *)inst->rva006E0CB0())->rva006CD650() : 0;
   ((Rva007002C0 *)&g_aptDateInterpreter)->rva007002C0(control->init.stream,inst,-1,character);
   control->init.sprite=-control->init.sprite;
   CHECK(before==*(int *)&g_aptDateInterpreter,0x133,"nStackSizePre == nStackSizePost");
   ((Rva00706950 *)&g_aptDateInterpreter)->rva00706950(saved,&setup);
  }
 }
 for(int i=0;i<frames[frame].count;++i) {
  AptControl *control=frames[frame].controls[i];
  switch(control->type) {
   case 5: if(!g_aptBackgroundSet){g_aptBackgroundCallback(control->value);g_aptBackgroundSet=true;} break;
   case 3: inst->inst->character->parent->animation.ExecuteInitActions(inst,control->place.character);display->placeObject(&control->place,inst);break;
   case 4: display->removeObject(&control->value);break;
   case 6: g_bfmeAptFreeAtE17784(inst->inst->character->parent->animation.characters[control->value]->sound,0);break;
   case 7: AptDebuggerPrint(3,"warning: soundstream level is always 0\n");break;
   case 1:case 2:case 8:break;
   default: CHECK(0,0x178,"NOT_REACHED");
  }
 }
}

#pragma comment(linker, "/alternatename:?rva007002C0@Rva007002C0@@QAEXHPAXH0@Z=?runStream@AptActionInterpreter@@QAEPBEPBEPAVAptCIH@@HPAUAptCharacterInst@@@Z")
#pragma comment(linker, "/alternatename:?removeObject@AptDisplayList@@QAEXPAH@Z=?bfmeForward1279@BfmeWrapper1279@@QAEXPAUBfmeInput1279@@@Z")
#pragma comment(linker, "/alternatename:?AptDebuggerPrint@@YAXHPBDZZ=?Rva006CC110Log@@YAXHPBDZZ")

// Temporary controls: donor semantic guide; native preserves old always-true
// (flags & 1 | 0x98) clause removed in later source. PDB node remains20B.
class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
struct AptControlInfo {int unused; float *matrix; int *cxform; void *actions; float ratio; int flags;};
struct AptPseudoCIH_t {AptControl *control;AptControlInfo *info; AptPseudoCIH_t *next,*prev; int depth;
 AptPseudoCIH_t(AptControl *,int,int,AptCharacter *);
 static void *operator new(unsigned int size){return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(size);}
 static void operator delete(void *,unsigned int);
};
class AptPseudoDisplayList {public:void *head;AptCIH *parent;void FindInst(int,AptPseudoCIH_t **,AptPseudoCIH_t **);void Insert(AptPseudoCIH_t *);};
void AptMovie::DoTemporaryFrameControls(AptPseudoDisplayList *display,int frame) {
 CHECK(frame>=0 && frame<nFrames,0xb2,"nFrame >= 0 && nFrame < (int)nFrames");
 if(frame<0 || frame>=nFrames) return;
 AptCIH *sprite=display->parent;
 for(int i=0;i<frames[frame].count;++i){
  AptControl *control=frames[frame].controls[i];
  CHECK(frame==sprite->Sprite()->frame,0xc0,"nFrame == pSprInst->getSpriteInstBase()->nFrame");
  switch(control->type) {
   case 3: {
    AptCharacter *character=0;
    AptPseudoCIH_t *prev,*item;
    AptPlaceControl *place=&control->place;
    display->FindInst(place->depth,&prev,&item);
    if(place->character!=-1)character=sprite->inst->character->parent->animation.characters[place->character];
    if(item && place->character==-1 && (place->flags & 1 | 0x98)) {
     CHECK(item->info!=0,0xd3,"pItem->pControlInfo != NULL");
     CHECK(item->control->type==3,0xd4,"pItem->pControl->eType == AptControlType_PlaceObject2");
     item->info->matrix=place->flags&4 ? place->matrix : item->info->matrix;
     item->info->cxform=place->flags&8 ? place->cxform : item->info->cxform;
     item->info->actions=place->flags&0x80 ? place->actions : item->info->actions;
     item->info->ratio=place->flags&0x10 ? place->ratio : item->info->ratio;
     item->info->flags|=place->flags;
    } else display->Insert(new AptPseudoCIH_t(control,frame,place->depth,character));
    break;
   }
   case 4:display->Insert(new AptPseudoCIH_t(control,frame,control->value,0));break;
   case 1:case 2:case 5:case 6:case 7:case 8:break;
   default:CHECK(0,0xf1,"NOT_REACHED");
  }
 }
}

#pragma comment(linker, "/alternatename:?IsSpriteInstBase@AptCIH@@QBE_NXZ=?isSpriteInstBase@Rva006CFCD0@@QBE_NXZ")
#pragma comment(linker, "/alternatename:?FindInst@AptPseudoDisplayList@@QAEXHPAPAUAptPseudoCIH_t@@0@Z=?rva006F6AC0@Rva006F6AC0@@QAEXHPAPAX0@Z")
#pragma comment(linker, "/alternatename:??0AptPseudoCIH_t@@QAE@PAUAptControl@@HHPAUAptCharacter@@@Z=??0Rva006F6A50@@QAE@PAXHHH@Z")
#pragma comment(linker, "/alternatename:??3AptPseudoCIH_t@@SAXPAXI@Z=?Rva006D8680Free@@YAXPAXH@Z")

#pragma comment(linker, "/alternatename:?rva00706950@Rva00706950@@QAEXPAXPAURva00700090Info@@@Z=?CleanupAfterExecution@AptActionInterpreter@@QAEXPAXPAUAptActionSetup@@@Z")
