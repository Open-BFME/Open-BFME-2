// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
// WB15E11C0 assertions306..318 name OnClipLoaded. Native5E9D78..5E9E27
// has RET8 and owns the allocated20B clip through the existing5E971F guard.
// Constructor5E9CC3 forwards level/name to the verified BattlePromptMovieClip
// constructor5FA7EB. Only accessed prefixes and proven call ABIs are modeled.
// BFME1/ZH have no battle-prompt UI donor.
//
// WB15E0680 (assertions 80..84) names PopulateMovieClip: a file-static
// helper retail calls with the battle in ESI and the clip on the stack (the
// whole-program private convention this toolchain gives a static noinline
// function). It builds one 16-byte player record per non-local player of
// every side (image of the faction icon, colour | 0xFF000000, name, and a
// page factory from 0x005E992F / 0x005E9961 by alliance) and adds it to the
// clip. The record's default constructor and its factory-reference
// assignment are ICF-folded retail bodies (0x00063333, 0x002174A4) proven
// by this unit's exact out-of-line copies (fold-proof pins).
namespace StrategicInGameUI { class BattlePromptDialog { public: class Impl; }; }
// ---- the battle-prompt player records (CreateLocalPlayerData / PopulateMovieClip) ----
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
// The 16-byte record's page-factory reference (+0): copied by 0x005F9141,
// released through 0x0007DEEF; its assignment is the ICF-folded 0x002174A4.
struct Rva005F918DHolder00 {
 TargetRef00217D4C *m_ptr;
 Rva005F918DHolder00() : m_ptr(0) {}
 ~Rva005F918DHolder00() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
 __declspec(noinline) Rva005F918DHolder00 &operator=(const Rva005F918DHolder00 &other)
 {
  if (this != &other) {
   if (other.m_ptr) ++other.m_ptr->references;
   if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
   m_ptr = other.m_ptr;
  }
  return *this;
 }
};
struct Rva005F918D {
 Rva005F918DHolder00 m_holder;
 unsigned int m_word4; // image
 unsigned int m_word8; // colour
 UnicodeString m_text0C; // player name
 __declspec(noinline) Rva005F918D() : m_word4(0), m_word8(0) {}
 Rva005F918D(const Rva005F918D &other);
 ~Rva005F918D();
};
struct Rva005F91F3Src;
template <class T> class RvaCloneResult : public Rva005F918DHolder00 {};
class Rva005E9742 { public: struct Payload { int v[6]; }; };
class Rva005E97B8 { public: struct Payload { int v[3]; }; };
class Rva005E982C { public: struct Payload { int v[3]; }; };
RvaCloneResult<Rva005E9742> Rva005E98FDCreate(const Rva005E9742::Payload *src);
RvaCloneResult<Rva005E97B8> Rva005E992FCreate(const Rva005E97B8::Payload *src);
RvaCloneResult<Rva005E982C> Rva005E9961Create(const Rva005E982C::Payload *src);
class Rva005E957C { public: Rva005E957C *rva005E957C(int,int,int,int,int,int); int words[6]; };
class RGBColor { public: float r,g,b; int getAsInt() const; };
class Image;
class ImageCollection { public: const Image *findImageByName(const AsciiString &); };
extern ImageCollection *TheMappedImageCollection;
struct FactionView { char prefix[0x20]; AsciiString icon; };
class Rva002E071E { public: bool rva002E071E(const Rva002E071E *) const; };
struct LivingWorldPlayer {
 char pad00[0x1C]; UnicodeString name; // +0x1C
 char pad20[0x20]; FactionView *faction; // +0x40
 char pad44[0x184-0x44]; RGBColor color; // +0x184
};
class LivingWorldLogic { public: char prefix[0x98]; LivingWorldPlayer *localPlayer; };
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva003F468D { public: int rva003F468D(int side,int index); int rva003F4DAE(int side); };
namespace StrategicHUD {
class BattlePromptMovieClip {
public:
 class Impl;
 BattlePromptMovieClip(int level,const AsciiString &name,const Rva005F91F3Src &ally);
 virtual ~BattlePromptMovieClip();
 void AddAlly(const Rva005F91F3Src &);
 void AddEnemy(const Rva005F91F3Src &);
private:
 Impl *m_impl;
};
}
class Rva0050B5F1 { public: bool rva0050B5F1(int,int); };
class Rva005FA874 { public: Rva005FA874(); ~Rva005FA874() { rva005FA874(); } void rva005FA874(); private: void *m_ptr; };

class Rva005E9625;
class Rva005E971F { public: void rva005E971F(Rva005E9625 *); };
class Rva0020E89C { public: UnicodeString rva0020E89C(); };
struct LivingWorldBattleSide28 { char opaque[0x1C]; };
class LivingWorldBattle {
public:
 int rva003F4752(void *player);
 int rva003F4FAA(int side,void *player);
 int rva003F4FD4();
 int getSideCount() const { return m_sidesEnd-m_sidesBegin; }
 char prefix[0x18];
 LivingWorldBattleSide28 *m_sidesBegin,*m_sidesEnd; // +0x18 / +0x1C
 char pad20[4];
 Rva0020E89C *region; // +0x24
};
class Rva005F9775 { public: void rva005F9775(const UnicodeString &); };
class Rva005F93CB { public: void rva005F93CB(bool); };
class Rva005F93D3 { public: void rva005F93D3(bool); };
class Rva005F93DB { public: void rva005F93DB(bool); };
class StrategicInGameUI::BattlePromptDialog::Impl {
public:
 void OnClipLoaded(int,const AsciiString &);
 void *owner,*frame;
 LivingWorldBattle *battle;
 int first,second,third;
 Rva005E9625 *clip;
};
// The prompt clip: StrategicHUD::BattlePromptMovieClip (+0 vptr, +4 Impl)
// extended with its owning dialog, the StrategicBattlePromptTimer slot and
// a flag; 20 bytes (OnClipLoaded's new), vtable 0x00878078.
class Rva005E9625 : public StrategicHUD::BattlePromptMovieClip {
public:
 Rva005E9625(StrategicInGameUI::BattlePromptDialog::Impl *dialog,int level,const AsciiString &name);
 virtual ~Rva005E9625();
private:
 StrategicInGameUI::BattlePromptDialog::Impl *m_dialog; // +0x08
 Rva005FA874 m_timer; // +0x0C
 bool m_10; // +0x10
};
namespace StrategicInGameUI {
// WB15E01F0 (assertions 49..62): the local player's prompt record. Native
// 0x005E9A5E (236B, cdecl hidden return) is banked: the factory result
// temporary shares the side local's stack slot here (frame 0x34 vs 0x38).
Rva005F918D CreateLocalPlayerData(LivingWorldBattle &battle,int first,int second,int third);

// WB15E0680 (assertions 80..84): one ally or enemy record per other player.
static __declspec(noinline) void PopulateMovieClip(StrategicHUD::BattlePromptMovieClip *clip,LivingWorldBattle &battle)
{
 LivingWorldPlayer *localPlayer=TheLivingWorldLogic->localPlayer;
 for (int side=0; side<battle.getSideCount(); ++side) {
  int count=((Rva003F468D *)&battle)->rva003F4DAE(side);
  for (int i=0; i<count; ++i) {
   LivingWorldPlayer *player=(LivingWorldPlayer *)((Rva003F468D *)&battle)->rva003F468D(side,i);
   if (player==localPlayer) continue;
   FactionView *faction=player->faction;
   Rva005F918D data;
   data.m_word4=(unsigned int)TheMappedImageCollection->findImageByName(faction->icon);
   data.m_word8=(unsigned int)player->color.getAsInt()|0xFF000000;
   data.m_text0C=player->name;
   if (((const Rva002E071E *)player)->rva002E071E((const Rva002E071E *)localPlayer)) {
    Rva005E97B8::Payload payload={{(int)&battle,side,i}};
    data.m_holder=Rva005E992FCreate(&payload);
    clip->AddAlly(*(const Rva005F91F3Src *)&data);
   } else {
    Rva005E982C::Payload payload={{(int)&battle,side,i}};
    data.m_holder=Rva005E9961Create(&payload);
    clip->AddEnemy(*(const Rva005F91F3Src *)&data);
   }
  }
 }
}
}

// Native 0x005E9CC3..0x005E9D78 (RET 0xC): the base gets the local player's
// record, then every other player is added and the timer registration (the
// false-returning ICF stub 0x0050B5F1) runs.
Rva005E9625::Rva005E9625(StrategicInGameUI::BattlePromptDialog::Impl *dialog,int level,const AsciiString &name)
 : StrategicHUD::BattlePromptMovieClip(level,name,*(const Rva005F91F3Src *)&StrategicInGameUI::CreateLocalPlayerData(*dialog->battle,dialog->first,dialog->second,dialog->third)),
   m_dialog(dialog),m_10(true)
{
 StrategicInGameUI::PopulateMovieClip(this,*m_dialog->battle);
 ((Rva0050B5F1 *)&m_timer)->rva0050B5F1(level,(int)&AsciiString("StrategicBattlePromptTimer"));
}

void StrategicInGameUI::BattlePromptDialog::Impl::OnClipLoaded(int level,const AsciiString &name)
{
 ((Rva005E971F *)&clip)->rva005E971F(new Rva005E9625(this,level,name));
 Rva0020E89C *region=battle->region;
 ((Rva005F9775 *)clip)->rva005F9775(region->rva0020E89C());
 unsigned options=(unsigned)battle->rva003F4FD4();
 ((Rva005F93CB *)clip)->rva005F93CB(((options>>1)&1)!=0);
 ((Rva005F93D3 *)clip)->rva005F93D3(((options>>3)&1)!=0);
 ((Rva005F93DB *)clip)->rva005F93DB(((options>>2)&1)!=0);
}
