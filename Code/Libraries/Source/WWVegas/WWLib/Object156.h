#ifndef BFME_OPAQUE_RECORD156_H
#define BFME_OPAQUE_RECORD156_H

// Neutral target view: one leading DWORD and two 76-byte copied members.
// Original types are unknown; the member view reuses a verified copy helper.
#include <vector>
#include <stddef.h>

class WeaponTemplateSetHead {
	char bytes[76];
public:
	WeaponTemplateSetHead();
	__declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &);
};

struct BfmeOpaqueRecord156 {
	unsigned int unknown_00;
	WeaponTemplateSetHead unknown_04;
	WeaponTemplateSetHead unknown_50;
	BfmeOpaqueRecord156();
};

typedef char OpaqueRecord156Extent[
	sizeof(BfmeOpaqueRecord156) == 156 ? 1 : -1];
typedef char OpaqueRecord156Member2[
	offsetof(BfmeOpaqueRecord156, unknown_50) == 0x50 ? 1 : -1];

namespace _STL {
template<> void _Construct<BfmeOpaqueRecord156, BfmeOpaqueRecord156>(
	BfmeOpaqueRecord156 *, const BfmeOpaqueRecord156 &) throw();
}

#endif
