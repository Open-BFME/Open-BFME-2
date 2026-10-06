// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?Rva004ED0D7Assign@@YAXPAVModelNodeClass@HLodClass@@PBV12@@Z @ 0x004ED0D7, 18 bytes.
// Guarded single-element copy: assigns *src into *dst when dst is non-null.
// Evidence: callers are the ModelNode range/counted copy loops at 0x004ED0E9,
// 0x004ED10F, 0x004ED471 and 0x004ED69B; callee is the rowed
// ModelNodeClass::operator= (??4ModelNodeClass@HLodClass@@QAEAAV01@ABV01@@Z)
// at 0x004ECEA8. Element stride 0x14 matches the ModelNode payload below,
// shared with Code/Libraries/Source/WWVegas/WW3D2/HLodModelNodeVectorResize.cpp.

#include "vector.h"
#include "vector3.h"

class RenderObjClass;

class HLodBase
{
};

class HLodClass : public HLodBase
{
public:
	class ModelNodeClass
	{
	public:
		ModelNodeClass & operator = (const ModelNodeClass &that);

		RenderObjClass *Model;
		int BoneIndex;
		Vector3 Offset;
	};
};

void __cdecl Rva004ED0D7Assign(HLodClass::ModelNodeClass *dst, const HLodClass::ModelNodeClass *src)
{
	if (dst != 0) {
		*dst = *src;
	}
}
