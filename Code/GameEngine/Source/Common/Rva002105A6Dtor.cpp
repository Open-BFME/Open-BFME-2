// cl: /EHs /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva002105A6@@UAE@XZ @ 0x002105A6 94B
// ModuleData-style dtor with Snapshot base restore to 0x00BBB554. Evidence:
// vector<AsciiString> at +0x20 via rowed dtor 0x0002CC70; C-string free at
// +0x2C via rowed _free 0x00030830; AsciiString teardown at +0x38 plus 0x44
// via folded releaseBuffer 0x00036410; Snapshot restore at +0x04 to BBB554
// via Snapshot ctor row 0x000053A6; callers 0x00210607 0x002108BF 0x00210B1F;
// layout from sibling clear 0x00210749.

#include <vector>

extern "C" void __cdecl free(void *p);

template <class T> class StringBase
{
	void *m_data;
	void releaseBuffer();
public:
	~StringBase() { releaseBuffer(); }
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class AsciiString
{
public:
	AsciiString();
	~AsciiString();
private:
	void *m_data;
};

extern const void *const g_00BBB554[];

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BBB554;
}

struct FreedPtr
{
	void *m_ptr;
	~FreedPtr() { if (m_ptr) free(m_ptr); }
};

class __declspec(novtable) Rva002105A6
{
public:
	virtual ~Rva002105A6();
private:
	Snapshot m_snap;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	_STL::vector<AsciiString> m_vec20;
	FreedPtr m_ptr2C;
	char m_pad30[8];
	StringBase<char> m_str38;
	char m_pad3C[8];
	StringBase<char> m_str44;
};

Rva002105A6::~Rva002105A6()
{
}
