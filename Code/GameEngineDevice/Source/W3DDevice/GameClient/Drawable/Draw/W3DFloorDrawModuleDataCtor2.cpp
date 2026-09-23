// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??0W3DFloorDrawModuleData@@QAE@XZ, retail 0x000CF681, 66 bytes.
// EH ctor over the pinned W3DPropDraw base (0xCEF2B, 0x10 bytes): base call,
// explicit vtable 0x00BCD5D8, two 16-byte-element vectors at +0x10/+0x24 via
// the ICF-folded Vector_base at 0x00211E58 (allocator temp on ebp-1), three
// flag bytes at +0x1C/+0x1D/+0x1E, and float zero at +0x20 (xorps+movss).
// Table 0x00BCD6B0 proves the names (WeatherTexture/StaticModelLODMode/
// ForceToBack/StartHidden/FloorFadeRateOnObjectDeath/HideIfModelConditions).
// Element type is the 16-byte stand-in (BfmeE16) whose vector_base is the
// rowed 0x211E58 body; the true texture/condition elements are unproven.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class W3DPropDrawModuleData
{
public:
	W3DPropDrawModuleData();
	virtual ~W3DPropDrawModuleData();

private:
	unsigned char m_opaque[0x10 - 4];
};

class W3DFloorDrawModuleData : public W3DPropDrawModuleData
{
public:
	W3DFloorDrawModuleData();
	virtual ~W3DFloorDrawModuleData();

private:
	_STL::vector<BfmeE16> m_weatherTexture;	// +0x10 WeatherTexture
	bool m_staticModelLODMode;	// +0x1C StaticModelLODMode
	bool m_forceToBack;	// +0x1D ForceToBack
	bool m_startHidden;	// +0x1E StartHidden
	float m_floorFadeRateOnObjectDeath;	// +0x20 FloorFadeRateOnObjectDeath
	_STL::vector<BfmeE16> m_hideIfModelConditions;	// +0x24 HideIfModelConditions
};

W3DFloorDrawModuleData::W3DFloorDrawModuleData()
	: m_staticModelLODMode(false),
	  m_forceToBack(false),
	  m_startHidden(false),
	  m_floorFadeRateOnObjectDeath(0.0f)
{
}
