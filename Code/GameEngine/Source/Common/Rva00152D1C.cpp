// cl: /Ireference/shims/bfme2_ascii /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva152d1c@Rva00152D1CObj@@QAEXH@Z @0x00152D1C 170B evidence: caller 0x00117172 via [mesh+0x94]->[+0xB8] arg 4; LINK BONUS 131B Rva00117120Cluster; virtual slot0 or 0 then AsciiString from char then copy +0x18 then vector copy +0x0C then matched FXShaderSetup::InitializeShader at 0x0015288F.
// The caller passes two string pointers, the parameter vector and the LOD; the matched callee returns bool in AL, which this caller ignores. prev/next Common.
#include "ascii_string.h"

struct Rva0007BB16Record;
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	vector(const vector &other);
	~vector();
private:
	void *m_00;
	void *m_01;
	void *m_02;
};
}

class Rva00152D1CInner
{
public:
	virtual const char *v00();
};

class FXShaderSetup
{
public:
	bool InitializeShader(const char *shaderName, const char *techniqueName,
		const _STL::vector<Rva0007BB16Record> *parameters, int lod);
};

class Rva00152D1CObj
{
public:
	void rva152d1c(int n);
private:
	char m_pad[8];
	Rva00152D1CInner *m_08;
	_STL::vector<Rva0007BB16Record> m_vec;
	AsciiString m_str;
};

void Rva00152D1CObj::rva152d1c(int n)
{
	Rva00152D1CInner *inner = m_08;
	const char *v = inner ? inner->v00() : 0;
	AsciiString tmp1(v);
	AsciiString tmp2(m_str);
	_STL::vector<Rva0007BB16Record> tmpVec(m_vec);
	((FXShaderSetup *)this)->InitializeShader(tmp1.str(), tmp2.str(), &tmpVec, n);
}
