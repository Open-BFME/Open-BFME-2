// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// Native 003F7F4B..003F802B, 224 bytes, RET0. Queue attribution is only
// positional: the original owner and function name remain unknown.
// Target independently proves reference8/stateC/label10/flags18,19,
// Audio slot25(+64), GameText slot14(+38), and the 136-byte event lifetime.
// The event constructor 2D982A and destructor 2D9A43 use the established shared
// BFME2 prefix; donor AudioEventRTS supplies its semantic guide only. The
// LivingWorld selection worker sets event+70; native zero position is copied
// through three SSE stores. Text lifetime uses the shared UnicodeString.
// All globals and direct callees reuse existing owners, with no new pins.
#include "Common/BfmeAudioEventPrefix136.h"
#include "unicode_string.h"
class AudioManager; extern AudioManager *TheAudio;
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class InGameUI; extern InGameUI *TheInGameUI;
class GameTextInterface; extern GameTextInterface *TheGameText;
class Rva002B2B66 {public:int rva002B2B66();};
class Rva0029B17C {public:void rva0029B17C();};
class Rva0029B16A {public:void rva0029B16A(int,int);};
class Rva003F7F4BAudioView {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual unsigned int add(const BfmeAudioEventPrefix136 *);
};
class Rva003F7F4BTextView {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual UnicodeString fetch(const AsciiString &,bool *);
};
class Rva003F7F4B {public:void rva003F7F4B();private:
 unsigned char pad[8]; OpaqueRefElement4 info; unsigned int id; AsciiString label; void *owner; unsigned char flag18,flag19;
};
void Rva003F7F4B::rva003F7F4B() {
 if(info.referent && id==1) {
 BfmeEventPositionView position(0,0,0);
 BfmeAudioEventPrefix136 event(info,position,1);
 event.m_int70=((Rva002B2B66*)TheLivingWorldLogic)->rva002B2B66();
 id=((Rva003F7F4BAudioView*)TheAudio)->add(&event);
 }
 if(flag19) ((Rva0029B17C*)TheInGameUI)->rva0029B17C();
 if(!label.isEmpty()) {
 UnicodeString text=((Rva003F7F4BTextView*)TheGameText)->fetch(label,0);
 ((Rva0029B16A*)TheInGameUI)->rva0029B16A((int)&text,1000000);
 }
}
