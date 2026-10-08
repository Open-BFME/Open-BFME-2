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
