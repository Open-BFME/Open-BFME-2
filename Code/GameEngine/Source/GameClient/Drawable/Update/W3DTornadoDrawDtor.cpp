// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1W3DTornadoDraw@@UAE@XZ, retail 0x000D18AB, 77 bytes.
// Target evidence: the audited scalar deleting dtor 0x000D19DD calls this
// body; slot 4 -> 0x000D1866 uses class-name string "W3DTornadoDraw".
// Body: installs vtable 0x00BCE218, runs the rowed decal-list drain
// rva000D1743 (0x000D1743), destroys the +0x0C list (0x004EC395), then the
// inlined intermediate dtor stores its vptr 0x00BC9690 and calls the
// fold-point base dtor 0x0049B47C. Layout from the matched ctor TU
// AnimatedParticleSysBoneClientUpdateCtor.cpp; the intermediate (ctor pin
// 0x000B19A1) is still opaque.
#include <list>

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();
};

class Rva000B19A1 : public Rva0049B47C
{
public:
	inline virtual ~Rva000B19A1() {}

private:
	unsigned char m_pad04[8];
};

class W3DTornadoDraw : public Rva000B19A1
{
public:
	virtual ~W3DTornadoDraw();

private:
	void rva000D1743();

	_STL::list<int> m_boneIndices;	// +0x0C
};

W3DTornadoDraw::~W3DTornadoDraw()
{
	rva000D1743();
}
