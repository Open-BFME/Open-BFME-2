// ?rva0006ABE7@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@_N@Z
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// stlport
// ?rva0006ABE7@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@_N@Z @0x0006ABE7 214B
// BaseHeightMapRenderObjClass texture reload with flag via rowed StringBase
// set 0x366F0 plus BfmeResetTextureRef clear 0x4D75B plus BFME2Load 0x132D89
// plus RefCountPtr assign 0x424D0 plus ShroudTexture getFilter 0x132856.
// Evidence: same-this caller 0x0006B804 plus slot caller 0x000926AC plus
// sibling 0x0006ACBD plus prev 0x0006AB98.
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

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

extern const char g_Rva0107301CEmptyString[];
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

__forceinline const char *GetStr0006ABE7(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

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
	int m_pad08;
	int m_0C;
	int m_10;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
	RefCountPtr<TextureClass> m_tex;
};

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

// ?rva0006ABE7@BaseHeightMapRenderObjClass@@QAEXVAsciiString@@_N@Z present-unmatched
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
	m_3828.getFilter()->m_0C = 0;
	m_3828.getFilter()->m_10 = 0;
}
