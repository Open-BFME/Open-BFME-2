// cl: /DNDEBUG /MD /EHsc
// ??1Rva0029B816@@UAE@XZ @0x0029B816 98B.
// Dtor vtable 0x7FD028: free ptrs +4 +8 via global 0xDFEAD8 slot 0x3C then narrow StringBase +0x14 via 0x36410 with EH scope 0xB74AC4.
// Unlocks 0x0029E1EF. Caller 0x0029E1F2.
extern class DisplayStringManager *TheDisplayStringManager;

template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data; };

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva0029B816Holder {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(void *p);
};
class Rva0029B816 {
public: virtual ~Rva0029B816();
private:
	void *m_4;
	void *m_8;
	char m_padC[8];
	StringBase<char> m_14;
};
Rva0029B816::~Rva0029B816()
{
	if (m_4 != 0)
		(*(Rva0029B816Holder **)&TheDisplayStringManager)->s15(m_4);
	m_4 = 0;
	if (m_8 != 0)
		(*(Rva0029B816Holder **)&TheDisplayStringManager)->s15(m_8);
	m_8 = 0;
}
