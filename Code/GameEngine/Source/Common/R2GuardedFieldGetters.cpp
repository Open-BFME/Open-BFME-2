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
