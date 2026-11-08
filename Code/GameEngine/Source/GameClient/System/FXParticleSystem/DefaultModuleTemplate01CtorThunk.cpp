// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/moduledata
// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $01 / N=2) default constructor.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// MSVC mangles DefaultModuleTemplate<2> as @$00
// ??0?$DefaultModuleTemplate@$01@FXParticleSystem@@QAE@XZ
DefaultModuleTemplate<2>::DefaultModuleTemplate()
    : CategoryModuleTemplate<2>(), DefaultUpdateModuleInfo()
{
}

}
