// ?rva001F5923@Rva001F5923@@QAEXXZ
// partial score=0.9899833194328607 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// Native1F5923..1F5A6A (327B). Owner/original callback name unresolved,
// so neutral receiver spelling retained. WB B16630 maps via vtable and
// reproduces timing, frame-cache and manager-list control flow.
// Clean donor575ba2b04 game/GameEngine/Source/GameClient/System/ParticleSys.cpp
// ParticleSystemManager::update (line2444), also ZH ParticleSys.cpp2928,
// is the semantic guide for handle/list traversal, update(playerIndex),
// advancing before deleting a dead system. This does not prove target owner.
// Target independently supplies list4C, elapsed60, playerIndex64, frame74;
// particle98 filter and clientC8/logic125 pause flags; global9C2 timing and
// D45 frame cache. Canonical GameLogic flag view retained. Scalar destructor
// flag0 followed by global operator delete matches native ::delete syntax.
// Remaining residue: after-before conversion scratch uses EBP-18/-14 instead
// of native dead before timer's EBP-20/-1C; all other327-byte code matches.
// stlport
#include <list>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64*);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64*);
class GlobalData{public:char pad0[0x9c2];bool profile;char pad9c3[0xd45-0x9c3];bool skipRepeatedFrames;};
extern GlobalData *TheWritableGlobalData;
class GameClient{public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6C();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
virtual unsigned getFrame()const;
 char pad4[0xc8-4];bool flagC8;
};extern GameClient *TheGameClient;
class ParticleSystem{public:virtual ~ParticleSystem();virtual void slot4();virtual void slot8();virtual void slotC();virtual bool update(int);char pad4[0x98-4];int flag98;};
class RvaSmartPtr12{public:RvaSmartPtr12():ptr(0),prev(0),next(0){};RvaSmartPtr12 &operator=(const RvaSmartPtr12&);void rva0004CBC0()throw();~RvaSmartPtr12(){if(ptr)rva0004CBC0();}ParticleSystem *ptr;void *prev,*next;};
class Rva001F5923{public:void rva001F5923();char pad0[0x4c];_STL::list<RvaSmartPtr12> systems;char pad50[0x60-0x50];float elapsed;int playerIndex;char pad68[0x74-0x68];unsigned lastFrame;};
void Rva001F5923::rva001F5923(){
 elapsed=0.0f;
 __int64 frequency,before;
 if(TheWritableGlobalData->profile){QueryPerformanceFrequency(&frequency);QueryPerformanceCounter(&before);}
 if(TheWritableGlobalData && TheWritableGlobalData->skipRepeatedFrames){unsigned frame=TheGameClient?TheGameClient->getFrame():0;if(frame==lastFrame)return;lastFrame=frame;}
 RvaSmartPtr12 sys;
 bool paused=TheGameClient->flagC8 && !TheGameLogic->getFlag125();
 for(_STL::list<RvaSmartPtr12>::iterator i=systems.begin();i!=systems.end();){
  sys=*i;
  if(sys.ptr){if(sys.ptr->flag98 || paused){if(!sys.ptr->update(playerIndex)){++i;::delete sys.ptr;}else ++i;}else ++i;}
 }
 if(TheWritableGlobalData->profile){__int64 after;QueryPerformanceCounter(&after);elapsed=(after-before)*1000.0f/frequency;}
}
