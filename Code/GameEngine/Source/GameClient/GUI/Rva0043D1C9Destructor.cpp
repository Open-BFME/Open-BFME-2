// cl: /O1 /Ob2 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// BFME1 donor6583b3c1ff21db4a561285717028fdafc780b7db:
// Screen teardown primary semantic source is
// game/GameEngine/Source/GameClient/GUI/BfmeAptScreenSpellStoreDestructor.cpp.
// Target43D1C9..43D34F/390B and rowed wrapper43D3BE/vtableC3D7F8#0 prove
// the destructor. Target literal SpellStore/Buttons/Spell%d supports donor
// subsystem; target loop has20 entries at2A8 vs donor12 at260. Target adds
// the mode/pause check and a pointer vector at27C; original pointer payload
// and final ControlBar call's original method name remain unproven.
// Full target54B member43D193 consumes24B at288 with ScienceType vector+8.
// All native named globals use their ledger definitions. Derived vptrs sit
// at0/218. Unknown fields stay opaque; no whole application class is claimed.
// Target539A65/5774 receives ECX=TheControlBar and three stack words (pointer
// and literal1/0), returns a scalar in EAX and RET12. This address-derived
// call declaration models that witnessed ABI; callee implementation remains
// a separate recovery/link dependency. All other call providers are existing
// rows except the older pinned Shell hide35BF4C dependency.
// The base donor supplies the two-base/string layout described below.
// game/GameEngine/Source/GameClient/GUI/Rva00465430AptGameWindowDestructor.cpp.
// Donor supplies the two-base/string teardown structure. Target5126F5/90B
// independently installs C659E8/C659E4 at0/218; releases string270 through
// full133B36410; calls full111B5248D0 on the secondary base and full184B
// GameWindow314A0C on the primary base. The target secondary prefix is58B
// rather than the donor's34B, so its string is270 rather than24C.
// Existing APT screen destructor pins use this ABI spelling; the original
// target class name and fields beyond the consumed prefix remain unproven.
// All three providers are independently full-byte verified. The shared
// BFME2 AsciiString header deliberately supplies target36410 teardown.
class GameWindow {
public: GameWindow(); // call-only default ctor: keep the shared census provider
protected: virtual ~GameWindow();
private: unsigned char unknown[0x218-4];
};
class Rva005248D0 {
public: virtual ~Rva005248D0();
private: unsigned char unknown[0x58-4];
};
#include "ascii_string.h"
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: virtual ~_bfme_AptGameWindow();
private: AsciiString filename270;
};

// stlport
#include <vector>
// Opaque pointer tag isolates this vector's target-proven throwing game-pool
// deallocation from the shared vector<void*> implementation. No pointee size
// or original type is asserted. Its natural range erase independently matches
// the complete34B provider31BD55 before the call-only alias below is used.
struct Rva0043D1C9Entry;
void Rva00030830FreeAllocation(void*);
namespace _STL {template<> Rva0043D1C9Entry**vector<Rva0043D1C9Entry*>::erase(Rva0043D1C9Entry**,Rva0043D1C9Entry**);// ?allocator<Rva0043D1C9Entry*>::deallocate present-unmatched
template<> inline void allocator<Rva0043D1C9Entry*>::deallocate(Rva0043D1C9Entry**p,unsigned int)const {if(p)::Rva00030830FreeAllocation(p);}}
enum ScienceType { SCIENCE_INVALID=0 };
class Rva0043D193Base {
public: virtual void f0()=0;virtual void f1()=0;virtual void f2()=0;
// ?Rva0043D193Base::~Rva0043D193Base present-unmatched
~Rva0043D193Base() {}
};
class __declspec(novtable) Rva0043D193:public Rva0043D193Base {
public: ~Rva0043D193();virtual void f0();virtual void f1();virtual void f2();
private: int unknown4;_STL::vector<ScienceType> sciences;int unknown14;
};

class Rva00223A94 {public:int rva00223A94(const AsciiString*);};
class Rva00222A8BTarget {public:void rva00222F55(bool);};
extern Rva00222A8BTarget* TheRva00222A8BTarget;
class Shell {public:void hide(bool);};extern Shell* TheShell;
class GameLogic {public:bool isInMultiplayerGame();void rva0023CD9E(bool,int,bool);char unknown[0x110];int mode;};extern GameLogic* TheGameLogic;
class ControlBar {public:int rva00539A65(void*,int,int);};extern ControlBar* TheControlBar;
class InGameUI;extern InGameUI* TheInGameUI;
class Rva0043D1C9UI {
public:
virtual void slot00()=0;
virtual void slot01()=0;
virtual void slot02()=0;
virtual void slot03()=0;
virtual void slot04()=0;
virtual void slot05()=0;
virtual void slot06()=0;
virtual void slot07()=0;
virtual void slot08()=0;
virtual void slot09()=0;
virtual void slot10()=0;
virtual void slot11()=0;
virtual void slot12()=0;
virtual void slot13()=0;
virtual void slot14()=0;
virtual void slot15()=0;
virtual void slot16()=0;
virtual void slot17()=0;
virtual void slot18()=0;
virtual void slot19()=0;
virtual void slot20()=0;
virtual void slot21()=0;
virtual void slot22()=0;
virtual void slot23()=0;
virtual void slot24()=0;
virtual void slot25()=0;
virtual void slot26()=0;
virtual void slot27()=0;
virtual void slot28()=0;
virtual void slot29()=0;
virtual void slot30()=0;
virtual void slot31()=0;
virtual void slot32()=0;
virtual void slot33()=0;
virtual void slot34()=0;
virtual void slot35()=0;
virtual void slot36()=0;
virtual void slot37()=0;
virtual void slot38()=0;
virtual void slot39()=0;
virtual void slot40()=0;
virtual void slot41()=0;
virtual void slot42()=0;
virtual void slot43()=0;
virtual void slot44()=0;
virtual void slot45()=0;
virtual void slot46()=0;
virtual void slot47()=0;
virtual void slot48()=0;
virtual void slot49()=0;
virtual void slot50()=0;
virtual void slot51()=0;
virtual void slot52()=0;
virtual void slot53()=0;
virtual void slot54()=0;
virtual void slot55()=0;
virtual void slot56()=0;
virtual void slot57()=0;
virtual void slot58()=0;
virtual void slot59()=0;
virtual void slot60()=0;
virtual void slot61()=0;
virtual void slot62()=0;
virtual void slot63()=0;
virtual void slot64()=0;
virtual void slot65()=0;
virtual void slot66()=0;
virtual void slot67()=0;
virtual void slot68()=0;
virtual void slot69()=0;
virtual void slot70()=0;
virtual void slot71()=0;
virtual void slot72()=0;
virtual void slot73()=0;
virtual void slot74()=0;
virtual void slot75()=0;
virtual void slot76()=0;
virtual void slot77()=0;
virtual void slot78()=0;
virtual void slot79()=0;
virtual void slot80()=0;
virtual void slot81()=0;
virtual void slot82()=0;
virtual void slot83()=0;
virtual void slot84()=0;
virtual void slot85()=0;
virtual void slot86()=0;
virtual void slot87()=0;
virtual void slot88()=0;
virtual void slot89()=0;
virtual void slot90()=0;
virtual void slot91()=0;
virtual void slot92()=0;
virtual void slot93()=0;
virtual void slot94(int)=0;
};
extern int g_Va00E03314;

class Rva0043D1C9:public _bfme_AptGameWindow {
public:virtual ~Rva0043D1C9();
private:
 char unknown274[8];
 _STL::vector<Rva0043D1C9Entry*> entries27C;
 Rva0043D193 sciences288;
 char unknown2A0[3];bool hidden2A3;
 int unknown2A4;
 struct Pair {int first;int second;} buttons2A8[20];
};
Rva0043D1C9::~Rva0043D1C9() {
 int zero=0;
 Rva0043D1C9UI*ui=reinterpret_cast<Rva0043D1C9UI*>(TheInGameUI);
 if(ui)ui->slot94(zero);
 if(TheRva00222A8BTarget) {
  for(int index=0;index<20;++index)if(buttons2A8[index].first) {
   AsciiString name;name.format("SpellStore/Buttons/Spell%d",index+1);
   reinterpret_cast<Rva00223A94*>(TheRva00222A8BTarget)->rva00223A94(&name);
  }
  if(hidden2A3==zero){TheRva00222A8BTarget->rva00222F55(false);hidden2A3=true;}
 }
 if(TheShell)TheShell->hide(false);
 GameLogic*logic=TheGameLogic;
 if(logic && !logic->isInMultiplayerGame() && logic->mode!=6)logic->rva0023CD9E(false,0,true);
 if(TheControlBar && !entries27C.empty()) {
  int count=entries27C.size();
  for(int i=0;i<count;++i){void*entry=entries27C[i];if(entry)TheControlBar->rva00539A65(entry,1,0);}
  entries27C.clear();
 }
 g_Va00E03314=0;
}
#pragma comment(linker,"/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")


#pragma comment(linker,"/alternatename:?erase@?$vector@PAURva0043D1C9Entry@@V?$allocator@PAURva0043D1C9Entry@@@_STL@@@_STL@@QAEPAPAURva0043D1C9Entry@@PAPAU3@0@Z=?erase@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXPAPAX0@Z")
