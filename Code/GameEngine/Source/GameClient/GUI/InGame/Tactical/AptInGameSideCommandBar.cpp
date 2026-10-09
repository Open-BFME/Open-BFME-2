// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WorldBuilder 013C8490 names Impl::OnButtonFrameLoaded; retail
// 005283F8..00528545 parses index/name and binds the movie in its slot.
// Native constructor 005288C4 initializes fifteen 12-byte slots at +24;
// this callback retains retail's inclusive index check (0 through 15).
// The callback reads state +14, constructs the existing sixteen-byte
// Rva005C31FB level/name view, and assigns through rowed 00575674.
// No original identity is claimed for the address-derived movie class.
#include "ascii_string.h"
#include <stdlib.h>
bool __cdecl Rva004128F0GetParam(const char *, const char *, AsciiString &);
namespace AptUtils {
const char *__cdecl SkipLevelN(const char *);
int __cdecl LevelIndexFromTarget(const char *);
}
class Rva000AD6F4 {
public:
 Rva000AD6F4(): m_ptr(0) {}
 ~Rva000AD6F4() { clear(); }
 void clear();
 void *m_ptr;
};
class Rva00528309 { public: void rva005283E3(); };
class Object;
class Rva00575674 {
public:
 void rva00575674(Object *);
 void *m_button;
 void *m_updater;
 int m_key;
};
class Rva005C31FB {
public:
 virtual ~Rva005C31FB();
 Rva005C31FB(int, const AsciiString &);
private:
 int m_level;
 AsciiString m_name;
 bool m_flag0C;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct SideBarUpdaterRef {
 SideBarUpdaterRef():m_ptr(0){}
 ~SideBarUpdaterRef() { if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
 void *m_ptr;
};
// The template is a source storage view, not an original retail type claim.
// Native57B528281..5282BA destroys counted updater4 then owning frame0.
template<class FrameHolder, class UpdaterHolder> struct SideBarButtonSlot {
 SideBarButtonSlot():m_key(-1){}
 ~SideBarButtonSlot(){}
 FrameHolder m_button;
 UpdaterHolder m_updater;
 int m_key;
};
template struct SideBarButtonSlot<Rva000AD6F4, SideBarUpdaterRef>;
typedef SideBarButtonSlot<Rva000AD6F4, SideBarUpdaterRef> SideBarSlot;

class AptInGameSideCommandBar {
public:
 class Impl {
 public:
  void Update();
  void OnButtonFrameLoaded(const char *params);
  void OnButtonFrameUnloaded(const char *params);
  void HideButtons(int);
  void OnFadeInComplete(const char *params);
  void OnFadeOutComplete(const char *params);
  void OnLoaded(const char *params);
  void OnUnloaded(const char *params);
 private:
  char m_prefix[0x14];
  int m_state;
  AsciiString m_prefixString; // +18, assigned by loaded callback
  unsigned m_selectedObject; // +1c, measured in Impl::Update
  unsigned m_displayedObject; // +20 as measured in Impl::Update
  SideBarSlot m_buttons[15];
  int m_count;
 };
 void Update();
private:
 Impl *impl;
};
void AptInGameSideCommandBar::Impl::OnButtonFrameLoaded(const char *params)
{
 if (!m_state) return;
 AsciiString indexText;
 if (!Rva004128F0GetParam(params, "index", indexText)) return;
 int index = atoi(indexText.str());
 if (index < 0 || index > 15) return;
 Rva00575674 *slot = (Rva00575674 *)&m_buttons[index];
 if (slot->m_button) return;
 AsciiString name;
 if (!Rva004128F0GetParam(params, "name", name)) return;
 slot->rva00575674((Object *)new Rva005C31FB(
  AptUtils::LevelIndexFromTarget(name.str()),
  AsciiString(AptUtils::SkipLevelN(name.str()))));
}

// Native 005288BD..005288C4 delegates through the owner pointer at +0.
// The public Update identity follows the proven Impl::Update tail call;
// WorldBuilder does not retain this seven-byte wrapper as a named body.
void AptInGameSideCommandBar::Update() { impl->Update(); }

// Native 00528738..005287D0 parses the slot, hides buttons from that
// index onwards, then clears the movie holder. Constructor 005288C4 binds
// this exact address to OnAptInGameSideCommandBarButtonFrameUnloaded.
// The method spelling describes that binding; WB keeps this body unnamed.
void AptInGameSideCommandBar::Impl::OnButtonFrameUnloaded(const char *params)
{
 if (!m_state) return;
 AsciiString indexText;
 if (!Rva004128F0GetParam(params, "index", indexText)) return;
 int index = atoi(indexText.str());
 if (index < 0 || index > 15) return;
 HideButtons(index);
 ((Rva000AD6F4 *)&m_buttons[index])->clear();
}

// Constructor 005288C4 binds 00528240 to
// OnAptInGameSideCommandBarFadeInComplete. The entire 16-byte body ends
// in ret4 immediately before 00528250. The spelling describes the binding;
// it is not a recovered WB method name. The unused string argument follows
// the same registered callback ABI as the two frame callbacks.
void AptInGameSideCommandBar::Impl::OnFadeInComplete(const char *)
{
 if (m_state == 2) m_state = 3;
}

// Constructor 005288C4 binds 00528250 to
// OnAptInGameSideCommandBarFadeOutComplete; all 20 bytes end at 00528264.
// With state4, forget the displayed object at +20 and return to state1.
// As above, the method spelling describes the callback binding.
void AptInGameSideCommandBar::Impl::OnFadeOutComplete(const char *)
{
 if (m_state == 4) {
  m_displayedObject = 0;
  m_state = 1;
 }
}

// Constructor 005288C4 binds 005283C9 to
// OnAptInGameSideCommandBarLoaded. Complete26B body calls the existing
// StringBase set(text) worker on +18 and sets state14 to1, ending at5283E3.
// The callback spelling describes the binding, not a retained WB name.
void AptInGameSideCommandBar::Impl::OnLoaded(const char *params)
{
 m_prefixString = params;
 m_state = 1;
}

// Constructor 005288C4 binds 005285E7 to the Unloaded callback.
// Entire eight-byte body calls the already rowed 5283E3 cleanup then ret4.
void AptInGameSideCommandBar::Impl::OnUnloaded(const char *)
{
 ((Rva00528309 *)this)->rva005283E3();
}
