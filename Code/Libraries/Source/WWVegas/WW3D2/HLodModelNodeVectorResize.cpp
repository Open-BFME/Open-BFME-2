// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Reconstructed from the BFME1 reference unit.  BFME2 does not carry hlod.h,
// so this TU preserves the proven nested ModelNode payload and its enclosing
// derived-class scope while instantiating the unchanged VectorClass template.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

void __cdecl operator delete[](void *) throw();

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
		bool operator == (const ModelNodeClass &that)
		{
			return (Model == that.Model) && (BoneIndex == that.BoneIndex);
		}

		bool operator != (const ModelNodeClass &that)
		{
			return !operator == (that);
		}

		RenderObjClass *Model;
		int BoneIndex;
		Vector3 Offset;
	};
};

template class VectorClass<HLodClass::ModelNodeClass>;
