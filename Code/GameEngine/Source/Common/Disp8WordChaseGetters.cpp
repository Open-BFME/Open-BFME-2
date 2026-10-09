// Disp8 word-chase getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / movsx eax,word [eax+<DISP2>] / ret
//
// A pointer is read at a fixed displacement from `this`, then a signed word
// is read at a second displacement from that pointer, sign-extended, and
// returned. MSVC 7.1 emits the disp8 loads `8B 41 XX` + `0F BF XX`, plus
// `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).
#define BFME_DISP8_WORDCHASE_ZERO_GETTER(NAME, DISP1) \
	class Inner##NAME \
	{ \
	public: \
		short m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		int get() const; \
	}; \
	int NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this + (DISP1)))->m_holder->m_value; \
	}

BFME_DISP8_WORDCHASE_ZERO_GETTER(Rva0023DB58WordChaseField, 0x0C)

// Native 2E6CB0..2E6CB7 and 2E6CB7..2E6CBE are independently complete
// RET0 leaves after the RET4 at 2E6CAD and before the distinct initializer
// at 2E6CBE. Each zero-extends an unsigned 16-bit pointee field, at +0x12
// or +0x10. BF1 9cbfb551fe20 PathfindCell_costSoFar.cpp guides the field
// access; its PathfindCell names are not established target identities.
class Rva002E6CB0PointeeValue
{
public:
    unsigned int getBits() const;
    void *holder;
};
unsigned int Rva002E6CB0PointeeValue::getBits() const
{
    return *(const unsigned short *)((const char *)holder + 0x12);
}

class Rva002E6CB7PointeeValue
{
public:
    unsigned int getBits() const;
    void *holder;
};
unsigned int Rva002E6CB7PointeeValue::getBits() const
{
    return *(const unsigned short *)((const char *)holder + 0x10);
}
