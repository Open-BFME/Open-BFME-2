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

extern "C" const void *const vtbl_00BBB554[];  // folded, 23 classes; via ??_7BfmeBaseVUQ@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBB554=??_7BfmeBaseVUQ@@6B@")

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BBB554));
}

class Rva001E3E43 : public Snapshot
{
public:
	virtual ~Rva001E3E43();
	Rva001E3E43 &operator=(const Rva001E3E43 &rhs);
private:
	int m_04;
	struct Vec12 { int a, b, c; } m_08, m_14;
	int m_20, m_24, m_28, m_2C;
	int m_30, m_34, m_38, m_3C, m_40, m_44, m_48, m_4C;
	int m_50, m_54, m_58, m_5C, m_60, m_64;
	struct Reg16 {
		int a, b, c, d;
	} m_68, m_78, m_88;
	unsigned char m_98, m_99, m_9A;
	int m_9C, m_A0, m_A4, m_A8, m_AC;
};

extern int g_Va00DFDC64;
// g_Va00DFDC64: matched references place it at VA 0xdfdc64 (zero-filled .bss).
int g_Va00DFDC64;

Rva001E3E43::~Rva001E3E43()
{
	--g_Va00DFDC64;
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
		m_68.a = rhs.m_68.a;
		m_68.b = rhs.m_68.b;
		m_68.c = rhs.m_68.c;
		m_68.d = rhs.m_68.d;
		{
			const int *src = (const int *)&rhs.m_78;
			int *dst = (int *)&m_78;
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
		}
		{
			const int *src = (const int *)&rhs.m_88;
			int *dst = (int *)&m_88;
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
