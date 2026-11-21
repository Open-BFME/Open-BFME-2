// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1GettingBuiltBehavior@@UAE@XZ, retail 0x0045448F, 114 bytes. Behavior-side
// destructor completing the GettingBuilt file-unit (ctor rowed at 0x004542FA,
// helper rowed at 0x0045427E, poolkey at 0x004543EB, deleting dtor at
// 0x0045477E slot 0 of vtable 0x00C404FC).
//
// Retail: 4 vptr restores (+0 0xC404FC, +0x0C 0xC40440, +0x10 0xC40434,
// +0x20 0xC403C8), helper call 0x0045427E, TheAudio (0x00DFE6E8) slot 0x6c
// removeAudioEvent with +0x24 handle then store 1, list at +0x40 via rowed
// 0x004EC395, base 0x0024A797. The constructor and destructor share the
// GettingBuiltBehavior layout and the +0x20 interface declaration.

#include <list>

class Thing;
class ModuleData;
class Object;

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Include/GameLogic/Module/UpdateSleepTime.h"




// The canonical UpdateModule, as GettingBuiltBehaviorCtor.cpp (first in link
// order) reads it, so both units emit the same GettingBuilt primary,
// BehaviorModuleInterface and +0x10 tables (LINK-168 mechanism 4).
// Retail table 0x00C40434 (+0x10) slot 0 is the rowed override 0x00454DF9.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

typedef unsigned int AudioHandle;

#include "../../../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

#include "GettingBuiltBehaviorView.h"

GettingBuiltBehavior::~GettingBuiltBehavior()
{
	rva0045427E();
	if (TheAudio != 0)
	{
		TheAudio->removeAudioEvent(m_audio24);
		m_audio24 = 1;
	}
}
