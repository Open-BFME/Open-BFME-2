// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// stlport
// ?rva0006ACBD@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@@Z @0x0006ACBD 173B
// BaseHeightMapRenderObjClass texture reload via rowed StringBase set at
// 0x366F0 plus BFME2LoadParticleTexture 0x132D89 plus RefCountPtr assign
// 0x424D0 plus ShroudTexture getFilter 0x132856. Evidence: same-this caller
// 0x0006B804 plus slot caller 0x000926AC plus prev 0x0006AB98 plus next
// BaseHeightMapGetMaximumVisibleBox.
#include "ascii_string.h"

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

public:
	T *m_ptr;
};

namespace _STL
{
	class ios_base
	{
	protected:
		void _M_clear_nothrow(int state);
	};
}

class ShroudFilter : public _STL::ios_base
{
	friend class BaseHeightMapRenderObjClass;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
	RefCountPtr<TextureClass> m_tex;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

extern const char g_Rva0107301CEmptyString[];
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

__forceinline const char *GetStr0006ACBD(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

class BaseHeightMapRenderObjClass
{
private:
	char m_pad[0x381C];
	ShroudTexture m_381C;
	AsciiString m_3820;
	AsciiString m_3824;
public:
	void rva0006ACBD(AsciiString name);
};

void BaseHeightMapRenderObjClass::rva0006ACBD(AsciiString name)
{
	if (name.isEmpty())
		((StringBase<char> &)(StringBase<char> &)name).set((StringBase<char> &)m_3824);
	((StringBase<char> &)m_3820).set((StringBase<char> &)name);
	const char *s = GetStr0006ACBD(m_3820);
	m_381C.m_tex = BFME2LoadParticleTexture(s, 0, 0);
	m_381C.getFilter()->_M_clear_nothrow(1);
}
