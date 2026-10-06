// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ??1Rva002E5791@@QAE@XZ 0x002E5791 53B
// Evidence: EH dtor calls wide releaseBuffer 0x00036E70 at +4 then narrow 0x00036410 at +0; prev Rva002E5711Dtor; unblocks 0x002E5E5A.
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


class Rva002E5791
{
public:
	~Rva002E5791();

private:
	StringBase<char> m_narrow;
	StringBase<unsigned short> m_wide;
};

Rva002E5791::~Rva002E5791()
{
}
