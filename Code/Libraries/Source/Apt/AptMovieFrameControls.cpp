// cl: /O2 /MD
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
struct AptCharacterInst { char pad[12]; AptCharacter *character; };
class AptCIH { public: char pad[0x4c]; AptCharacterInst *inst; const AptCIH *rva006E0CB0() const; };
struct AptPlaceControl {int flags,depth,character;};
struct AptControl {int type; union {struct {int sprite,stream;} init; AptPlaceControl place; int value;};};
struct AptFrame {int count; AptControl **controls;};
class AptDisplayList {public:void placeObject(AptPlaceControl *,AptCIH *); void removeObject(int *);};
class AptMovie {public:int nFrames;AptFrame *frames; void doFrameControls(AptDisplayList *,AptCIH *,int);};
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
