// ?CreateLocalPlayerData@StrategicInGameUI@@SA?AURva005F918D@@AAVLivingWorldBattle@@HHH@Z
// partial score=0.91 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHs /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned int); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005F918DHolder00 {
 TargetRef00217D4C *m_ptr;
 Rva005F918DHolder00() : m_ptr(0) {}
 ~Rva005F918DHolder00() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva005F918D {
 Rva005F918DHolder00 m_holder;
 unsigned m_word4,m_word8;
 UnicodeString m_text0C;
 __declspec(noinline) Rva005F918D() : m_word4(0),m_word8(0) {}
 Rva005F918D(const Rva005F918D &);
 ~Rva005F918D();
};
class AptCommandMap;
template<class T> class AptRef { public: AptRef &operator=(const AptRef &); };
class Rva005E9742 { public: struct Payload { int v[6]; }; };
template<class T> class RvaCloneResult {
public:
 TargetRef00217D4C *pointer;
 RvaCloneResult(const RvaCloneResult &other) : pointer(other.pointer) { if (pointer) ++pointer->references; }
 ~RvaCloneResult() { if (pointer) ReleaseTreeHintRef00217D4C(pointer); }
};
RvaCloneResult<Rva005E9742> Rva005E98FDCreate(const Rva005E9742::Payload *);
class Rva005E957C { public: Rva005E957C *rva005E957C(int,int,int,int,int,int); int words[6]; };
class RGBColor { public: float r,g,b; int getAsInt() const; };
class FactionView { public: char prefix[0x20]; AsciiString icon; };
class LivingWorldPlayer { public: char pad00[0x1C]; UnicodeString name; char pad20[0x20]; FactionView *faction; char pad44[0x184-0x44]; RGBColor color; };
class LivingWorldLogic { public: char prefix[0x98]; LivingWorldPlayer *localPlayer; };
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldBattle { public: int rva003F4752(void *); int rva003F4FAA(int,void *); };
class Image;
class ImageCollection { public: const Image *findImageByName(const AsciiString &); };
extern ImageCollection *TheMappedImageCollection;
class StrategicInGameUI {
public:
 static Rva005F918D CreateLocalPlayerData(LivingWorldBattle &,int,int,int);
};
Rva005F918D StrategicInGameUI::CreateLocalPlayerData(LivingWorldBattle &battle,int first,int second,int third)
{
 LivingWorldPlayer *player=TheLivingWorldLogic->localPlayer;
 int side=battle.rva003F4752(player);
 int index=battle.rva003F4FAA(side,player);
 FactionView *faction=player->faction;
 Rva005F918D result;
 result.m_word4=(unsigned)TheMappedImageCollection->findImageByName(faction->icon);
 result.m_word8=(unsigned)player->color.getAsInt()|0xFF000000;
 result.m_text0C=player->name;
 Rva005E957C payload;
 payload.rva005E957C((int)&battle,side,index,first,second,third);
 *((AptRef<AptCommandMap> *)&result.m_holder)=reinterpret_cast<const AptRef<AptCommandMap> &>(Rva005E98FDCreate((const Rva005E9742::Payload *)&payload));
 return result;
}

