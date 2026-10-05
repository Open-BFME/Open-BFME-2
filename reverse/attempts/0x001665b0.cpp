// ?insert@?$vector@UElem36@@V?$allocator@UElem36@@@_STL@@@_STL@@QAEPAUElem36@@PAU3@ABU3@@Z
// partial score=0.96 date=2026-10-05
// ?insert@?$vector@UElem36@@V?$allocator@UElem36@@@_STL@@@_STL@@QAEPAUElem36@@PAU3@ABU3@@Z
// partial score=0.95 date=2026-10-04
// cl: /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$vector@UElem36@@V?$allocator@UElem36@@@_STL@@@_STL@@QAEPAUElem36@@PAU3@ABU3@@Z @0x001665B0 288B:
// STLport vector<Elem36> single insert. Same 0x24 stride stand-in as
// stlport_vector_elem36_push_back.cpp (dword + 16-byte block + three dwords +
// byte); callees rowed/pinned (_Construct 0x001610F0 copy-ctor 0x00161050
// copy_backward 0x001611B0 overflow 0x001663F0); called from 0x00166A1B.
#include <vector>

struct Elem36Block16
{
	float m_words[4];
};

struct Elem36Tail
{
	Elem36Block16 m_block;
	float m_word14;
	float m_word18;
	float m_word1C;
};

struct Elem36
{
	int m_word00;
	Elem36Tail m_tail;
	bool m_flag20;

	Elem36(const Elem36 &other);
	Elem36 &operator=(const Elem36 &other)
	{
		m_word00 = other.m_word00;
		m_tail.m_block.m_words[0] = other.m_tail.m_block.m_words[0];
		m_tail.m_block.m_words[1] = other.m_tail.m_block.m_words[1];
		m_tail.m_block.m_words[2] = other.m_tail.m_block.m_words[2];
		m_tail.m_block.m_words[3] = other.m_tail.m_block.m_words[3];
		m_tail.m_word14 = other.m_tail.m_word14;
		m_tail.m_word18 = other.m_tail.m_word18;
		m_tail.m_word1C = other.m_tail.m_word1C;
		m_flag20 = other.m_flag20;
		return *this;
	}
};

typedef _STL::vector<Elem36, _STL::allocator<Elem36> > Elem36Vector;

template _STL::vector<Elem36>::iterator _STL::vector<Elem36>::insert(Elem36 *, const Elem36 &);
