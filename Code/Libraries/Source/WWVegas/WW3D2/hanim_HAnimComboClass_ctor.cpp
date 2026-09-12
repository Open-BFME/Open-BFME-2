// cl: /G7 /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// HAnimComboClass::HAnimComboClass(int) at 0x00196B80, split out of hanim.cpp
// because retail built it with /G7 -- the loop decrement is sub edi,1 --
// while hanim.cpp's HAnimComboDataClass::Set_HAnim only matches without that
// flag (it needs inc). Same pattern as hanim_weight_vector_add.cpp. Body
// copied verbatim from hanim.cpp, as are the headers.
#define Matrix4x4 Matrix4
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#include "hanim.h"
#include "assetmgr.h"
#include "htree.h"
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"

DEFINE_AUTO_POOL(HAnimComboDataClass,256);

// Moved verbatim from hanim.cpp: this TU needs the body visible so the
// combo ctor below inlines it (retail folds the member stores into the
// allocation loop instead of calling out).
HAnimComboDataClass::HAnimComboDataClass(bool shared)
: Shared(shared), HAnim(0), PivotMap(0), Frame(0), Weight(1)
{}

HAnimComboClass::HAnimComboClass( int num_animations )
{
	HAnimComboData.Resize(num_animations);

	// Binary minus, not --/-=: under this TU's /G7 only this spelling emits
	// retail's sub edi,1 loop decrement (verified against -- and -= 1).
	while (num_animations) {
		HAnimComboData.Add(new HAnimComboDataClass());
		num_animations = num_animations - 1;
	}
}
