// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// BfmeResetTextureRef::operator=(const BfmeResetAnyRef &), retail 0x00131D99,
// 50 bytes. Dedicated TU so dx8wrapper.cpp cannot see this body.
// Non-TEX holders are cleared; TEX or null go through RefCountPtr assign.

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

BfmeResetTextureRef &BfmeResetTextureRef::operator=(const BfmeResetAnyRef &rhs)
{
	if (rhs.pointer && rhs.pointer->GetClassId() != 'TEX')
		clear();
	else
		*(BfmeMapPictureTexture *)this = *(const BfmeMapPictureTexture *)&rhs;
	return *this;
}
