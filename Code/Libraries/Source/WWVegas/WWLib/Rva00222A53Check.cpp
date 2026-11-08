// cl: /MD
// ?rva00222A53@Rva00222A8BTarget@@QAEEXZ @0x00222A53 56B
// Window-modal check: +0x300 header -4 != -1 and +0x314 window !=0 then
// TheWindowManager slot 0xC0 current equals +0x314 returns true else +0x329.
// Evidence: callers 0x0043288D 31B test-al and 0x002A3303 1314B; TheWindowManager
// 103 TUs extern; virtual 0xC0 indirect no reloc; prev Rva002229E3 next stlport.
// TheRva00222A8BTarget global proves owner class Rva00222A8BTarget.
#include "../../../../GameEngine/Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
#include "../../../../GameEngine/Include/Common/Rva00222A8BTarget.h"
unsigned char Rva00222A8BTarget::rva00222A53()
{
    void *p = m_300;
    if (*(int *)((char *)p - 4) != -1) {
        void **pp = &m_314;
        if (*pp != 0) {
            if (*pp == TheWindowManager->winGetFocus())
                return 1;
        }
    }
    return m_329;
}
