// cl: /DNDEBUG /MD /EHsc /Ob2
// ??1Rva001D28F0Element@@QAE@XZ, retail 0x00689500, 119 bytes.
// Dedicated TU (Rva001D25F0VectorInsertOverflow.cpp instantiates
// vector<Rva001D28F0Element> over this type; a same-TU definition would
// capture those REL32s locally).
//
// Non-virtual element destructor: an owned pointer at +0x18 (torn down
// through the rowed 0x688980 destructor, then freed) plus three string
// members at +0/+4/+8 and 12 bytes of plain data at +0xC. The members are
// spelled AsciiStringMember so their destruction resolves to the pinned
// 0x36410 fold directly (a locally-defined AsciiString dtor would capture
// the calls in-TU instead). Destruction runs in reverse declaration order
// (+8, +4, +0), and the explicit pointer teardown runs first.

class AsciiStringMember
{
public:
	~AsciiStringMember();

private:
	void *m_data;
};

class Rva00688980
{
public:
	~Rva00688980();
};

class Rva001D28F0Element
{
public:
	~Rva001D28F0Element();

private:
	AsciiStringMember m_first;
	AsciiStringMember m_second;
	AsciiStringMember m_third;
	unsigned char m_plain[0xC];
	Rva00688980 *m_owned;
};

// ??1Rva001D28F0Element@@QAE@XZ
Rva001D28F0Element::~Rva001D28F0Element()
{
	// NOTE: read through a local so the pointer parks in a callee-saved
	// register (it is used on both sides of the teardown call); reading
	// the member twice keeps it in ecx with a later reload instead.
	Rva00688980 *owned = m_owned;
	if (owned != 0) {
		owned->~Rva00688980();
		operator delete(owned);
	}
}
