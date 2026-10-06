// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?Rva004ED10FFill@@YAPAVModelNodeClass@HLodClass@@PAV12@IPBV12@@Z @ 0x004ED10F, 37 bytes.
// Counted fill: copies *src into each of count destinations, stride 0x14,
// returning one past the last. Evidence: sole caller 0x004ED4DF passes dst in
// eax, count from idiv and src from [ebp+0x0C]; callee is the rowed
// Rva004ED0D7Assign at 0x004ED0D7. Loop shape test-jbe plus dec-before-pop
// needs unsigned count with <=0 guard and --n in the condition. Shares the
// ModelNode payload with HLodModelNodeAssign.cpp.
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

HLodClass::ModelNodeClass * __cdecl Rva004ED10FFill(HLodClass::ModelNodeClass *dst, unsigned int count, const HLodClass::ModelNodeClass *src)
{
	HLodClass::ModelNodeClass *p = dst;
	unsigned int n = count;
	if (n <= 0) {
		return p;
	}
	do {
		Rva004ED0D7Assign(p, src);
		++p;
	} while (--n != 0);
	return p;
}
