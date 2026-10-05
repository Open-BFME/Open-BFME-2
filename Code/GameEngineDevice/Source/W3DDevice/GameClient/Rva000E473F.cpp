// cl: /O1 /MD /EHsc
// Cursor-slot render helper: release (0x000E473F, 93B) plus reinit
// (0x000E479C, 234B). Both take the DX8 device mutex around their work.
// The reinit drops any live vertex/index buffers through the release body,
// allocates a 32-byte BfmeDynamicNativeVB (0x152, 0x3A9C, 1, 0) and a 24-byte
// DX8IndexBufferClass (0x7534, USAGE_DYNAMIC), zeroes two words, refills the
// embedded texture slot, and when the slot holds a surface, fetches its
// level-0 reset surface and draws one 0x7F7FFF pixel at (0, 0) before
// raising the +0x22 ready flag.
//
// Target facts (read-only retail decode this seat): both bodies open with
// mov eax,imm32 plus call __EH_prolog (0x00629188), save this in esi behind
// BFME_DX8_Thread_Lock (0x0011F520), and close with BFME_DX8_Thread_Assert
// (0x00120F50). The release repeats the REF_PTR_RELEASE shape (test, dec
// [ecx+4], jne, call [eax] slot 0, and-zero) for +0x04 and +0x08, then
// BfmeResetTextureRef::clear (0x0004D75B) on +0x14. The reinit calls the
// release when +0x04 or +0x08 is live, runs operator new (0x0002FDA0) for
// 0x20/0x18 bytes with the standard new-expression EH states 1/2, calls the
// 6-arg slot refill (0x00131DFC) on +0x14, checks the slot head, fetches
// CursorTextureSlot::Get_Surface_Level (0x00132D70) into an ebp-0x10 holder,
// calls SurfaceClass::DrawPixel (0x00116C30) on it with (0, 0, 0x7F7FFF),
// destroys the holder via W3DRadarResetSurface::~ (0x00176CB0), and sets
// [esi+0x22]. Class and member names are address-derived; the slot view
// (reset-ref base, cursor-slot middle, refill tail) is inferred from the
// three co-located calls sharing one unadjusted this, not from a header.

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *) throw();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

struct SurfaceClass
{
	void DrawPixel(unsigned int x, unsigned int y, unsigned int color);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	void *m_surface;
	~W3DRadarResetSurface();
};

struct CursorTextureSlot : public BfmeResetTextureRef
{
	W3DRadarResetSurface Get_Surface_Level();
};

struct Rva00131DFC : public CursorTextureSlot
{
	char m_pad04[0x0E - 0x04];
	bool m_ready0E; // absolute +0x22: a 4-aligned 0xE tail cannot precede it
	void rva00131DFC(void *a, void *b, void *c, void *d, int e, int f);
};

class BfmeDynamicVBRefCount
{
public:
	virtual void DeleteThis();
	virtual ~BfmeDynamicVBRefCount();
	int references;
	void Release_Ref() { if (--references == 0) DeleteThis(); }
};

class BfmeDynamicVBBase : public BfmeDynamicVBRefCount
{
public:
	virtual ~BfmeDynamicVBBase();
	unsigned type;
	unsigned short vertexCount;
	int engineReferences;
	void *format;
	bool usesDeclaration;
};

class BfmeDynamicNativeVB : public BfmeDynamicVBBase
{
public:
	void *buffer;
	BfmeDynamicNativeVB(unsigned a, unsigned short b, unsigned c, unsigned d);
};

class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};
	virtual void DeleteThis();
	virtual ~DX8IndexBufferClass();
	int m_references;
	char m_pad08[0x18 - 8];
	void Release_Ref() { if (--m_references == 0) DeleteThis(); }
	DX8IndexBufferClass(unsigned index_count, UsageType usage);
};

class Rva000E473F
{
public:
	void rva000E473F();
	void rva000E479C();

private:
	char m_pad00[4];
	BfmeDynamicNativeVB *m_vb;
	DX8IndexBufferClass *m_ib;
	int m_0C;
	int m_10;
	Rva00131DFC m_slot;
};

// ?rva000E473F@Rva000E473F@@QAEXXZ @0x000E473F 93B
void Rva000E473F::rva000E473F()
{
	BFMEDX8DeviceLock guard;
	if (m_vb != 0)
	{
		m_vb->Release_Ref();
		m_vb = 0;
	}
	if (m_ib != 0)
	{
		m_ib->Release_Ref();
		m_ib = 0;
	}
	m_slot.clear();
}

// ?rva000E479C@Rva000E473F@@QAEXXZ @0x000E479C 234B
void Rva000E473F::rva000E479C()
{
	BFMEDX8DeviceLock guard;
	if (m_vb != 0 || m_ib != 0)
		rva000E473F();
	m_vb = new BfmeDynamicNativeVB(0x152, 0x3A9C, 1, 0);
	m_ib = new DX8IndexBufferClass(0x7534, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_0C = 0;
	m_10 = 0;
	m_slot.rva00131DFC((void *)1, (void *)1, (void *)0x15, (void *)1, 1, 0);
	if (m_slot.pointer != 0)
	{
		m_slot.Get_Surface_Level().DrawPixel(0, 0, 0x7F7FFF);
	}
	m_slot.m_ready0E = true;
}
