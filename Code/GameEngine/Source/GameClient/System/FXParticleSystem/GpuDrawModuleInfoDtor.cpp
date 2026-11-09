// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// Native 0x003A9D43 tears down the string at +0x0C, then Snapshot.
// Keep this TU's existing novtable code-generation property on a forward
// declaration; the shared header supplies the complete class and layout.
namespace FXParticleSystem { class __declspec(novtable) GpuDrawModuleInfo; }
#include "../../../../Include/GameClient/GpuDrawModuleInfo.h"

namespace FXParticleSystem
{

GpuDrawModuleInfo::~GpuDrawModuleInfo()
{
}

}
