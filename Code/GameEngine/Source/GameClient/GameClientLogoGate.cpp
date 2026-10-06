// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native 0x00239539..0x0023958B, complete 82B cdecl callback.
// Target: callback address stored by 0x0023BF5B; unused context word and
// byte-tested second argument; state values 5/7; EALogoMovie string temporary.
// Existing matched DIR32 sites establish TheGameEngine (DFE710),
// TheWritableGlobalData (DFE758), and TheDisplay (DFE9D8). The slot offsets
// 0x5C/0x10C and flag +0xAF2 come from this target body. Slot names, parameter
// labels, complete layouts and original callback name remain unknown.
// ZH GameClient.cpp supplies a logo-playback semantic lead, not target
// identity: BFME2 uses arguments 0/8 and this callback shape rather than its
// update() branch. The explicit views avoid defining private engine classes.
#include "ascii_string.h"
class GameEngine;
class Rva00239539EngineSlots { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
};
extern GameEngine *TheGameEngine;
class GlobalData;
struct Rva00239539Flags { char prefix[0xAF2]; unsigned char flagAF2; };
extern GlobalData *TheWritableGlobalData;
class Display;
class Rva00239539DisplaySlots { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67(AsciiString movie, int first, int second);
};
extern Display *TheDisplay;
int __cdecl rva00239539(void *, bool allowIntro) {
 int result=5;
 reinterpret_cast<Rva00239539EngineSlots *>(TheGameEngine)->slot23();
 if (allowIntro) {
  if (reinterpret_cast<Rva00239539Flags *>(TheWritableGlobalData)->flagAF2) reinterpret_cast<Rva00239539DisplaySlots *>(TheDisplay)->slot67(AsciiString("EALogoMovie"),0,8);
 } else result=7;
 return result;
}
