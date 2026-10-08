// ??0Rva006DE2C0@@QAE@XZ
// partial score=0.75 date=2026-10-08
// cl: /DNDEBUG /MD /EHa
//
// Six AptValue-derived constructors at 0x006DE480, 0x006DE510, 0x006DE5A0,
// 0x006DE630, 0x006DE6D0 and 0x006DE790 (138 bytes each).
//
// Evidence: each body inlines the BfmeAptValue006DCD20(type) base ctor -- the
// SEType flag init plus the release-vector registration through
// g_releaseVectorAtE17710 at VA 0x00E17710 and vtable VA 0x00CEAED0 -- then the
// Rva006D6360(type,size) base ctor (vtable VA 0x00CEA228, AptNativeHash member
// at +8 constructed by ??0AptNativeHash@@QAE@H@Z at 0x0070A740), then a
// non-polymorphic bits base whose ctor clears byte +0x1C and bits 8-9 of the
// dword at +0x1C, then sets bit 18 of the AptValue flags at +4 and installs the
// class's own vtable.
//
// Callers are the six construction sites 0x006DF53E, 0x006DF575, 0x006DF5AC,
// 0x006DF5E3, 0x006DF61A, 0x006DF651: each allocates 0x20 bytes from the
// 0x00E176F4 pool (0x006D29E0) and stores the object into a global (0x00E18070,
// 0x00E180B8, 0x00E18068, 0x00E180BC, 0x00E18650, 0x00E18360). The class
// identities are unproven, so they are address-named. The base classes are
// local names; their vtable stores are DIR32 operands and auto-patch to the
// target's 0x00CEAED0 / 0x00CEA228. Per class the target fixes the folded type
// constant, the hash size and the final vtable VA:
//
//   Rva006DE480  type 0x17  hash  8  vtable 0x00CEB214
//   Rva006DE510  type 0x18  hash  8  vtable 0x00CEB250
//   Rva006DE5A0  type 0x1f  hash  8  vtable 0x00CEB28C
//   Rva006DE630  type 0x19  hash 11  vtable 0x00CEB2C8
//   Rva006DE6D0  type 0x26  hash  8  vtable 0x00CEB304
//   Rva006DE790  type 0x27  hash  8  vtable 0x00CEB340

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};

class AptValueVector
{
public:
	void rva006E6C00(AptValue *pValue);
};

// VA 0x00E17710; defined by AptValueConstructorBFME2.cpp.
extern AptValueVector *g_releaseVectorAtE17710;

class RvaAptValueBase
{
	void setTypeAt006DBBC0(int type)
	{
		m_flags = (m_flags & 0x01ffffffu) | (static_cast<unsigned int>(type) << 25);
	}
protected:
	unsigned int m_flags;
public:
	RvaAptValueBase(int type)
	{
		setTypeAt006DBBC0(type);
		m_flags = (m_flags & 0xFE000035u) | 0x30u;
		if (type == 0x1c || type == 0x2b || type == 0x2c)
			m_flags &= ~4u;
		else {
			m_flags |= 4u;
			g_releaseVectorAtE17710->rva006E6C00(reinterpret_cast<AptValue *>(this));
		}
	}
	virtual ~RvaAptValueBase() {}
};

class AptNativeHash
{
	int mnTotalSize;
	AptValue *mpData;
	AptValue *mp__proto__;
	AptValue *mpPrototype;
	unsigned int nEventHandlers;
public:
	AptNativeHash(int size);
};

class Rva006D6360Base : public RvaAptValueBase
{
public:
	Rva006D6360Base(int type, int size) : RvaAptValueBase(type), m_hash(size) {}
	virtual ~Rva006D6360Base() {}
	AptNativeHash m_hash;
};

// Non-polymorphic bits base: keeping its clear code in its own inline ctor is
// what makes cl emit the memory form of the +0x1C mask rather than a register
// load/store pair.
class Rva006DBits
{
protected:
	unsigned int m_bits;
public:
	Rva006DBits()
	{
		*(unsigned char *)&m_bits = 0;
		m_bits &= 0xFFFFFCFF;
	}
};

#define RVA_APT_CTOR(NAME, TYPE, SIZE) \
	class NAME : public Rva006D6360Base, public Rva006DBits \
	{ \
	public: \
		NAME(); \
		virtual ~NAME() {} \
	}; \
	NAME::NAME() : Rva006D6360Base(TYPE, SIZE), Rva006DBits() \
	{ \
		m_flags = (m_flags & 0xFE07FFFFu) | 0x40000u; \
	}

RVA_APT_CTOR(Rva006DE480, 0x17, 8)
RVA_APT_CTOR(Rva006DE510, 0x18, 8)
RVA_APT_CTOR(Rva006DE5A0, 0x1f, 8)
RVA_APT_CTOR(Rva006DE630, 0x19, 0xb)
RVA_APT_CTOR(Rva006DE6D0, 0x26, 8)
RVA_APT_CTOR(Rva006DE790, 0x27, 8)

// Target-only simple AptValue-derived constructors. Native bodies at
// 0x006DE2C0..0x006DE320 and 0x006DE390..0x006DE3F3 inline the same
// release-vector-registering base above, with types 3 and 11 respectively.
// Each then changes only the +4 flag bits and installs its own vtable
// (VA 0x00CEB19C / 0x00CEB1D8). Original derived class identities are unknown.
class Rva006DE2C0 : public RvaAptValueBase
{
public:
    Rva006DE2C0();
    virtual ~Rva006DE2C0() {}
};
Rva006DE2C0::Rva006DE2C0() : RvaAptValueBase(3)
{
    m_flags = (m_flags & 0xFFFFFFEFu) | 0x3FFC0u;
}

class Rva006DE390 : public RvaAptValueBase
{
public:
    Rva006DE390();
    virtual ~Rva006DE390() {}
};
Rva006DE390::Rva006DE390() : RvaAptValueBase(11)
{
    m_flags = (m_flags & 0xFE07FFFFu) | 0x7FFC0u;
}
