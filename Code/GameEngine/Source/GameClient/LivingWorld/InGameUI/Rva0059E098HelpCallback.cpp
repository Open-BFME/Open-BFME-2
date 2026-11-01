// cl: /O1 /MD /EHsc /G7 /arch:SSE
// Native 0x0059E098..0x0059E0C1 (41 bytes): hidden return pointer, RET4.
// WB 0x014D9DE0 independently returns CreateHelpFor(this+38) or an empty
// counted help handle. Original callback/owner names remain unidentified.
// The return handle spelling/lifetime is carried from the rowed 0x0056BC3D
// provider. Its nontrivial destructor explains the compiler's return flag
// stack slot; no explicit unread or volatile source local is required.
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct RvaF6Ret {
    RvaF6Ret(TargetRef00217D4C *p) : m_ptr(p) {
        if (m_ptr) ++m_ptr->references;
    }
    __declspec(dllimport) __forceinline ~RvaF6Ret() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
    TargetRef00217D4C *m_ptr;
};
class Rva005E2338Elem;
namespace StrategicInGameUI {
RvaF6Ret CreateHelpFor(const Rva005E2338Elem *);
}
class Rva0059E098Class {
public:
    RvaF6Ret rva0059E098();
private:
    char m_pad00[0x38];
    const Rva005E2338Elem *m_entry;
};
RvaF6Ret Rva0059E098Class::rva0059E098() {
    if (m_entry) return StrategicInGameUI::CreateHelpFor(m_entry);
    else return RvaF6Ret(0);
}
