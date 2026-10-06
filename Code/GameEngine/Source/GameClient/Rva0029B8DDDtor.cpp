// cl: /DNDEBUG /MD /EHsc
// ??1Rva0029B8DD@@UAE@XZ @0x0029B8DD 60B.
// Dtor stores vtable 0x7FD02C then StringBase wide +8 and narrow +4 via rowed releaseBuffer 0x36E70 0x36410 with EH prolog scope 0xB74AD9.
// Unlocks 0x0029B8C1. Caller 0x0029B8C4.
template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data; };

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva0029B8DD {
public: virtual ~Rva0029B8DD();
private:
	StringBase<char> m_4;
	StringBase<unsigned short> m_8;
};
Rva0029B8DD::~Rva0029B8DD() {}
