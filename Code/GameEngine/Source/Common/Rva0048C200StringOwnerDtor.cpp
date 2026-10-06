// cl: /DNDEBUG /MD /EHsc
// ??1Rva0048C200Owner@@QAE@XZ, retail 0x002019E1, 54B.
// Dtor of two-String owner whose ctor is 0x00201998; calls releaseBuffer
// at +8 then +4 via inlined StringBase<char> member dtors with EH.
// Evidence: abuts ctor (0x00201998+73=0x002019E1), same flags, callees rowed.
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva0048C200Owner
{
public:
	~Rva0048C200Owner();
private:
	void *m_head00;
	StringBase<char> m_first04;
	StringBase<char> m_second08;
};

Rva0048C200Owner::~Rva0048C200Owner()
{
}

// ??1Rva0023DBC3@@QAE@XZ, retail 0x0023DBC3, 54 bytes: the same member teardown
// (two strings after a pointer) for another class of this layout; only the EH
// handler record differs from ~Rva0048C200Owner's bytes. Identity unknown.
class Rva0023DBC3
{
public:
	~Rva0023DBC3();
private:
	void *m_head00;
	StringBase<char> m_first04;
	StringBase<char> m_second08;
};
Rva0023DBC3::~Rva0023DBC3()
{
}
