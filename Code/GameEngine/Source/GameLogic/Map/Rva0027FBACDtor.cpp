// cl: /DNDEBUG /MD /EHsc
// ??1Rva0027FBAC@@UAE@XZ @0x0027FBAC 82B. Dtor stores vtable 0x00BFB1E0,
// null-checked delete of +0xC8 via first virtual with int arg 0 returning
// pointer freed by rowed ??3@YAXPAX@Z, then releases AsciiString at +8 via
// rowed ?releaseBuffer@?$StringBase@D@@AAEXXZ. Caller 0x00280C05 is its ??_G.
template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
         T *m_data; };

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

typedef StringBase<char> AsciiString;

class Rva0027FBACHelper {
public: virtual void *Get(int);
};

class Rva0027FBAC {
public: virtual ~Rva0027FBAC();
private: char m_pad04[4];
         AsciiString m_str;
         char m_pad0C[188];
         Rva0027FBACHelper *m_c8;
};
Rva0027FBAC::~Rva0027FBAC()
{
	if (m_c8) {
		::operator delete(m_c8->Get(0));
		m_c8 = 0;
	}
}
