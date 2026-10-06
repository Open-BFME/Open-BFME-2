// ??4Rva0051F6DF@@QAEAAV0@ABV0@@Z
// Seat-4 finish pass from the 0.96 bank
// ??4Rva0051F6DF@@QAEAAV0@ABV0@@Z
// partial score=0.9 date=2026-09-29
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??4Rva0051F6DF@@QAEAAV0@ABV0@@Z @0x0051F6DF 206B
// Vector operator= for 20-byte Rva0039B893: self-check, realloc via rowed
// 0x0051ED51 plus tidy 0x00565A42 when otherSize exceeds capacity, else
// copy via rowed 0x0039BD9BCopy plus destroy 0x0022C8E3 or uninit-copy 0x0039BA22.
// Evidence: chain lane, callers at 0x0051F9A5/0x005208C5, twin tags at
// ebp+0xb matching landed 0x0039C190. Owning class unproven.

class Rva0039B893
{
public:
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();
	int m_field04;
	int m_field08;
	short m_field0C;
	short m_field0E;
	short m_field10;
	char m_pad12[2];
};

struct Rva0052BF9BElem;
namespace _STL { struct __false_type { }; }

void __cdecl Rva0039BD9BCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result);
void __cdecl Rva0022C8E3DestroyRange(Rva0052BF9BElem *first, Rva0052BF9BElem *last);
Rva0039B893 *__cdecl Rva0039BA22UninitCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const _STL::__false_type &tag);

class Rva0051ED51Holder
{
public:
	Rva0039B893 *rva0051ED51(unsigned int n, Rva0039B893 *first, Rva0039B893 *last);
};

class Rva00565A42
{
public:
	void rva00565A42();
};

class Rva0051F6DF
{
public:
	Rva0051F6DF &operator=(const Rva0051F6DF &other);

private:
	Rva0039B893 *m_start;
	Rva0039B893 *m_finish;
	Rva0039B893 *m_end;
};

typedef Rva0039B893 *(__cdecl *Copy4Fn)(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, void *tag);

Rva0051F6DF &Rva0051F6DF::operator=(const Rva0051F6DF &other)
{
	if (&other == this)
		return *this;
	Rva0039B893 *otherFinish = other.m_finish;
	unsigned otherSize = otherFinish - other.m_start;
	unsigned cap = m_end - m_start;
	// The copy tag is its own stack object. Deriving it from another local's
	// address (the banked attempt used (char *)&otherFinish + 15) ties its
	// frame slot to that local's, so the compiler places the two adjacently and
	// the lea displacements move together; retail keeps them independent.
	const _STL::__false_type tag;
	if (otherSize > cap) {
		Rva0039B893 *newStart = ((Rva0051ED51Holder *)this)->rva0051ED51(otherSize, other.m_start, otherFinish);
		((Rva00565A42 *)this)->rva00565A42();
		m_start = newStart;
		m_end = newStart + otherSize;
	} else {
		unsigned thisSize = m_finish - m_start;
		if (thisSize >= otherSize) {
			Rva0039B893 *newEnd = (Rva0039B893 *)((Copy4Fn)Rva0039BD9BCopy)(other.m_start, otherFinish, m_start, (void *)&tag);
			Rva0022C8E3DestroyRange((Rva0052BF9BElem *)newEnd, (Rva0052BF9BElem *)m_finish);
		} else {
			Rva0039B893 *mid = other.m_start + thisSize;
			((Copy4Fn)Rva0039BD9BCopy)(other.m_start, mid, m_start, (void *)&tag);
			unsigned thisSize2 = m_finish - m_start;
			Rva0039B893 *mid2 = other.m_start + thisSize2;
			// Re-read other.m_finish at the call site rather than reusing the
			// spilled otherFinish local: retail pushes [edi+0x4] here, which is
			// the field itself, not the frame slot holding a copy of it.
			Rva0039BA22UninitCopy(mid2, other.m_finish, m_finish, tag);
		}
	}
	m_finish = m_start + otherSize;
	return *this;
}
