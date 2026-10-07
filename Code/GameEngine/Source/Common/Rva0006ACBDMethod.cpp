// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
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
	friend class Rva0006D470;
	friend class Rva0006D3B6;
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

__forceinline const char *GetStr0006ACBD(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
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

// Target 0x0006D470..0x0006D52A RET4, 186B; body is a texture-name
// change guard around the same verified loaders as rva0006ACBD.
// Native accesses establish texture +3844, current name +3848, default +384C.
// Those offsets do not prove it is the existing terrain owner: keep this
// receiver address-derived. The texture/refcount/filter views carry existing
// callee identities, and their original names remain donor inferences.
class Rva0006D470 {
    char m_pad[0x3844];
    ShroudTexture m_3844;
    AsciiString m_3848;
    AsciiString m_384C;
public:
    void rva0006D470(AsciiString name);
};
void Rva0006D470::rva0006D470(AsciiString name)
{
    if(name.isEmpty())
        ((StringBase<char>&)name).set((StringBase<char>&)m_384C);
    if(name.compare(m_3848)!=0) {
        ((StringBase<char>&)m_3848).set((StringBase<char>&)name);
        m_3844.m_tex=BFME2LoadParticleTexture(GetStr0006ACBD(m_3848),0,0);
        m_3844.getFilter()->_M_clear_nothrow(1);
    }
}

// Target 0x0006D3B6..0x0006D470 RET4, 186B; body is a texture-name
// change guard around the same verified loaders as rva0006ACBD.
// Native accesses establish texture +3838, current name +383C, default +3840.
// Those offsets do not prove it is the existing terrain owner: keep this
// receiver address-derived. The texture/refcount/filter views carry existing
// callee identities, and their original names remain donor inferences.
class Rva0006D3B6 {
    char m_pad[0x3838];
    ShroudTexture m_3838;
    AsciiString m_383C;
    AsciiString m_3840;
public:
    void rva0006D3B6(AsciiString name);
};
void Rva0006D3B6::rva0006D3B6(AsciiString name)
{
    if(name.isEmpty())
        ((StringBase<char>&)name).set((StringBase<char>&)m_3840);
    if(name.compare(m_383C)!=0) {
        ((StringBase<char>&)m_383C).set((StringBase<char>&)name);
        m_3838.m_tex=BFME2LoadParticleTexture(GetStr0006ACBD(m_383C),0,0);
        m_3838.getFilter()->_M_clear_nothrow(1);
    }
}
