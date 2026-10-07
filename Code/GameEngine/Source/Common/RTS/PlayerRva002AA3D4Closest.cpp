// cl: /DNDEBUG /MD
#include "XYDistanceCallView.h"
// ?Rva002AA3D4Closest@@YAHPAVObject@@PAX@Z @0x002AA3D4 70B
// Object-iteration callback: keeps the nearest object that passes a
// must-be-set / must-be-clear KindOf test. Its user data is the 0x4C-byte
// record the Player-region caller at 0x002AB1C9 builds on its stack (two
// 0x1C-byte KindOf masks, the searcher's position copied from its Object
// +0x38, then the best object and squared distance) and hands with this
// function's address to the iterator at 0x002AB08B; the same pattern is at
// 0x002AB214. Callees Thing::isKindOfMulti 0x0030AD7D and the squared-2D
// distance 0x002615E3 are pinned. Retail compares with fcompi, which MSVC
// 7.1 emits only under /arch:SSE. Names are address-derived.
template <int NUMBITS> class BitFlags
{
	unsigned char m_bits[0x1C];
};
typedef BitFlags<116> KindOfMaskType;
struct Coord3D
{
	float x, y, z;
};
class Thing
{
public:
	bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const;
};
class Object : public Thing
{
public:
};
struct Rva002AA3D4Search
{
	KindOfMaskType m_mustBeSet;	// +0x00
	KindOfMaskType m_mustBeClear;	// +0x1C
	Coord3D m_pos;			// +0x38
	Object *m_closest;		// +0x44
	float m_closestDistSq;		// +0x48
};
int __cdecl Rva002AA3D4Closest(Object *obj, void *userData)
{
	Rva002AA3D4Search *search = (Rva002AA3D4Search *)userData;
	if (obj->isKindOfMulti(search->m_mustBeSet, search->m_mustBeClear)) {
		float distSq = reinterpret_cast<Rva000CBA20 *>(obj)->distSq(reinterpret_cast<const Rva000CBA20Point *>(&search->m_pos));
		if (search->m_closestDistSq > distSq) {
			search->m_closest = obj;
			search->m_closestDistSq = distSq;
		}
	}
	return 1;
}
