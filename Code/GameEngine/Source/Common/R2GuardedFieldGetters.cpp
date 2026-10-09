// ?get@Rva004C1160@@QAEHXZ, retail 0x004059BE (17B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/R2GuardedFieldGetters.cpp
// (BFME1 0x004C1160). Guarded field read: null pointee returns zero, else one
// int field at +0x1C8 of the pointee reached via the pointer at +0x08.
// The donor defines 22 further siblings the sweep did not place, so only the
// placed body is instantiated here.

struct IntAt1C8h { char m_leading[ 0x1C8 ]; int m_value; };

#define R2_GUARDED_FIELD_GET( NAME, OFF, POINTEE, TYPE )  \
	class NAME                                          \
	{                                                   \
	public:                                             \
		char m_leading[ OFF ];                          \
		POINTEE *m_pointee;                             \
		TYPE get();                                     \
	};                                                  \
	TYPE NAME::get()                                    \
	{                                                   \
		if ( m_pointee )                                \
		{                                               \
			return m_pointee->m_value;                  \
		}                                               \
		return 0;                                       \
	}

R2_GUARDED_FIELD_GET( Rva004C1160, 0x8, IntAt1C8h, int )

// Four further complete retail leaves, found by compiling the clean BFME1
// 9cbfb551fe20dae985f91f2319d8997287b6a705 donor under /O1 /arch:SSE /G7
// with a 5-byte search floor. Each target independently reads a pointer at
// receiver+0, returns zero if null, else reads exactly 32 bits at its listed
// pointee offset. Every path ends in RET0 and there are no relocations.
// Original classes, field purpose and signedness/pointer interpretation are
// unknown. These carriers preserve only that measured raw-bit contract;
// their names use target addresses rather than donor carrier addresses.
#define BFME_R2_NULL_HEAD_BITS(NAME, FIELD) \
    class NAME \
    { \
    public: \
        unsigned getBits() const; \
        const void *m_pointee; \
    }; \
    unsigned NAME::getBits() const \
    { \
        if (m_pointee) \
            return *(const unsigned *)((const char *)m_pointee + FIELD); \
        return 0; \
    }

// Previous RET50D45; two local RETs end50D4F/50D52; next entry50D53.
BFME_R2_NULL_HEAD_BITS(Rva00050D46, 0x2C)
// Previous RET50DE2; two local RETs end50DEC/50DEF; next entry50DF0.
BFME_R2_NULL_HEAD_BITS(Rva00050DE3, 0x3C)
// Previous RET2E6AE0; two local RETs end2E6AEA/2E6AED; next entry2E6AEE.
BFME_R2_NULL_HEAD_BITS(Rva002E6AE1, 0x14)
// Previous RET4 at2E6B2D; local RETs2E6B39/2E6B3C; next entry2E6B3D.
BFME_R2_NULL_HEAD_BITS(Rva002E6B30, 0x0C)

// Native 2E6AD4..2E6AE1 is a complete 13-byte leaf, independently aligned
// from known 2E6A82 and prior RET 2E6AD3; both local returns and the next
// already rowed sibling at 2E6AE1 confirm its full extent.
// Current BFME1 9cbfb551 PathfindCell::getObstacleID is a source lead only;
// target facts are receiver pointer+0, null-to-zero and raw pointee word+20.
// Original receiver, field meaning and signedness remain unresolved.
BFME_R2_NULL_HEAD_BITS(Rva002E6AD4, 0x20)

// Nullable argument word getter, reference lead from BF1 revision9cbfb551:
// game/Libraries/Source/WWVegas/WWLib/Rva006A43D0PointerHashResize.cpp,
// Rva006A43D0ExtractKey::operator(). Preserve its typed conditional shape;
// original receiver/functor, payload identity and field meaning are unknown.
// Native full50E0E..50E1C: argument load, null guard, raw word+8, RET4.
// Decoding from known50DF0 ends RET50E04; next9-byte arg-deref leaf ends
// RET4 at50E0B, proving this entry; next known body starts50E1C.
struct Rva00050E0ERawWord
{
    unsigned prefix[2];
    unsigned word8;
};
class Rva00050E0ENullArg
{
public:
    unsigned getBits(Rva00050E0ERawWord *value) const;
};
unsigned Rva00050E0ENullArg::getBits(Rva00050E0ERawWord *value) const
{
    return value==0 ? 0 : value->word8;
}

// Clean BF1 f98983a7 Rva009004A0RenderObjectFactory.cpp supplies the
// nullable first-pointer conditional as a source lead, not c_str identity.
// Native50D60..50D6C follows the rowed50D53 RET50D5F and has one RET50D6B;
// the next independent body begins50D6C. It returns receiverword0 or the
// established global object at DE0878. Keep its canonical declaration and
// expose only an opaque address: owner, payload and original prototype are
// unrecovered. The donor's literal fallback does not prove a target string.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Rva00050D60Pointer
{
public:
    const void *getPointer() const;
    const void *value;
};
const void *Rva00050D60Pointer::getPointer() const
{
    return value ? value : &AsciiString::TheEmptyString;
}

// The old ConstIntGetters8Addr row at 0x203517 covers an interior fallback
// block. Native 0x203510..0x203521 is a complete 17-byte conditional getter
// between the prior LEA/RET leaf and the next floating-point body. It reads
// receiver pointer +0x30: null returns the genuine AsciiString::TheEmptyString
// object at VA 0xDE0878, nonnull returns an interior address at pointer+0x14.
// BF1 f989 nullable-pointer sources guide the conditional only. Payload type,
// owner, semantic fields and member/free spelling remain unknown; retain an
// address-owned consumed-prefix view and the canonical global declaration.
class Rva00203510Pointer
{
public:
    const void *getPointer() const;
private:
    char m_unmodelled0[0x30];
    const char *m_value;
};
const void *Rva00203510Pointer::getPointer() const
{
    const char *value = m_value;
    if (!value)
        return &AsciiString::TheEmptyString;
    return value + 0x14;
}
