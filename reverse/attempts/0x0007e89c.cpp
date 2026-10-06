// ?headB@Rva00066A9ASub@@QAEXXZ
// partial score=0.98 date=2026-10-07
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
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	RefCountPtr const &operator=(RefCountPtr const &other);
};

RefCountPtr<TextureClass> __cdecl rva0011E120(int width, int height, int format);

class Rva000FE065
{
public:
	void rva000FE065();
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
	Rva000FE065 *m_helper; // +0x100
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
		setHeadBTexture(rva0011E120(0x200, 0x200, 0));
	}

	if (m_helper)
		m_helper->rva000FE065();
}

void Rva00066A9AHost::rva00066A9A()
{
	headA();
	Rva00066A9ASub *g = (Rva00066A9ASub *)W3DGCData00DE2000;
	if (g)
		g->headB();
	if (m_3850)
		m_3850->tailA();
	if (m_3854)
		m_3854->tailB();
}
