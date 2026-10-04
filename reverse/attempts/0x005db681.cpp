// ??1Rva005DB681@@UAE@XZ
// partial score=0.93 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva005DB681@@UAE@XZ @0x005DB681 89B. Dtor with vtable 0x876798 at +0,
// member CreateAHeroData at +0x58 with vtable 0x87678C then 0x8711BC,
// conditional rva002B7250 via global g_00E063F8, base dtor 0x5248D0 pinned.
// Caller 0x005DB7F5 unblocks 0x005DB7F2.
extern const void *const g_00C76798[];
extern const void *const g_00C7678C[];
extern const void *const g_00C711BC[];
extern void *g_00E063F8;

class CreateAHeroData
{
public:
	virtual void _M_slot_00();
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *p);
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva005DB681 : public Rva005248D0
{
public:
	virtual ~Rva005DB681();
private:
	char m_pad[0x58 - 4];
	CreateAHeroData m_58;
};

// ??1Rva005DB681@@UAE@XZ present-unmatched
Rva005DB681::~Rva005DB681()
{
	*(const void **)this = g_00C76798;
	*(const void **)((char *)this + 0x58) = g_00C7678C;
	if (g_00E063F8)
		((Rva002B7250 *)((char *)g_00E063F8 + 0x2C))->rva002B7250((CreateAHeroData *)((char *)this + 0x58));
	*(const void **)((char *)this + 0x58) = g_00C711BC;
}
