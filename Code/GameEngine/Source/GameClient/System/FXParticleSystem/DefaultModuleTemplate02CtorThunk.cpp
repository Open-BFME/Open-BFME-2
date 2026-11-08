// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/moduledata

// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $02 / N=3) default constructor.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// ??0?$DefaultModuleTemplate@$02@FXParticleSystem@@QAE@XZ
DefaultModuleTemplate<3>::DefaultModuleTemplate()
    : CategoryModuleTemplate<3>(), DefaultPhysicsModuleInfo()
{
}

}
