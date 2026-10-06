// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0026F684@@QAE@XZ @0x0026F5B3 209B
// Evidence: same vtable 0x7FABF0 as dtor 0x0026F684 in Rva0026F684Dtor.cpp; prev stlport_vector_4b_assign; next is own dtor; Rva003623E5Member pin 0x003623E5 at +0x80; vectors E16 bases via 0x00211E58
#include <vector>

#include "ascii_string.h"


struct BfmeE16
{
	float x, y, z, w;
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct OpaqueRefPtr
{
	OpaqueRefCounted *m_ptr;
	OpaqueRefPtr() : m_ptr(0) {}
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

class Rva003623E5Member
{
public:
	Rva003623E5Member();
};

class Rva0026F684
{
public:
	Rva0026F684();
	virtual ~Rva0026F684();
private:
	int m_04;
	AsciiString m_08;
	int m_0C;
	_STL::vector<BfmeE16> m_10;
	_STL::vector<BfmeE16> m_1C;
	AsciiString m_28;
	AsciiString m_2C;
	float m_30;
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
	unsigned char m_78;
	unsigned char m_79;
	AsciiString m_7C;
	Rva003623E5Member m_80;
	int m_84;
	int m_88;
	AsciiString m_8C;
	int m_90;
	unsigned char m_94;
	int m_98;
};

Rva0026F684::Rva0026F684()
	: m_04(0)
	, m_08()
	, m_0C(0)
	, m_10(_STL::allocator<BfmeE16>())
	, m_1C(_STL::allocator<BfmeE16>())
	, m_28()
	, m_2C()
	, m_30(0.0f)
	, m_34(0)
	, m_38(-1)
	, m_3C()
	, m_40()
	, m_44(-1)
	, m_48()
	, m_4C(-1)
	, m_50(-1)
	, m_54(-1)
	, m_58(-1)
	, m_5C(-1)
	, m_60(-1)
	, m_64(0)
	, m_68(0)
	, m_6C()
	, m_70(0)
	, m_74()
	, m_78(0)
	, m_79(0)
	, m_7C()
	, m_80()
	, m_84(0)
	, m_88(0)
	, m_8C()
	, m_90(0)
	, m_94(0)
	, m_98(-1)
{
}
