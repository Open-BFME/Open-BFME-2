// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
// WB15E11C0 assertions306..318 name OnClipLoaded. Native5E9D78..5E9E27
// has RET8 and owns the allocated20B clip through the existing5E971F guard.
// Constructor5E9CC3 forwards level/name to the verified BattlePromptMovieClip
// constructor5FA7EB. Only accessed prefixes and proven call ABIs are modeled.
// BFME1/ZH have no battle-prompt UI donor. Other file bodies are banked or
// blocked on their recorded stack scheduling and whole-program ABI issues.
namespace StrategicInGameUI { class BattlePromptDialog { public: class Impl; }; }
class Rva005E9625 {
public:
 Rva005E9625(StrategicInGameUI::BattlePromptDialog::Impl *,int,const AsciiString &);
 virtual ~Rva005E9625();
 char remainder[16];
};
class Rva005E971F { public: void rva005E971F(Rva005E9625 *); };
class Rva0020E89C { public: UnicodeString rva0020E89C(); };
class LivingWorldBattle { public: char prefix[0x24]; Rva0020E89C *region; int rva003F4FD4(); };
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
