// cl: /DNDEBUG /MD
//
// WeaponTemplateSetHead copy ctor, retail 0x00045455, 24 bytes.
// Dedicated TU so WeaponTemplateSetCopyCtor.cpp cannot inline this memcpy.

#include <string.h>

#include "../../../Include/Common/WeaponTemplateSetHead.h"

WeaponTemplateSetHead::WeaponTemplateSetHead(const WeaponTemplateSetHead &that)
{
	memcpy(this, &that, 0x4C);
}
