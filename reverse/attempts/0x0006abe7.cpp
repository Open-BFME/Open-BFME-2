// ?rva0006ABE7@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@_N@Z
// partial score=0.97 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// stlport
// ?rva0006ABE7@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@_N@Z @0x0006ABE7
// 214B. Sibling of rva0006ACBD in the same unit: reloads the terrain's second
// texture from a name (default at +0x3830 when the name is empty) and records
// a flag byte at +0x3834, after releasing the previous texture through the
// rowed BfmeResetTextureRef::clear (0x0004D75B). The texture holder is at
// +0x3828, its current name at +0x382C. The loader (0x00132D89), RefCountPtr
// assign (0x000424D0) and filter getter (0x00132856) are the ones rva0006ACBD
// uses; the filter fields are written directly here (min/mag = 2, the two
// later words = 0). Callee of 0x0006B804.
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

class BfmeResetTextureRef
{
public:
	void clear();
};

class ShroudFilter
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
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

BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

__forceinline const char *GetStr0006ABE7(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class BaseHeightMapRenderObjClass
{
private:
	char m_pad[0x3828];
	ShroudTexture m_3828;
	AsciiString m_382C;
	AsciiString m_3830;
	bool m_3834;
public:
	void rva0006ABE7(AsciiString name, bool flag);
};

void BaseHeightMapRenderObjClass::rva0006ABE7(AsciiString name, bool flag)
{
	if (name.isEmpty())
		((StringBase<char> &)name).set((StringBase<char> &)m_3830);
	((BfmeResetTextureRef *)&m_3828)->clear();
	m_3834 = flag;
	((StringBase<char> &)m_382C).set((StringBase<char> &)name);
	const char *s = GetStr0006ABE7(m_382C);
	m_3828.m_tex = BFME2LoadParticleTexture(s, 0, 0);
	m_3828.getFilter()->m_00 = 2;
	m_3828.getFilter()->m_04 = 2;
	m_3828.getFilter()->m_0c = 0;
	m_3828.getFilter()->m_10 = 0;
}
