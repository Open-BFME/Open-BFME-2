// cl: /MD
//
// ??1Rva001E3E43@@UAE@XZ, retail 0x001E3E43, 19 bytes.
// Scalar dtor: stores derived vtable 0x00BDE888, dec global 0x00DFDC64,
// restores Snapshot base vtable 0x00BBB554. Called by deleting dtor
// at 0x001E4625 (push esi / call 0x1E3E43 / test [esp+8],1 / delete).
// Owner identity unproven, honest Rva name.
//
// ??4Rva001E3E43@@QAEAAV0@ABV0@@Z, retail 0x001E3CF4, 335 bytes.
// Copy assignment: self-check, copies all except vptr 0x00BDE888, returns this.
// Evidence: caller copy-ctor 0x001E4641 constructs 3x0x10 array at +0x68 via
// vector iterator then calls it; vtable/global match Rva001E3E43; unblocks 0x001E4641.


class Xfer;

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"


// Rva001E3E43CopyCtor.cpp's view of the class and its 16-byte +0x68 elements
// (spelled identically so a merged unit emits one).
class Rva001E3E43Element
{
public:
	Rva001E3E43Element();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Rva001E3E43 : public Snapshot
{
public:
	~Rva001E3E43();
	Rva001E3E43(const Rva001E3E43 &rhs);
	Rva001E3E43 &operator=(const Rva001E3E43 &rhs);
private:
	int m_04;
	struct Vec12 { int a, b, c; } m_08, m_14;
	int m_20, m_24, m_28, m_2C;
	int m_30, m_34, m_38, m_3C, m_40, m_44, m_48, m_4C;
	int m_50, m_54, m_58, m_5C, m_60, m_64;
	Rva001E3E43Element m_68[3];
	unsigned char m_98, m_99, m_9A;
	int m_9C, m_A0, m_A4, m_A8, m_AC;
};

extern int g_Va00DFDC64;
// g_Va00DFDC64: matched references place it at VA 0xdfdc64 (zero-filled .bss).
int g_Va00DFDC64;

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva001E3E43::~Rva001E3E43()
{
	--g_Va00DFDC64;
}

// ?bfmeAnchorRva001E3E43Dtor absent-from-retail
void bfmeAnchorRva001E3E43Dtor(Rva001E3E43 *p)
{
	p->Rva001E3E43::~Rva001E3E43();
}

Rva001E3E43 &Rva001E3E43::operator=(const Rva001E3E43 &rhs)
{
	if (this != &rhs) {
		m_04 = rhs.m_04;
		m_08 = rhs.m_08;
		m_14 = rhs.m_14;
		m_20 = rhs.m_20;
		m_24 = rhs.m_24;
		m_28 = rhs.m_28;
		m_30 = rhs.m_30;
		m_34 = rhs.m_34;
		m_38 = rhs.m_38;
		m_3C = rhs.m_3C;
		m_40 = rhs.m_40;
		m_44 = rhs.m_44;
		m_48 = rhs.m_48;
		m_4C = rhs.m_4C;
		m_50 = rhs.m_50;
		m_54 = rhs.m_54;
		m_58 = rhs.m_58;
		m_5C = rhs.m_5C;
		m_60 = rhs.m_60;
		m_64 = rhs.m_64;
		{
			const int *src = (const int *)&rhs.m_68[0];
			int *dst = (int *)&m_68[0];
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
		}
		{
			const int *src = (const int *)&rhs.m_68[1];
			int *dst = (int *)&m_68[1];
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
		}
		{
			const int *src = (const int *)&rhs.m_68[2];
			int *dst = (int *)&m_68[2];
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
		}
		m_98 = rhs.m_98;
		m_99 = rhs.m_99;
		m_9C = rhs.m_9C;
		m_A0 = rhs.m_A0;
		m_A4 = rhs.m_A4;
		m_2C = rhs.m_2C;
		m_9A = rhs.m_9A;
		m_A8 = rhs.m_A8;
		m_AC = rhs.m_AC;
	}
	return *this;
}
