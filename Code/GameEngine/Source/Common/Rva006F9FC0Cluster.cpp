// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// 0x006F9FC0: bounding-box containment predicate.  It asks the argument
// object (address-derived callee 0x6E1E30) to fill a 16-byte rect, converts
// this object's signed int coordinates at +0x74/+0x78 to float, and tests
// containment.

struct Rva006F9FC0Rect
{
	float x1;
	float y1;
	float x2;
	float y2;
};

class Rva006E1E30
{
public:
	void rva006E1E30(Rva006F9FC0Rect *rect);
};

#include "../../../Libraries/Source/Apt/AptAnimationPoolData.h"

// ?rva006F9FC0@AptAnimationPoolData@@QAE_NPAVRva006E1E30@@H@Z
bool AptAnimationPoolData::rva006F9FC0(Rva006E1E30 *object, int)
{
	Rva006F9FC0Rect rect;
	object->rva006E1E30(&rect);
	if ((float)m_74 >= rect.x1 && (float)m_74 <= rect.x2
		&& (float)m_78 >= rect.y1 && (float)m_78 <= rect.y2)
		return true;
	return false;
}
