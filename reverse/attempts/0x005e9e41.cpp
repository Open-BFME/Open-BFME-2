// ??0Impl@BattlePromptDialog@StrategicInGameUI@@QAE@PAXPAVRva0057C394@@PAVLivingWorldBattle@@HHH@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C { TargetRef00217D4C *m_ptr; };
struct DelegateDesc { void *m_object; void *m_method; };
class FunctorTarget {};
typedef void (FunctorTarget::*FunctorMethod)(int,const AsciiString &);
struct FunctorBinding {
 template<class T> FunctorBinding(void (T::*method)(int,const AsciiString &),T *target)
  : m_target(reinterpret_cast<FunctorTarget *>(target)),m_method(reinterpret_cast<FunctorMethod>(method)) {}
 FunctorTarget *m_target;
 FunctorMethod m_method;
};
class Rva00579E47 {
public:
 Rva00579E47(const DelegateDesc &);
 ~Rva00579E47() { if (pointer) ReleaseTreeHintRef00217D4C(pointer); }
 TargetRef00217D4C *pointer;
};
class Rva0057C394 { public: void rva0057C394(const AsciiString &,const TreeHintRef00217D4C &); };
namespace StrategicInGameUI { class BattlePromptDialog { public: class Impl; }; }
class Rva005E9625 { public: Rva005E9625(StrategicInGameUI::BattlePromptDialog::Impl *,int,const AsciiString &); virtual ~Rva005E9625(); char remainder[16]; };
class Rva005E971F { public: void rva005E971F(Rva005E9625 *); void rva005E9705(); };
class Rva0020E89C { public: UnicodeString rva0020E89C(); };
class LivingWorldBattle { public: char prefix[0x24]; Rva0020E89C *region; int rva003F4FD4(); };
struct BattlePromptClipHandle {
 Rva005E9625 *pointer;
 BattlePromptClipHandle() : pointer(0) {}
 ~BattlePromptClipHandle() { ((Rva005E971F *)this)->rva005E9705(); }
};
class StrategicInGameUI::BattlePromptDialog::Impl {
public:
 Impl(void *,Rva0057C394 *,LivingWorldBattle *,int,int,int);
 void OnClipLoaded(int,const AsciiString &);
 void *owner;
 Rva0057C394 *frame;
 LivingWorldBattle *battle;
 int first,second,third;
 BattlePromptClipHandle clip;
 int unknown1C;
};
struct BattlePromptCallbackDesc {
 StrategicInGameUI::BattlePromptDialog::Impl *object;
 void (StrategicInGameUI::BattlePromptDialog::Impl::*method)(int,const AsciiString &);
};
StrategicInGameUI::BattlePromptDialog::Impl::Impl(void *o,Rva0057C394 *f,LivingWorldBattle *b,int a,int c,int d)
 : owner(o),frame(f),battle(b),first(a),second(c),third(d),unknown1C(0)
{
 FunctorBinding desc(&Impl::OnClipLoaded,this);
 Rva00579E47 callback(reinterpret_cast<const DelegateDesc &>(desc));
 frame->rva0057C394(AsciiString("StrategicBattlePrompt.swf"),reinterpret_cast<const TreeHintRef00217D4C &>(callback));
}


