// ?rva00420254@VictoryConditions@@QAEXABVAsciiString@@_N00@Z
// partial score=0.9 date=2026-10-10
// cl: /O1 /Ob2 /G7 /arch:SSE /EHs /MD /Ireference/shims/bfme2_ascii
// ??1VictoryConditions@@UAE@XZ, retail 0x004201FA, 62 bytes. Derived dtor of
// VictoryConditions over Rva0041FE0E over SubsystemInterface: installs derived
// vtable 0x00C3BA28 then calls rowed this->rva00420110 0x00420110 then
// installs base vtable 0x00C3B988 via inlined base dtor then calls rowed
// SubsystemInterface dtor 0x001B4E74 with __EH_prolog 0x00629188.
// Evidence: sole caller deleting-dtor 0x00420238 calls this; callee 0x00420110
// takes same this; base ctor 0x0041FDF8 sets vtable 0x00C3B988 and caller
// 0x0042017F overwrites to 0x00C3BA28; layout +0x10/+0x85 matches neighbours.

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).

#include "ascii_string.h"
#include "unicode_string.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class Rva0041FE0E : public SubsystemInterface
{
public:
	Rva0041FE0E();
	virtual ~Rva0041FE0E();
	char m_pad04[8];
	int m_0C;
};

inline Rva0041FE0E::~Rva0041FE0E()
{
}

class VictoryConditions : public Rva0041FE0E
{
public:
	VictoryConditions();
    virtual ~VictoryConditions();
    void rva00420110();
    void rva00420254(const AsciiString &,bool,const AsciiString &,const AsciiString &);
private:
    bool m_endGameShowing; // +10
    unsigned m_endGameShowTime; // +14
    char m_state18[0x8c-0x18];
    int m_field8C;
    bool m_field90;
    bool m_field91;
};

VictoryConditions::~VictoryConditions()
{
	rva00420110();
}

class Rva0041FE86 { public: void rva0041FE86(); };
VictoryConditions::VictoryConditions()
{
    m_endGameShowing = false;
    m_endGameShowTime = 0;
    m_field8C = 0;
    m_field90 = false;
    m_field91 = false;
    ((Rva0041FE86 *)this)->rva0041FE86();
}
typedef char NativeVictorySize[sizeof(VictoryConditions)==0x94 ? 1 : -1];

// Constructor identity: WorldBuilder identifies the C3BA28 family as
// VictoryConditions; native GameEngine init registers factory420353 as
// TheVictoryConditions. Native base ctor41FDF8 and reset41FE86 are matched.
// BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 VictoryConditions.cpp
// supplies the construct-then-reset subsystem pattern, while all offsets and
// pre-reset stores above come from BFME2's 79-byte body. +8C/+90/+91 meanings
// remain unknown. Native factory allocation and field extent prove size94.

class VictoryConditionsInterface;
VictoryConditionsInterface *Rva00420353CreateVictoryConditions()
{ return (VictoryConditionsInterface *)new VictoryConditions; }

class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
class Rva00222A8BTarget {public:int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);};
extern "C" void *g_pRva00224BC9;
class GameTextInterface;extern GameTextInterface *TheGameText;
class VictoryTextPrefix {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();
 virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();
 virtual void slot12();virtual void slot13();
 virtual UnicodeString fetchName(const AsciiString *,bool *);
};
class Display;extern Display *TheDisplay;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
// BF1 575ba2 VictoryConditionsUpdate supplies the four-argument banner ABI
// and state/timer guide; native420254..420353 proves BF2's fields10/14,
// key/text temporary lifetimes, slot14 and literal arguments independently.
// Original UI slot name inferred from ShowEndGame string, not source identity.
void VictoryConditions::rva00420254(const AsciiString &label,bool defeat,const AsciiString &name,const AsciiString &extra)
{
 if(g_pRva00224BC9 && !m_endGameShowing) {
  { AsciiString key(":VictoryDefeat");
    UnicodeString text=((VictoryTextPrefix *)TheGameText)->fetchName(&label,0);
    ((BfmeAptWindowManager *)g_pRva00224BC9)->bfmeSetText(key,text,false); }
  const char *suffix;
  if (!extra.isEmpty()) suffix=extra.str();
  else suffix="";
  const char *state=defeat?"0":"1";
  ((Rva00222A8BTarget *)g_pRva00224BC9)->invoke((void *)13,"ShowEndGame",3,state,(void *)name.str(),(void *)suffix,0,0);
  m_endGameShowing=true;
  m_endGameShowTime=timeGetTime();
  *(bool *)((char *)TheDisplay+0x140)=false;
 }
}
