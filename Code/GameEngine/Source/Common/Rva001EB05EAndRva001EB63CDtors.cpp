// cl: /O1 /G7 /EHsc /MD
//
// Address-derived record views. Retail 0x001EB05E tears down a narrow string
// at +0x10, then a wide string at +0x0C. Retail 0x001EB63C is called by the
// 28-byte deleting wrapper at 0x002AD057 and is used with 0xD8-byte elements
// by 0x002AE5CF. Its bytes tear down narrow strings at +0xD4 and +0xD0, then
// call 0x001EB05E on the subobject at +0xB0. The record's identity and the
// prefix fields remain unknown.

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	T *m_data;
};

template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

class Rva001EB05E
{
public:
	~Rva001EB05E();

private:
	unsigned char m_prefix[0x0C];
	StringBase<unsigned short> m_wideString;
	StringBase<char> m_narrowString;
	unsigned char m_tail[0x0C];
};

Rva001EB05E::~Rva001EB05E()
{
}

class Rva001EB63C
{
public:
	~Rva001EB63C();

private:
	unsigned char m_unknown[0xB0];
	Rva001EB05E m_subobject;
	StringBase<char> m_narrowStringD0;
	StringBase<char> m_narrowStringD4;
};

Rva001EB63C::~Rva001EB63C()
{
}
