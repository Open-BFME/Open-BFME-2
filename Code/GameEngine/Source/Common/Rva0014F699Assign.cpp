// cl: /O1
// ??4Rva0014F699@@QAEAAV0@ABV0@@Z @0x0014F699 127B; copy-assignment over 0x4C-byte element with RefCountPtr at +0x48.
// Retail: mov eax [esp+4] / push esi / mov esi ecx / 17 dword copies +4..+44 / add eax 0x48 / push eax / lea ecx [esi+0x48] / call 0x424D0 RefCountPtr assign / mov eax esi / pop esi / ret 4.
// Target facts: this in ecx; source on stack; +0 vptr not copied; 17 dwords +4..+44 via mov; +48 via rowed ??4?$RefCountPtr@VTextureClass@@@@QAEABV0@ABV0@@Z; returns this; size 0x4C proven by callers 0x0014F746 0x0014FA2A 0x0014FA90 idiv/add loops.
// Callers: 0x0014F76A 0x0014FA37 0x0014FAAC; callees: 0x000424D0.
// Not established: owning class identity; names are address-derived.
// ??1Rva0014F699@@UAE@XZ @0x0014D1E3 52B: dtor releasing RefCountPtr at +0x48 via Release_Ref and restoring vtable 0x007C6F24. Evidence: same 0x4C element; rowed Release_Ref 0x0061ED10; callers at 0x0014DC42 0x001505A9 0x00150A2F 0x00150BE3.
// class-gate: allow Snapshot private single-virtual base for 0x0014D1E3 vtable 0x007C6F24; shared Snapshot.h is 4-slot BBB554 canonical base and gives wrong vtable and slots here.
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &other);
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

extern const void *const g_00BC6F24[];

class Snapshot
{
public:
  virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = (const void *)g_00BC6F24;
}

class __declspec(novtable) Rva0014F699 : public Snapshot
{
public:
	virtual ~Rva0014F699();
	Rva0014F699 &operator=(const Rva0014F699 &other);
private:
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	RefCountPtr<TextureClass> m_48;
};

Rva0014F699 &Rva0014F699::operator=(const Rva0014F699 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2c = other.m_2c;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_3c = other.m_3c;
	m_40 = other.m_40;
	m_44 = other.m_44;
	m_48 = other.m_48;
	return *this;
}

inline Rva0014F699::~Rva0014F699()
{
}

#pragma inline_depth(0)
// ?_bfmeRva0014F699Anchor present-unmatched
void _bfmeRva0014F699Anchor(Rva0014F699 *p) { p->Rva0014F699::~Rva0014F699(); }
#pragma inline_depth()
