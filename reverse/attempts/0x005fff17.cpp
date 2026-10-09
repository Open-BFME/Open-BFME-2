// ?rva005FFF17@Impl@BattlePromptPlayerPageMovieClip@StrategicHUD@@QAEXH_N@Z
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
#include "ascii_string.h"
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *,void *,const char *,const char *,int *,bool *);
namespace StrategicHUD {
class BattlePromptPlayerPageMovieClip { public: class Impl; };
class BattlePromptPlayerPageMovieClip::Impl {
public:
    void rva005FFF17(int index,bool visible);
private:
    void *unknown00;
    void *level04;
    AsciiString path08;
    char unknown0C[0x40];
    struct ButtonState { bool visible; unsigned char unknown01; } state4C[2];
};
void BattlePromptPlayerPageMovieClip::Impl::rva005FFF17(int index,bool visible)
{
    bool saved=visible;
    ButtonState &state=state4C[index];
    if(state.visible==saved) return;
    Rva00577C23AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,level04,path08.str(),"SetSwapButtonVisibility",&index,&visible);
    state.visible=saved;
}
}

