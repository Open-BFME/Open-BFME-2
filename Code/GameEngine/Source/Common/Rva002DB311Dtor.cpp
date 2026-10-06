// cl: /MD /EHsc
// ??1Rva002DB311@@UAE@XZ @0x002DB311 318B
// Evidence: unlock lane; vtable g_00C03E24; callees clear 0x0048BA39 releaseBuffer 0x00036410 TailRecord dtor 0x0010F149 and ??_M CRT; 11 singles + 7 arrays to 0x144.
extern const void *const g_00C03E24[];
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
	void clear();
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class AsciiElem
{
public:
	~AsciiElem() { ((StringBase<char> *)this)->clear(); }
private:
	void *m_data;
};
class OpaqueRefCounted
{
public:
	void Release_Ref();
};
class BfmeStringTailRecord156
{
public:
	~BfmeStringTailRecord156();
private:
	OpaqueRefCounted *m_ptr;
};
class Rva002DB311
{
public:
	virtual ~Rva002DB311();
	StringBase<char> m_04;
	char m_pad08[0x18];
	StringBase<char> m_20;
	StringBase<char> m_24;
	char m_pad28[0xC];
	StringBase<char> m_34;
	StringBase<char> m_38;
	StringBase<char> m_3C;
	StringBase<char> m_40;
	StringBase<char> m_44;
	StringBase<char> m_48;
	StringBase<char> m_4C;
	StringBase<char> m_50;
	AsciiElem m_54[4];
	BfmeStringTailRecord156 m_64[4];
	AsciiElem m_74[12];
	AsciiElem m_A4[12];
	BfmeStringTailRecord156 m_D4[4];
	AsciiElem m_E4[12];
	AsciiElem m_114[12];
};
Rva002DB311::~Rva002DB311()
{
}
