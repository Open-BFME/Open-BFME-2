// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// BfmeResetShaderRef::operator=(const BfmeResetAnyRef &), retail 0x0015142A,
// 50 bytes. Dedicated TU so dx8wrapper.cpp and the texture-assign unit cannot
// see this body. Non-FXSH holders are cleared; FXSH or null go through
// RefCountPtr assign. clear is the ICF twin already pinned on the texture ref.

#include "BfmeResetTagged.h"

class BfmeMapPictureTexture
{
	void *pointer;

public:
	BfmeMapPictureTexture &operator=(const BfmeMapPictureTexture &);
};

struct BfmeResetAnyRef
{
	BfmeResetTagged *pointer;
};

#include "BfmeResetTextureRef.h"

struct BfmeResetShaderRef
{
	void *pointer;
	BfmeResetShaderRef &operator=(const BfmeResetAnyRef &rhs);
};

BfmeResetShaderRef &BfmeResetShaderRef::operator=(const BfmeResetAnyRef &rhs)
{
	if (rhs.pointer && rhs.pointer->GetClassId() != 0x46585348)
		((BfmeResetTextureRef *)this)->clear();
	else
		*(BfmeMapPictureTexture *)this = *(const BfmeMapPictureTexture *)&rhs;
	return *this;
}
