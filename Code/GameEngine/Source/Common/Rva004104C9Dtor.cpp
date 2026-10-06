// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/stringinline
//
// ??1Rva004104C9@@QAE@XZ, retail 0x004104C9, 53 bytes. Unlock lane: pair of
// AsciiString at +0 and Rva0045EF90Object at +4. Ctor 0x004106C1 builds the
// same pair from two const refs (ret 8); dtor destroys +4 via rowed
// ??1Rva0045EF90Object@@UAE@XZ then releases +0 via rowed
// ?releaseBuffer@?$StringBase@D@@AAEXXZ (0x00036410). Callers 0x004105AB,
// 0x00410983, 0x00411278 destroy stack temps of this type.

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

typedef StringBase<char> AsciiString;

class Rva0045EF90Object
{
public:
	virtual ~Rva0045EF90Object();
};

class Rva004104C9 : private StringBase<char>
{
public:
	~Rva004104C9();
private:
	Rva0045EF90Object m_obj;
};

Rva004104C9::~Rva004104C9()
{
}
