// cl: /MD
//
// ??0Rva004FA830@@QAE@ABV?$StringBase@D@@@Z @0x004FA815 27B: ctor of the
// opaque AsciiString-holder at vtable 0x008633A0. Retail stores the vtable
// then copy-constructs the member at +4 via pinned StringBase<char> copy
// 0x000365F0 and returns this (ret 4). Sibling dtor at 0x004FA830 plus
// deleting dtor at 0x005C4537 in AsciiStringFoldDeleters.cpp (/O1 /MD).
// Caller 0x004FAC21 forwards its own single arg here. Layout read from
// retail lea ecx,[esi+4].

template <typename T> class StringBase
{
	friend class Rva004FA830;
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


class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &s);

private:
	StringBase<char> m_s;
};

Rva004FA830::Rva004FA830(const StringBase<char> &s) : m_s(s)
{
}
