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
class Rva000AD6F4 { public: void clear(); };
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
class AptInGameSideCommandBar {
public:
 class Impl {
 public:
  void Update();
  void OnButtonFrameLoaded(const char *params);
  void OnButtonFrameUnloaded(const char *params);
  void HideButtons(int);
 private:
  char m_prefix[0x14];
  int m_state;
  char m_middle[0xc];
  Rva00575674 m_buttons[15];
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
 Rva00575674 *slot = &m_buttons[index];
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
