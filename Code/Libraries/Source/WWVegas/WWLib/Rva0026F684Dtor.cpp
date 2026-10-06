// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0026F684@@QAE@XZ @0x0026F684 227B
// Evidence: vtable 0x7FABF0; callers 0x0026F8BA deleting dtor plus unwind; members releaseBuffer StringBaseWide plus Rva00360D26Member plus vector AsciiString plus free plus Release_Ref
#include <vector>

#include "ascii_string.h"


class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct OpaqueRefPtr
{
	OpaqueRefCounted *m_ptr;
	~OpaqueRefPtr() { if (m_ptr) m_ptr->Release_Ref(); }
};

struct MallocPtr
{
	void *m_ptr;
	~MallocPtr() { if (m_ptr) free(m_ptr); }
};
void __cdecl free(void *p);

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class Rva0026F684
{
public:
	virtual ~Rva0026F684();
private:
	int m_04;
	AsciiString m_08;
	int m_0C;
	_STL::vector<AsciiString> m_10;
	MallocPtr m_1C;
	int m_20;
	int m_24;
	AsciiString m_28;
	AsciiString m_2C;
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	OpaqueRefPtr m_40;
	int m_44;
	OpaqueRefPtr m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	AsciiString m_6C;
	int m_70;
	AsciiString m_74;
	int m_78;
	AsciiString m_7C;
	Rva00360D26Member m_80;
	int m_84;
	int m_88;
	AsciiString m_8C;
};

Rva0026F684::~Rva0026F684()
{
	m_68 = 0;
	m_64 = 0;
	m_70 = 0;
}
