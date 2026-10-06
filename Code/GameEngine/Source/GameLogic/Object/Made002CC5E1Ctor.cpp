// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// stlport
//
// ??0Made002CC5E1@@QAE@XZ retail 0x00507C2D 343B
// DamageNugget ctor over rowed base Rva00507823 0x0050775B (vtable 0x00864010
// then derived vtable 0x00864048). Derived floats at +0x128/+0x130/+0x134
// zero plus -1.0f at +0x12C/+0x140/+0x144 via 0x00BBB9AC plus pi at +0x138
// via 0x00BC7468 plus 1.0f at +0x150/+0x198 via 0x00BBB8D8 plus ints
// 0x16 at +0x158 and 0x1D at +0x160 plus vector at +0x168 via rowed
// Vector_base 0x00211E58 plus 0x1C member at +0x178 via rowed 0x0024C7B3
// plus filter at +0x19C via pinned 0x003623E5 plus duplicate memset 0x1C
// at +0x178 plus two FixedStorage temps from 0x009FEFA4 via rowed copy
// 0x0004543D consumed by pinned initFromStorages 0x00362087. Evidence:
// base rowed 0x0050775B plus derived vtables 0x00864048/0x00864C38/
// 0x008650B8 plus callers parseDamageNugget 0x002CC606 plus derived
// Made002CCA37 0x0050B1FF and Made002CCCF3 0x0050BF92 call here.
#include <vector>
#include <string.h>

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper() { clear80(); }
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

extern unsigned char g_00DFEFA4StoragePrototype[28];

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);
private:
	int m_x;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
private:
	unsigned char m_data[0x1C];
};

#include "ascii_string.h"


// "DamageScalar" entries (Made002CC5E1DamageScalar.cpp): a filter handle
// plus a Real; the 8-byte stride is read off push_back 0x0050882B.
struct Made002CC5E1DamageScalar
{
	Rva003623E5Member filter;
	float scalar;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
private:
	Rva001EAE6FHelper m_bits04;
	Rva001EAE6FHelper m_bits84;
	int m_104;
	_STL::vector<AsciiString> m_vec108;
	_STL::vector<AsciiString> m_vec114;
	Rva003623E5Member m_filter120;
	bool m_124;
};

class Made002CC5E1 : public Rva00507823
{
public:
	Made002CC5E1();
private:
	float m_128;
	float m_12C;
	float m_130;
	float m_134;
	float m_138;
	bool m_13C;
	char m_pad13D[3];
	float m_140;
	float m_144;
	bool m_148;
	char m_pad149[3];
	float m_14C;
	float m_150;
	int m_154;
	int m_158;
	int m_15C;
	int m_160;
	int m_164;
	_STL::vector<Made002CC5E1DamageScalar> m_vec168;
	float m_174;
	Rva0024C7B3Member m_178;
	bool m_194;
	char m_pad195[3];
	float m_198;
	Rva003623E5Member m_19C;
	bool m_1A0;
};

Made002CC5E1::Made002CC5E1()
	: m_128(0.0f)
	, m_12C(-1.0f)
	, m_130(0.0f)
	, m_134(0.0f)
	, m_138(3.1415927f)
	, m_13C(false)
	, m_140(-1.0f)
	, m_144(-1.0f)
	, m_148(true)
	, m_14C(0.0f)
	, m_150(1.0f)
	, m_154(0)
	, m_158(0x16)
	, m_15C(0)
	, m_160(0x1D)
	, m_164(0)
	, m_174(0.0f)
	, m_194(false)
	, m_198(1.0f)
	, m_1A0(false)
{
	memset(&m_178, 0, 0x1C);
	m_19C.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)));
}
