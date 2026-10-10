// ?headB@Rva00066A9ASub@@QAEXXZ
// partial score=0.98 date=2026-10-10
// ?headB@Rva00066A9ASub@@QAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /EHsc /MD
//
// Dump range 1. The 0x66A9A host body calls this subobject's headB through the
// retail global at 0x00DE2000 when non-null. Target bytes for headB establish
// the member offsets +0xF8 and +0x100 plus the callees and DX8 lock scope. The
// owner type and helper identities remain address-derived structural inferences.

extern void *W3DGCData00DE2000;

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template <class T>
class RefCountPtr
{
public:
	T *Referent;
	RefCountPtr() : Referent(0) {}
	RefCountPtr(const RefCountPtr &other) : Referent(other.Referent) { if (Referent) ++*(unsigned short *)((char *)Referent + 4); }
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	RefCountPtr const &operator=(RefCountPtr const &other);
};

enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
class DX8Wrapper { public: static RefCountPtr<TextureClass> Create_Render_Target(int width, int height, WW3DFormat format); };

class WaterTracksRenderSystem
{
public:
	void ReAcquireResources();
};

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

struct Rva00066A9ADx8Guard
{
	Rva00066A9ADx8Guard() { BFME_DX8_Thread_Lock(); }
	~Rva00066A9ADx8Guard() { BFME_DX8_Thread_Assert(); }
};

class Rva00066A9ASub
{
public:
	void headB();
	__forceinline void setHeadBTexture(RefCountPtr<TextureClass> const &texture)
	{
		m_texture.operator=(texture);
	}
	void tailA();
	void tailB();

private:
	char m_pad[0xF8];
	RefCountPtr<TextureClass> m_texture; // +0xF8
	char m_padFC[4];
	WaterTracksRenderSystem *m_helper; // +0x100
};

class Rva00066A9AHost
{
public:
	void rva00066A9A();
	void headA();

	char m_pad[0x3850];
	Rva00066A9ASub *m_3850; // +0x3850
	Rva00066A9ASub *m_3854; // +0x3854
};

void Rva00066A9ASub::headB()
{
	Rva00066A9ADx8Guard guard;
	{
		m_texture = DX8Wrapper::Create_Render_Target(0x200, 0x200, WW3D_FORMAT_UNKNOWN);
	}

	if (m_helper)
		m_helper->ReAcquireResources();
}

