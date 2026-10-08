// Disp32 float-to-int getters: nine-byte const __thiscall members with one
// shape:
//
//     cvttss2si eax,[ecx+<DISP>] / ret
//
// One float field is read back truncated to int. Most displacements here are
// disp32 (MSVC 7.1 uses disp8 whenever the offset fits, so most offsets
// are at least 0x80); the 0x78 sibling below compiles to the six-byte disp8
// encoding. Identity is not recovered: every name is derived from
// its address.
// cl: /MD /EHsc /DNDEBUG
#define BFME_DISP32_CVT_FLOAT_INT_GETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		int get() const; \
		char m_lead[DISP]; \
		float m_value; \
	}; \
	int NAME::get() const \
	{ \
		return (int)m_value; \
	}

BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C8CCIntGetter, 0x88)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C8E6IntGetter, 0x8C)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C900IntGetter, 0x90)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C91AIntGetter, 0x94)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C934IntGetter, 0x98)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva002620ADIntGetter, 0x1AC)
BFME_DISP32_CVT_FLOAT_INT_GETTER(Rva0030C890IntGetter, 0x78)

// Clean donor leads: Open-BFME-1 40e7f2f21f0011b42a5654697cdedbc2658b6d9b,
// game/GameEngine/Source/Common/BfmeConv1332.cpp and BfmeConv1299.cpp
// (unchanged from 34f59164f6d1efd413c5fd37f4894ec834c3c0fe).
// Target evidence: each complete, INT3-delimited body converts consecutive
// floats with CVTTSS2SI, writes signed dwords at the same offsets, returns
// the receiver, and ends in RET 4. These are minimum physical views; original
// class names and any relationship between the two receivers are unknown.
struct Rva0016CB90FloatView { float m_00, m_04, m_08; };
class Rva0016CB90IntView
{
public:
    Rva0016CB90IntView *assign(const Rva0016CB90FloatView *source);
    int m_00, m_04, m_08;
};
Rva0016CB90IntView *Rva0016CB90IntView::assign(const Rva0016CB90FloatView *source)
{
    m_00 = (int)source->m_00;
    m_04 = (int)source->m_04;
    m_08 = (int)source->m_08;
    return this;
}

struct Rva00169F30FloatView { float m_00, m_04; };
class Rva00169F30IntView
{
public:
    Rva00169F30IntView *assign(const Rva00169F30FloatView *source);
    int m_00, m_04;
};
Rva00169F30IntView *Rva00169F30IntView::assign(const Rva00169F30FloatView *source)
{
    m_00 = (int)source->m_00;
    m_04 = (int)source->m_04;
    return this;
}
