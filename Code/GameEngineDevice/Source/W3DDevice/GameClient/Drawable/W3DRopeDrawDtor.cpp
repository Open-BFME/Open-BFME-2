// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1W3DRopeDraw@@UAE@XZ @0x000CA8BC 90B: W3DRopeDraw public virtual dtor.
// Donor BFME1 W3DRopeDraw.cpp dtor calls tossSegments. Vptr installs plus vector
// storage free via game free plus base DrawableModule dtor at folded 0x0049B47C
// via existing ??1DrawableModule pin. /EHs for the byte state store before free.
// Scene layout per W3DLaser precedent. Unblocks deleting dtor at 0x000CA9D5.
#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

struct BfmePod16 { int a[4]; };

#include "../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"
inline DrawModule::~DrawModule() {} // retail inlines this into the derived destructors

struct RGBColor;

class RopeDrawInterface
{
public:
	virtual void initRopeParms(float length, float width, const RGBColor &color, float wobbleLen, float wobbleAmp, float wobbleRate) = 0;
	virtual void setRopeCurLen(float length) = 0;
	virtual void setRopeSpeed(float curSpeed, float maxSpeed, float accel) = 0;
};

class W3DRopeDrawPrimary : public DrawModule
{
};

class W3DRopeDraw : public W3DRopeDrawPrimary, public RopeDrawInterface
{
public:
	virtual ~W3DRopeDraw();
	virtual void initRopeParms(float length, float width, const RGBColor &color,
		float wobbleLen, float wobbleAmp, float wobbleRate);
	virtual void setRopeCurLen(float length);
	virtual void setRopeSpeed(float curSpeed, float maxSpeed, float accel);
private:
	_STL::vector<BfmePod16> m_segments;
	void tossSegments();
};

W3DRopeDraw::~W3DRopeDraw()
{
	tossSegments();
}
