// cl: /MD
// ??1Rva0031F831@@QAE@XZ @0x0031F831 9B dtor zeroes +8 then releases StringBase.
// Retail and [ecx+8],0 then jmp releaseBuffer 0x00036410. Evidence: unlock lane;
// caller 0x0031F856 is deleting dtor calling this as ??1; rowed releaseBuffer
// ?releaseBuffer@?$StringBase@D@@AAEXXZ; and-mem-zero idiom needs /O1.
template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
         T *m_data; };

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva0031F831 {
public: ~Rva0031F831();
private: StringBase<char> m_str;
         char m_pad[4];
         int m_8; };
Rva0031F831::~Rva0031F831()
{
	m_8 = 0;
}
