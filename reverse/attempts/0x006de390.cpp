// ??0Rva006DE390@@QAE@XZ
// partial score=0.45 date=2026-10-10
// Bank contains both related variants; neither is a landed recovery.
// cl: /O2 /arch:SSE /DNDEBUG /MD /EHsc
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

class BfmeAptValue006DCD20
{
	void setTypeAt006DBBC0(int type)
	{
		m_flags = (m_flags & 0x01ffffffu) | (static_cast<unsigned int>(type) << 25);
	}
protected:
	unsigned int m_flags;
public:
	__forceinline BfmeAptValue006DCD20(int type)
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
	virtual ~BfmeAptValue006DCD20();
};

class Rva006DE2C0 : public BfmeAptValue006DCD20
{
public:
 Rva006DE2C0();
 virtual ~Rva006DE2C0();
};
Rva006DE2C0::Rva006DE2C0() : BfmeAptValue006DCD20(3)
{
 m_flags=(m_flags & 0xffffffefu) | 0x0003ffc0u;
}
class Rva006DE390 : public BfmeAptValue006DCD20
{
public:
 Rva006DE390();
 virtual ~Rva006DE390();
};
Rva006DE390::Rva006DE390() : BfmeAptValue006DCD20(11)
{
 m_flags=(m_flags & 0xfe07ffffu) | 0x0007ffc0u;
}
