// ??0Rva006DE2C0@@QAE@XZ
// partial score=0.85 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva006DE2C0@@QAE@XZ @0x006DE2C0 (96B) and ??0Rva006DE390@@QAE@XZ @0x006DE390 (99B):
// AptValue-derived constructors that inline only the BfmeAptValue006DCD20(type) base
// ctor (SEType 3 and 0x0B; flag init, release-vector registration through
// g_releaseVectorAtE17710, vtable 0x00CEAED0) and then set a field mask in the flags
// at +4 and install the class's own vtable (0x00CEB19C / 0x00CEB1D8). Same recipe as
// Rva006DE480Siblings.cpp, without the hash member. Callers: Apt initializer 0x006DF470
// (sites 0x006DF47E / 0x006DF4EC...). Class identities unproven, address-named.

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


struct Rva006DGuard
{
	~Rva006DGuard() {}
};

#define RVA_APT_FLAG_CTOR(NAME, TYPE, KEEP, SET) \
	class NAME : public RvaAptValueBase \
	{ \
	public: \
		NAME(); \
		virtual ~NAME() {} \
		Rva006DGuard m_guard; \
	}; \
	NAME::NAME() : RvaAptValueBase(TYPE) \
	{ \
		m_flags = (m_flags & (KEEP)) | (SET); \
	}

RVA_APT_FLAG_CTOR(Rva006DE2C0, 0x03, 0xFFFFFFEFu, 0x3FFC0u)
RVA_APT_FLAG_CTOR(Rva006DE390, 0x0b, 0xFE07FFFFu, 0x7FFC0u)
