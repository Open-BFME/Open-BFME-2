// cl: /O1 /EHsc /MD
// ?rva004482B7@Rva004482B7@@QAE?AV?$StringBase@G@@H@Z retail 0x004482B7 40B
// By-value accessor: copy-construct StringBase<unsigned short> from
// m_items[index].m_name (0x1D0-wide records at +0x10C) through the rowed
// StringBase<unsigned short> copy ctor 0x00037050 and return it through the
// hidden return buffer. Evidence: callers 0x004482AB 0x0044AF50 0x0044B076
// 0x0044B0CE read the returned m_data; sibling accessor 0x00448280 copies
// this+0xF64 the same way; the non-trivial destructor is what makes retail
// keep the /EHsc frame and its `and dword ptr [ebp-4],0` state slot.
template <typename T> class StringBase
{
	friend class Rva004482B7;
	friend class Rva00448280;
	StringBase(const StringBase &that);
	~StringBase();
	T *m_data;
};

struct Rva004482B7Elem
{
	StringBase<unsigned short> m_name;
	char m_rest[0x1CC];
};

class Rva004482B7
{
	char m_pad[0x10C];
	Rva004482B7Elem m_items[8];

public:
	StringBase<unsigned short> rva004482B7(int index);
	StringBase<unsigned short> rva0044829E();
};

StringBase<unsigned short> Rva004482B7::rva004482B7(int index)
{
	return m_items[index].m_name;
}

// ?rva0044829E@Rva004482B7@@QAE?AV?$StringBase@G@@XZ @0x0044829E (25B):
// Zero-index wrapper over rva004482B7: by-value return through the hidden
// buffer with fixed index 0. Evidence: calls rowed 0x4482B7 with push 0;
// same /O1 /EHsc /MD frame with `and [ebp-4],0`.
StringBase<unsigned short> Rva004482B7::rva0044829E()
{
	return rva004482B7(0);
}

// ?rva00448280@Rva00448280@@QAE?AV?$StringBase@G@@XZ @0x00448280 (30B):
// Sibling by-value accessor copying m_wide at +0xF64 (Rva004482FB layout:
// base 0xDC plus 8x0x1D0 plus gap 8) through rowed copy ctor 0x37050.
// Evidence: prev/next neighbours; same frame as rva004482B7.
class Rva00448280
{
	char m_pad[0xF64];

public:
	StringBase<unsigned short> rva00448280();

private:
	StringBase<unsigned short> m_wide;
};

StringBase<unsigned short> Rva00448280::rva00448280()
{
	return m_wide;
}
