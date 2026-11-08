// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/moduledata
// Open-BFME5: clean-C++ DefaultModuleTemplate (ledger $00 / N=1) default constructor.

#include "../../../../Include/GameClient/DefaultModuleTemplate.h"

namespace FXParticleSystem
{

// MSVC mangles DefaultModuleTemplate<1> as @$00
// ??0?$DefaultModuleTemplate@$00@FXParticleSystem@@QAE@XZ
DefaultModuleTemplate<1>::DefaultModuleTemplate()
    : CategoryModuleTemplate<1>(), DefaultAlphaModuleInfo()
{
}

}
