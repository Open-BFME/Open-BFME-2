// ?rva00420254@VictoryConditions@@QAEXABVAsciiString@@_N00@Z
// cl: /O1 /EHsc /MD /arch:SSE /GF- /Ireference/shims/bfme2_ascii
// platformsdk
// d3 seat6 w2: /GF- (two "" uses compiled as separate literals: suffix stays in ECX,
// state in EDI as retail) + the fetchName result passed as a temporary, equal-arm
// name.str() hack removed: 254/255, only residue is cl packing the UnicodeString
// temporary into the dead label home [ebp+8] where retail gives it its own slot [ebp-0x14].
// ??1VictoryConditions@@UAE@XZ, retail 0x004201FA, 62 bytes. Derived dtor of
// VictoryConditions over Rva0041FE0E over SubsystemInterface: installs derived
// vtable 0x00C3BA28 then calls rowed this->rva00420110 0x00420110 then
// installs base vtable 0x00C3B988 via inlined base dtor then calls rowed
// SubsystemInterface dtor 0x001B4E74 with __EH_prolog 0x00629188.
// Evidence: sole caller deleting-dtor 0x00420238 calls this; callee 0x00420110
// takes same this; base ctor 0x0041FDF8 sets vtable 0x00C3B988 and caller
// 0x0042017F overwrites to 0x00C3BA28; layout +0x10/+0x85 matches neighbours.

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).

#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "../../Include/GameLogic/VictoryConditionsClass.h"

inline Rva0041FE0E::~Rva0041FE0E()
{
}


// VictoryConditions::~VictoryConditions is rowed in its home unit; this copy was a duplicate definition.

// VictoryConditions::VictoryConditions is rowed in its home unit; this copy was a duplicate definition.
typedef char NativeVictorySize[sizeof(VictoryConditions)==0x94 ? 1 : -1];

// Constructor identity: WorldBuilder identifies the C3BA28 family as
// VictoryConditions; native GameEngine init registers factory420353 as
// TheVictoryConditions. Native base ctor41FDF8 and reset41FE86 are matched.
// BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 VictoryConditions.cpp
// supplies the construct-then-reset subsystem pattern, while all offsets and
// pre-reset stores above come from BFME2's 79-byte body. +8C/+90/+91 meanings
// remain unknown. Native factory allocation and field extent prove size94.

class VictoryConditionsInterface;
// ?Rva00420353CreateVictoryConditions@@YAPAVVictoryConditionsInterface@@XZ is rowed in its own unit; this copy collided with it.

class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
#include "../../Include/Common/Rva00222A8BTarget.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameTextInterface;extern GameTextInterface *TheGameText;
class VictoryTextPrefix {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();
 virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();
 virtual void slot12();virtual void slot13();
 virtual UnicodeString fetchName(const AsciiString *,bool *);
};
class Display;extern Display *TheDisplay;
// BF1 575ba2 VictoryConditionsUpdate supplies the four-argument banner ABI
// and state/timer guide; native420254..420353 proves BF2's fields10/14,
// key/text temporary lifetimes, slot14 and literal arguments independently.
// Original UI slot name inferred from ShowEndGame string, not source identity.
void VictoryConditions::rva00420254(const AsciiString &label,bool defeat,const AsciiString &name,const AsciiString &extra)
{
 switch (1) { case 1: if(!g_bfmeAptWindowManager || m_10) break;
 { AsciiString key(":VictoryDefeat");
      ((BfmeAptWindowManager *)g_bfmeAptWindowManager)->bfmeSetText(key,((VictoryTextPrefix *)TheGameText)->fetchName(&label,0),false); }
 const char *suffix;
 if (!extra.isEmpty()) suffix=extra.str();
 else suffix="";
 ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke((void *)13,"ShowEndGame",3,defeat?"0":"1",(void *)name.str(),(void *)suffix,0,0);
  m_10=true;
  unsigned long t = (true ? timeGetTime() : timeGetTime());
  m_14=t;
  *(bool *)((char *)TheDisplay+0x140)=false;
 }
}
