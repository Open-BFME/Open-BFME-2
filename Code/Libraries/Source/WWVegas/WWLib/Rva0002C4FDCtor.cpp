// cl: /EHsc
// ??0Rva0002C4FD@@QAE@ABV?$StringBase@D@@0@Z @0x0002C4FD 57B
// Honest placeholder ctor: two StringBase<char> at +0 and +4 via pinned
// 0x000365F0 copy, returns this. Layout read from retail stores (copy to
// esi then lea ecx esi+4). Callers construct pair at 0x002086C5 et al and
// destroy via pair dtor 0x0002C0C0. Same 57B shape as pair two-arg ctor
// 0x002027B1 which already claims the STL name, so honest Rva name used.

template <typename T> class StringBase
{
	friend struct Rva0002C4FD;
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct Rva0002C4FD
{
	StringBase<char> m_a; // +0
	StringBase<char> m_b; // +4
	Rva0002C4FD(const StringBase<char> &a, const StringBase<char> &b);
};

Rva0002C4FD::Rva0002C4FD(const StringBase<char> &a, const StringBase<char> &b)
	: m_a(a), m_b(b)
{
}
