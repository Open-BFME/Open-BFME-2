// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ??1Rva001976F0@@QAE@XZ
// retail 0x0032C1C1, 54 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R4TwoMemberDestructors.cpp
// (reference/open-bfme-1 @ 6d943426), which recompiled /Os emits this body
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// six are omitted.
//
// Retail destroys the second member (+0x10) before the first (+0x4) -- the
// reverse of declaration order -- and guards each with its own SEH frame, so
// the compiler-generated unwind state (`and dword ptr [ebp-4], 0` then
// `or ..., -1`) appears between them. Both members are the same vector type,
// so both destructor calls land on one address.
//
// IDENTITY IS NOT RECOVERED. The name is address-derived, carried from the
// donor. The element and container types are the donor's local views, not
// recovered target identities.

struct Gen00196F30;

namespace _STL
{
template <class T> class allocator;

template <class T, class Allocator>
class vector
{
public:
	~vector();
private:
	char m_body[0xC];
};
}

typedef _STL::vector<Gen00196F30, _STL::allocator<Gen00196F30> > Rva00196F30Vector;

#define R4_TWO_MEMBER_DTOR( NAME, LEAD, M1, M2 )                              \
	struct NAME                                                               \
	{                                                                         \
		char m_lead[ LEAD ];                                                  \
		M1 m_first;                                                           \
		M2 m_second;                                                          \
		~NAME();                                                              \
	};                                                                        \
	NAME::~NAME() {}

// @??1Rva001976F0@@QAE@XZ 0x0032C1C1
R4_TWO_MEMBER_DTOR( Rva001976F0, 4, Rva00196F30Vector, Rva00196F30Vector )