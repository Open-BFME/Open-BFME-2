// ?OnPanelLoaded@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHPBD@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
#include "ascii_string.h"
struct Rva005F4AD7Inner;
struct Rva005F4AD7 {
 Rva005F4AD7Inner *m_ptr;
 Rva005F4AD7(const Rva005F4AD7 &) throw();
 ~Rva005F4AD7();
 Rva005F4AD7 &operator=(const Rva005F4AD7 &);
};
class Rva005F4AED {
public:
 virtual void slot00() = 0;
 virtual Rva005F4AD7 createPanel(int level,const AsciiString &leaf) = 0;
 Rva005F4AD7 rva005F4AED(int level,const AsciiString &leaf);
};
Rva005F4AD7 Rva005F4AED::rva005F4AED(int level,const AsciiString &leaf) {
 const Rva005F4AD7 panel=createPanel(level,leaf);
 return panel;
}
const char *__cdecl Rva00412845AfterLevel(const char *);
int __cdecl Rva004128BBGetLevel(const char *);
struct Rva002BED91 { Rva005F4AED *m_ptr; Rva005F4AED *operator->() const { return m_ptr; } void clear(); };
namespace StrategicHUD {
class ArmyUnitSwapperMovieClip {
public:
 class Impl {
 public:
  void OnPanelLoaded(int slotIndex,const char *path);
 private:
  struct Slot { Rva002BED91 factory; Rva005F4AD7 panel; char remainder[0x10]; };
  char padding[0x1c];
  Slot slots[2];
 };
};
void ArmyUnitSwapperMovieClip::Impl::OnPanelLoaded(int slotIndex,const char *path) {
 Slot &slot=slots[slotIndex];
 if(slot.factory.m_ptr && !slot.panel.m_ptr) {
  {
   AsciiString leaf(Rva00412845AfterLevel(path));
   slot.panel=slot.factory->rva005F4AED(Rva004128BBGetLevel(path),leaf);
  }
  slot.factory.clear();
 }
}
}
