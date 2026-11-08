// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/moduledata

// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $05 / N=6) default constructor.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$05@FXParticleSystem@@QAE@XZ
DefaultModuleTemplate<6>::DefaultModuleTemplate()
    : CategoryModuleTemplate<6>(), DefaultDrawModuleInfo()
{
}

}
