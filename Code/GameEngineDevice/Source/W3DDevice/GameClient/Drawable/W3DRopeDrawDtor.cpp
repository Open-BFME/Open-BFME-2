// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1W3DRopeDraw@@UAE@XZ @0x000CA8BC 90B: W3DRopeDraw public virtual dtor.
// Donor BFME1 W3DRopeDraw.cpp dtor calls tossSegments. Vptr installs plus vector
// storage free via game free plus base DrawableModule dtor at folded 0x0049B47C
// via existing ??1DrawableModule pin. /EHs for the byte state store before free.
// Scene layout per W3DLaser precedent. Unblocks deleting dtor at 0x000CA9D5.
#include <vector>

struct BfmePod16 { int a[4]; };

class DrawableModule
{
protected:
	virtual ~DrawableModule();
	void *m_moduleData;
	void *m_drawable;
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class RopeDrawInterface
{
public:
	virtual void ropeSlot();
};

class W3DRopeDraw : public DrawModule, public RopeDrawInterface
{
public:
	virtual ~W3DRopeDraw();
private:
	_STL::vector<BfmePod16> m_segments;
	void tossSegments();
};

W3DRopeDraw::~W3DRopeDraw()
{
	tossSegments();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?ropeSlot@RopeDrawInterface@@UAEXXZ=?initRopeParms@W3DRopeDraw@@UAEXMMABURGBColor@@MMM@Z")
