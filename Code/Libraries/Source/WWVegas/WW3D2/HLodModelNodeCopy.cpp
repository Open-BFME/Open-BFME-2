// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?Rva004ED0E9Copy@@YAPAVModelNodeClass@HLodClass@@PBV12@0PAV12@@Z @ 0x004ED0E9, 38 bytes.
// Range copy: copies [first last) into result via the guarded Assign,
// returning one past the last destination. Evidence: callers at 0x004ED4B2 and
// 0x004ED4FD pass src-begin src-end dst-begin; callee is the rowed
// Rva004ED0D7Assign at 0x004ED0D7. Increment order ++first then ++result gives
// retail add-edi before add-esi. Shares the ModelNode payload with its
// siblings.
#include "vector.h"
#include "vector3.h"

class RenderObjClass;

class HLodClass
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

void __cdecl Rva004ED0D7Assign(HLodClass::ModelNodeClass *dst, const HLodClass::ModelNodeClass *src);

HLodClass::ModelNodeClass * __cdecl Rva004ED0E9Copy(const HLodClass::ModelNodeClass *first, const HLodClass::ModelNodeClass *last, HLodClass::ModelNodeClass *result)
{
	HLodClass::ModelNodeClass *r = result;
	const HLodClass::ModelNodeClass *f = first;
	while (f != last) {
		Rva004ED0D7Assign(r, f);
		++f;
		++r;
	}
	return r;
}
