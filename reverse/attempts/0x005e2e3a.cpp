// ?SetPageEnabled@Impl@RegionDetailsMovieClip@StrategicHUD@@QAEXH_N@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Native5E2E3A..5E2E91 RET8. WB15F4D00 SetPageEnabled, its SetTabEnabled
// literal, and rowed sibling ShowPage/HidePage support this field/call view.
// Only receiver+4 level, +8 string and +30 flags are read here; the padding
// is unread and does not establish the missing members' types.
// The complete32B lookup is included so MSVC can witness EDX preservation;
// it already lives in StrategicHUDRegionDetailsMovieClip.cpp. Copy only the
// new method there when this caller becomes exact; do not add a second owner.
// This89B trial fixes the old receiver/flag-pointer register wall. Compared
// with87B native it uses CL then copies to BL and saves EBX inside the branch;
// the final saved-register restoration order differs too. All callees resolve.
#include "ascii_string.h"
struct Rva005E2CFAEntry { void *m_result; const char *m_name; };
extern const Rva005E2CFAEntry g_00C77B40[3];
__declspec(noinline) const char *Rva005E2D26Get(int key)
{
 for(unsigned int i=0;i<3;++i) {
  if(key==(int)g_00C77B40[i].m_result) return g_00C77B40[i].m_name;
 }
 return 0;
}
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva0054C83FAptCall(Rva00222A8BTarget *,void *,const char *,const char *,const char **,bool *);
namespace StrategicHUD {
class RegionDetailsMovieClip { public: class Impl; };
class RegionDetailsMovieClip::Impl {
public: void SetPageEnabled(int page, bool enabled);
private:
 RegionDetailsMovieClip *owner;
 int m_level;
 AsciiString m_name;
 char unread0C[0x30-0x0C];
 bool m_pageEnabled[3];
};
void RegionDetailsMovieClip::Impl::SetPageEnabled(int page, bool enabled)
{
 bool &flag=m_pageEnabled[page];
 if(flag!=enabled) {
  const bool initialEnabled=enabled;
  const char *id=Rva005E2D26Get(page);
  Rva0054C83FAptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),(void*)m_level,m_name.str(),"SetTabEnabled",&id,&enabled);
  flag=initialEnabled;
 }
}
}
