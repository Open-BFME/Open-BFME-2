// cl: /DNDEBUG /MD /EHsc
//
// ??1W3DTankDraw@@UAE@XZ, retail 0x000CE960, 142 bytes.
// W3DTankDraw dtor: reinstalls vtables 0xBCCBE8/+0xC 0xBCC588/+0x10 0xBCA08C,
// releases 4 treads at +0x304 (each 0x14, REF_PTR_RELEASE via inline
// Release_Ref dec at +4 then slot-0 Delete_This), conditionally destroys the
// two 12-byte intrusive handles at +0x2F4/+0x2E8 through the rowed
// ??1BfmeParticleSystemHandle@@QAE@XZ at 0x4CBC0 when m_system!=0, then calls
// the pinned MI base dtor at 0xC79C9. Layout: opaque MI base (12B) plus shared
// MiBase1 plus per-class B2 gives +0/+0xC/+0x10; pad to 0x2E8 covers the true
// W3DScriptedModelDraw members (ctor at 0xC0DD8 proves 0x2E8); handles and
// treads match ctor 0xCEA6C (handles zeroed at 0x2E8/0x2F4, TreadObjectInfo
// ctor 0xCDFB1 for 4x0x14 at 0x304, prevRenderObj at 0x300).
// Retail's unwind map (base 0xC79C9 in state 0, +0x2E8 and +0x2F4 in states
// 1 and 2 through the out-of-line conditional destroy 0x002115C5) makes the
// two handles members with that destructor, not explicit calls in the body.
// Retail keeps no state stores between them: with the handle dtor's body
// visible (inline here, not expanded at /O1) the compiler treats the call
// as non-throwing and drops those stores. Donor BFME1
// W3DTankDrawDestructor.cpp/W3DTankDraw.cpp treads loop; BFME2 deltas:
// handles are 12-byte intrusive (not ParticleSystem*) with caller-side guard
// (DefaultModuleHeadBaseDtor precedent: trivial store plus explicit
// conditional destroy). Evidence: deleting wrapper 0xCEB2C slot 0 of
// 0xBCCBE8 calls here; slot 4 pool key 0xCE9EE uses "W3DTankDraw" string.

class RefCountClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}
	int NumRefs;
};

class RenderObjClass : public RefCountClass
{
};

struct TreadObjectInfo
{
	RenderObjClass *m_robj;
	unsigned char m_rest[0x10];
};

class ParticleSystem;
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};
class ParticleSystem
{
public:
	unsigned char m_pad[0x9C];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
};
inline BfmeParticleSystemHandle::~BfmeParticleSystemHandle()
{
	if (m_previous)
		m_previous->m_next = m_next;
	else
		m_system->m_firstHandle = m_next;
	if (m_next)
		m_next->m_previous = m_previous;
	else
		m_system->m_lastHandle = m_previous;
	m_previous = 0;
	m_next = 0;
}

struct W3DTankDrawDebrisHandle
{
	~W3DTankDrawDebrisHandle()
	{
		if (m_ptr0 != 0)
			((BfmeParticleSystemHandle *)this)->~BfmeParticleSystemHandle();
	}
	void *m_ptr0;
	void *m_ptr1;
	void *m_ptr2;
};

class Rva000C79C9
{
public:
	virtual ~Rva000C79C9();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class W3DTankDraw_B2
{
public:
	virtual void f2();
};

class W3DTankDraw : public Rva000C79C9, public MiBase1, public W3DTankDraw_B2
{
public:
	virtual ~W3DTankDraw();

private:
	unsigned char m_pad14[0x2E8 - 0x14];
	W3DTankDrawDebrisHandle m_treadDebrisLeft;
	W3DTankDrawDebrisHandle m_treadDebrisRight;
	void *m_prevRenderObj;
	TreadObjectInfo m_treads[4];
};

W3DTankDraw::~W3DTankDraw()
{
	for (int i = 0; i < 4; ++i)
	{
		RenderObjClass *robj = m_treads[i].m_robj;
		if (robj)
		{
			robj->Release_Ref();
			m_treads[i].m_robj = 0;
		}
	}
}
