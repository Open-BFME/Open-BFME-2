// cl: /O1 /MD /EHsc
// ??1Rva005D0D85@@UAE@XZ 0x005D0D85 54 dtor calls clear 0x005D0ABB at +4 vtable 0x00C75590 base vtable 0x00C75278 via callers 0x0057653E 0x005D100A
class Rva005D0C87;

// The owning pointer to the 0x20-byte implementation; clear() (rowed
// 0x005D0ABB) deletes it.
class Rva005D0ABB
{
public:
	Rva005D0ABB(Rva005D0C87 *impl) : m_impl(impl) {}
	void clear();
private:
	Rva005D0C87 *m_impl;
};

class Rva005D0D85Base
{
public:
	virtual ~Rva005D0D85Base();
};

// ??1Rva005D0D85Base@@UAE@XZ present-unmatched
inline Rva005D0D85Base::~Rva005D0D85Base()
{
}

class Rva005D0D85 : public Rva005D0D85Base
{
public:
	Rva005D0D85(int a, int b, int c);
	virtual ~Rva005D0D85();
private:
	Rva005D0ABB m_holder;
};

// The implementation's constructor, 0x005D0C87 (not yet rowed; pinned).
class Rva005D0C87
{
public:
	Rva005D0C87(Rva005D0D85 *owner, int a, int b, int c);
private:
	unsigned char m_pad00[0x20];
};

// ??0Rva005D0D85@@QAE@HHH@Z, retail 0x005D0D2D..0x005D0D85 (88 bytes, EH,
// RET 12): the base (EH state 0), vtable 0x00C75590, then the holder takes a
// new implementation built from the owner and the three arguments (state 1
// guards the allocation).
Rva005D0D85::Rva005D0D85(int a, int b, int c)
	: m_holder(new Rva005D0C87(this, a, b, c))
{
}

Rva005D0D85::~Rva005D0D85()
{
	m_holder.clear();
}
