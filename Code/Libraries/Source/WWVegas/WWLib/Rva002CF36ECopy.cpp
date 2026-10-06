// cl: /MD /GX-
// ?Rva002CF36ECopy@@YAXPAURva002CF13B@@PBU1@@Z @0x002CF36E 18B.
// Null-guarded placement copy through the rowed 0x002CF13B copy ctor:
// if (dest) new (dest) Rva002CF13B(*src). Same 18B shape as the rowed
// 0x002CF35C copy. Caller at 0x002CF883 unblocks 0x002CF86F.
#include <new>

class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other);
};

struct Rva002CF13B
{
	BfmeFixedStorage002CF0F0 m_head;
	int m_field04;
	Rva002CF13B(const Rva002CF13B &other);
};

void __cdecl Rva002CF36ECopy(Rva002CF13B *dest, const Rva002CF13B *src)
{
	if (dest != 0)
		new (dest) Rva002CF13B(*src);
}
