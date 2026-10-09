// Disp8 dword inc/dec: four-byte __thiscall members with one shape:
//
//     inc dword ptr [ecx+<DISP>] / ret        (FF 41 XX C3)
//     dec dword ptr [ecx+<DISP>] / ret        (FF 49 XX C3)
//
// A dword counter at a fixed displacement from `this` is incremented (or
// decremented) in place. Every displacement here fits in a signed byte, so
// MSVC 7.1 emits the disp8 form plus `ret`, for four bytes total. The
// accessed member is spelled as an `int` right after the lead array; the
// bytes cannot distinguish `int` from `unsigned int` or any other
// four-byte-wide incremented slot. Members before the accessed one are
// spelled as a lead array because their types are not witnessed here, only
// their total size.
// Identity is not recovered: every name is derived from its address (the
// disp8 dword-getter family pioneered the same opaque-holder pattern in
// Disp8DwordFieldGetters.cpp).
// No // cl: line (defaults match the frameless four-byte shape).
#define BFME_DISP8_DWORD_INC(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void inc(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::inc() \
	{ \
		++m_counter; \
	}

#define BFME_DISP8_DWORD_DEC(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void dec(); \
		char m_lead[DISP]; \
		int m_counter; \
	}; \
	void NAME::dec() \
	{ \
		--m_counter; \
	}

// WB1107620 RadarMarker::AddReference increments its +8 reference count.
// Native smart-pointer assignment4C9B8F calls this four-byte body before
// the adjacent RadarMarker::DeleteReference body2D76BB.
class RadarMarker
{
public:
	void AddReference();
private:
	char m_opaque00[8];
	int m_refCount;
};

void RadarMarker::AddReference()
{
	++m_refCount;
}
BFME_DISP8_DWORD_INC(Rva0028A807DwordCounter, 0x24)
BFME_DISP8_DWORD_INC(Rva0028A80BDwordCounter, 0x2C)
BFME_DISP8_DWORD_INC(Rva0028A80FDwordCounter, 0x28)
BFME_DISP8_DWORD_INC(Rva0020357EDwordCounter, 0x50)
BFME_DISP8_DWORD_INC(Rva00428DB8DwordCounter, 0x10)
BFME_DISP8_DWORD_INC(Rva004D55B8DwordCounter, 0x18)
BFME_DISP8_DWORD_INC(Rva004ECD9FDwordCounter, 0x1C)
BFME_DISP8_DWORD_INC(Rva0053F8E5DwordCounter, 0x14)
BFME_DISP8_DWORD_INC(Rva00552C52DwordCounter, 0x54)
BFME_DISP8_DWORD_INC(Rva005D1A79DwordCounter, 0x04)
BFME_DISP8_DWORD_DEC(Rva00552C4EDwordCounter, 0x54)
BFME_DISP8_DWORD_DEC(Rva004ECDA3DwordCounter, 0x1C)
BFME_DISP8_DWORD_DEC(Rva00050D14DwordCounter, 0x14)

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?attach@NetCommandMsg@@QAEXXZ=?inc@Rva004D55B8DwordCounter@@QAEXXZ")

// Native6272D0..6272D5 lies between INT3 padding and ends RET:
// subtract24 from raw word4. Clean BF1 9cb Rva009F5B10VectorPushBack24.cpp
// supplies the expression only; no vector identity or element type is claimed.
// Unsigned storage preserves the native32-bit wrap semantics.

// ?subtract24@Rva006272D0Fields@@QAEXXZ
struct Rva006272D0Fields { char pad[4]; unsigned int word4; void subtract24(); };
void Rva006272D0Fields::subtract24() { word4 -= 24u; }
