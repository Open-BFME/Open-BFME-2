// Disp8 shl dword getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP>] / shl eax,<IMM8> / ret
//
// One dword is read at a fixed displacement from `this`, shifted left, and
// the result is returned. MSVC 7.1 emits the disp8 load `8B 41 XX` plus
// `C1 E0 XX`, plus `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless eight-byte shape).
#define BFME_DISP8_SHL_DWORD_GETTER(NAME, DISP, IMM) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		int m_value; \
	}; \
	int NAME::get() const \
	{ \
		return m_value << IMM; \
	}

BFME_DISP8_SHL_DWORD_GETTER(Rva00169650ShlDwordField, 0x10, 0x04)

// Fresh clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705
// game/GameEngine/Source/Common/UnclaimedSmallLeaves04.cpp /O2 /arch:SSE /G7
// supplies the raw32 left-shift expression. Retail independently proves two
// separate INT3-bracketed leaves: 0x00169580..0x00169588 reads +0x10 then
// doubles twice; 0x00169590..0x00169596 reads +0x10 then doubles once.
// Each returns EAX with RET0. The original receiver classes, field purposes
// and signedness are unknown; unsigned storage expresses the raw32 shift.
// No common receiver identity is inferred from adjacent addresses.
#define BFME_DISP8_SCALED_BITS(NAME, SHIFT) \
    class NAME { \
    public: \
        unsigned scaled() const; \
        char m_lead[0x10]; \
        unsigned m_value; \
    }; \
    unsigned NAME::scaled() const { return m_value << SHIFT; }

BFME_DISP8_SCALED_BITS(Rva00169580ScaledField, 2)
BFME_DISP8_SCALED_BITS(Rva00169590ScaledField, 1)

// Whole clean BF1 f989 Rva00928F80Accessors.cpp and Rva009239F0Accessors.cpp
// supply the modular unsigned-field scaling expressions under O2/SSE2/G7.
// Native independently brackets15AB40..15AB4A and169450..169459 with INT3:
// both load receiver word10, then scale by8/6 and return EAX with RET0.
// Original owner, field purpose and signedness remain unknown; unsigned
// arithmetic preserves the witnessed32bit result without allocation claims.
// Existing169580/169590 scale siblings establish this home's O2/G7 profile.
BFME_DISP8_SCALED_BITS(Rva0015AB40ScaledField, 3)

class Rva00169450ScaledField
{
public:
    unsigned scaled() const;
private:
    char m_unmodelled0[0x10];
    unsigned m_word10;
};
unsigned Rva00169450ScaledField::scaled() const
{
    return m_word10 * 6;
}
