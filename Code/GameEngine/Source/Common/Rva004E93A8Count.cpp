// cl: /MD
// ?rva004E93A8@Rva004E93A8@@QAEHXZ @0x004E93A8 64B count ptr array +0xc +0x10 where get()==0 and (elem+0x5c==1 or global flag) callees get 0x002AA22A callers 0x002C6C6D 0x004E974A
#include "../../Include/Common/Rva002AA22AByteField.h"
struct Glob004E93A8 { char _pad[0x860]; unsigned char m_860; };
// TheSkirmishAIManager is owned as a Rva002A8F24 (Rva005EEA20Find.cpp); this
// unit reads it through its own view.
class Rva002A8F24;
extern Rva002A8F24 *TheSkirmishAIManager;
class Rva004E93A8
{
public:
    char _pad0[0xc];
    Rva002AA22AByteField **m_begin;
    Rva002AA22AByteField **m_end;
    int rva004E93A8();
};

int Rva004E93A8::rva004E93A8()
{
    int count = 0;
    Rva002AA22AByteField **p = m_begin;
    Rva002AA22AByteField **e = m_end;
    for (;;) {
        if (p == e)
            break;
        Rva002AA22AByteField *cur = *p;
        if (cur->get() == 0) {
            if (*(int *)((char *)cur + 0x5c) == 1 || ((Glob004E93A8 *)TheSkirmishAIManager)->m_860 != 0)
                ++count;
        }
        ++p;
    }
    return count;
}
