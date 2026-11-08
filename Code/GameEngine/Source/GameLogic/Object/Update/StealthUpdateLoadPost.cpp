// cl: /MD
// ?loadPostProcess@StealthUpdate@@MAEXXZ 0x00374AE8 26B evidence: slot 1 of vtable 0x00817F20; base UpdateModule loadPostProcess pin plus flag at +0x47 when +0x3c set then tail to rowed rva003748BD; donor Rva0024A797Derived flags
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/StealthUpdate.h"
void StealthUpdate::loadPostProcess()
{
    UpdateModule::loadPostProcess();
    if (m_disguiseAsTemplate)
        m_xferRestoreDisguise = true;
    return rva003748BD();
}
