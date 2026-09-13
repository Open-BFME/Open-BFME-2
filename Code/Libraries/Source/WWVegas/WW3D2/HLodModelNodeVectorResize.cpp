// cl: /Ireference/shims/bfmevector /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Reconstructed from the BFME1 reference unit.  BFME2 does not carry hlod.h,
// so this TU preserves the proven nested ModelNode payload and its enclosing
// derived-class scope while instantiating the unchanged VectorClass template.

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
