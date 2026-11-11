// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// platformsdk
//
// ??1Rva005CF9FF@@UAE@XZ @0x005CF9FF 68B, ??1Rva005CFA43@@UAE@XZ @0x005CFA43
// 68B and ??1Rva005CFA87@@UAE@XZ @0x005CFA87 68B: three sibling dtors,
// identical but for their own vtables 0x00C752CC, 0x00C752D4 and 0x00C752DC
// (callers: the rowed ??_G wrappers 0x005CFDDC, 0x005CFDF8, 0x005CFE14).
// Each stores its vtable; when its flag byte (+0x10, +0x08 and +0x0C respectively) is set and the global
// at VA 0x00E05FAC is non-null, calls the pinned Rva0054CBEFTarget::method
// 0x0054CBEF on it with 0 (the same gated call, with 1, as the rowed
// ??1Rva004FBCBE, whose (int)AptStrategicMessageBox::s_instance spelling is reused); then the inline
// base dtor resets to 0x00C75290 (Rva005CF872, as in Rva005CFDA6Dtor.cpp).
// Identities unproven; address-derived names.

#include "ascii_string.h"
#include "unicode_string.h"
#include <windows.h>
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../Include/Common/Rva0054D3E1Prompt.h"
#include "../../Include/Common/Rva0054D2DDTarget.h"
#include "../../Include/Common/Rva0054CBEFTarget.h"

class AptStrategicMessageBox {private: static AptStrategicMessageBox *s_instance; friend class Rva005CF9FF; friend class Rva005CFA43; friend class Rva005CFA87;};

class Rva005CF872
{
public:
	Rva005CF872(void *owner):m_04((int)owner) {}
	virtual ~Rva005CF872() {}
	virtual void Update() {}	// retail 0x00C75290 slot 1, the shared empty body

private:
	int m_04;
};

class Rva005CF9FF : public Rva005CF872
{
public:
	Rva005CF9FF(void*,int,int,bool);
 virtual ~Rva005CF9FF();
	virtual void Update();	// 0x005D0EB8

private:
	int m_08;
	int m_0C;
	bool m_flag;
};

Rva005CF9FF::~Rva005CF9FF()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

class Rva005CFA43 : public Rva005CF872
{
public:
	Rva005CFA43(void*,int,bool);
 virtual ~Rva005CFA43();	// retail 0x00C752D4 keeps the base Update

private:
	bool m_flag;
};

Rva005CFA43::~Rva005CFA43()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

class Rva005CFA87 : public Rva005CF872
{
public:
	Rva005CFA87(void *owner, bool change);
	virtual ~Rva005CFA87();
	virtual void Update();	// 0x005CFE30

private:
	int m_08;
	bool m_flag;
};

Rva005CFA87::~Rva005CFA87()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}


// Native187B5D044C..5D0507; WB15B9220 names the ShowAllEnemiesRetreated
// state constructor with the two identical strategic text labels. Existing
// dtor-owned Rva005CFA87 spelling preserved; boolC and timestamp8 target-read.
Rva005CFA87::Rva005CFA87(void*o,bool change):Rva005CF872(o),m_08(timeGetTime()),m_flag(change) {
 AptStrategicMessageBox *prompt=AptStrategicMessageBox::s_instance;
 if(prompt){
  UnicodeString title=TheGameText->fetch("STRATEGICHUD:AllEnemiesRetreatedTitle",0);
  UnicodeString text=TheGameText->fetch("STRATEGICHUD:AllEnemiesRetreatedMessage",0);
  if(change) ((Rva0054D3E1Prompt*)prompt)->configure(4,title,text);
  else ((Rva0054D2DDTarget*)prompt)->method(4,title,text);
  m_flag=true;
 }
}

class LivingWorldLogic;extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
UnicodeString GetBattleTypeSelectedMessage(int);
namespace StrategicInGameUI { UnicodeString GetDefaultStartingBattleMessage(int); }
// WB15B8920 names GetStartingBattleMessage. Native354B5D015C through5D02BE
// keeps two user inputs in ECX/EDX and hidden Unicode output on the stack.
// A TU-local static definition with both callers below lets MSVC infer that
// internal ABI; explicit __fastcall puts the hidden output first and fails.
namespace StrategicInGameUI {
static UnicodeString GetStartingBattleMessage(int opponent,int chosen) {
 if(opponent==chosen||(opponent!=1&&opponent!=3)) return StrategicInGameUI::GetDefaultStartingBattleMessage(chosen);
 bool exists;
 UnicodeString mismatch=TheGameText->fetch("STRATEGICHUD:OpponentSelectionIsDifferent",&exists);
 if(!exists)return StrategicInGameUI::GetDefaultStartingBattleMessage(chosen);
 UnicodeString priority=TheGameText->fetch(chosen==1?"STRATEGICHUD:BattlePriorityAutoResolve":"STRATEGICHUD:BattlePriorityRTS",0);
 UnicodeString result;
 result.format(mismatch.str(),GetBattleTypeSelectedMessage(opponent).str(),priority.str(),StrategicInGameUI::GetDefaultStartingBattleMessage(chosen).str());
 return result;
}
}
// Native206B5D02BE through5D038C; state field8 stored from argument2,
// timestampC and bool10 independently read by the rowed dtor; vtableC752CC.
Rva005CF9FF::Rva005CF9FF(void*owner,int data,int opponent,bool change):Rva005CF872(owner),m_08(data),m_0C(timeGetTime()),m_flag(change) {
 if(((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false)>1){
  AptStrategicMessageBox *prompt=AptStrategicMessageBox::s_instance;
  if(prompt){
   UnicodeString title=TheGameText->fetch("STRATEGICHUD:StartingBattleTitle",0);
   UnicodeString text=StrategicInGameUI::GetStartingBattleMessage(opponent,1);
   if(change)((Rva0054D3E1Prompt*)prompt)->configure(4,title,text);
   else((Rva0054D2DDTarget*)prompt)->method(4,title,text);
   m_flag=true;
  }
 }
}
// Native192B5D038C through5D044C; bool8 and vtableC752D4 tie this ctor
// to the existing dtor; selected message kind3 is target-measured.
Rva005CFA43::Rva005CFA43(void*owner,int opponent,bool change):Rva005CF872(owner),m_flag(change) {
 if(((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false)>1){
  AptStrategicMessageBox *prompt=AptStrategicMessageBox::s_instance;
  if(prompt){
   UnicodeString title=TheGameText->fetch("STRATEGICHUD:StartingBattleTitle",0);
   UnicodeString text=StrategicInGameUI::GetStartingBattleMessage(opponent,3);
   if(change)((Rva0054D3E1Prompt*)prompt)->configure(4,title,text);
   else((Rva0054D2DDTarget*)prompt)->method(4,title,text);
   m_flag=true;
  }
 }
}
