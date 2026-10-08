// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /EHc- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native 005FA89C..005FA8C5: three-stack-argument thiscall constructor.
// C79E30 connects it to the destructor at 005FAF5D; +28 stores input +04.
// Replaces the fastcall surrogate and literal vtable store with real C++.
#include "BattlePromptArmyPanelView.h"
class Rva005FED59 { public: void rva005FED59() const; };
Rva005FAF5D::Rva005FAF5D(int a, int b, Rva005FA89CC *input)
    : Rva005FF13A(a, b, (const Rva005FEF11Input **)input), m_owner28(input->m_04)
{
}
// Native 005FAF5D..005FAF9F, 66 bytes. Clears the owning controller only
// when its +14 active-panel pointer still refers to this panel.
Rva005FAF5D::~Rva005FAF5D()
{
    if (m_owner28->m_active14 == this)
        m_owner28->rva005FADEF(0);
}

// Native 005FAF9F returns this panel to its owning controller after the
// established +08 validation wrapper. The callee's parameter type is opaque.
void Rva005FAF5D::rva005FAF9F()
{
    ((Rva005FED59 *)this)->rva005FED59();
    m_owner28->rva005FADEF((Rva005FED59 *)this);
}

// Native005FA8C5..005FA8CD: the constructor ends at this entry,
// followed by the20-byte roll-over callback. The proven panel clip at+08
// forwards its Boolean selection argument to the matched005FF4CD wrapper.
void Rva005FAF5D::rva005FA8C5(bool flag)
{
    setClipSelected(flag);
}
