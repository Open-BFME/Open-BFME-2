// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??1W3DFloorDrawModuleData@@UAE@XZ, retail 0x000CF6C3, 80 bytes.
// EH dtor over the pinned W3DPropDraw base (rowed 0xCEF3C): explicit vtable
// 0x00BCD5D8, raw free of +0x24 HideIfModelConditions storage via _free,
// vector<CameraMarker> teardown at +0x10 WeatherTexture via rowed 0xCF60B,
// then base dtor. Three flag bytes +0x1C/+0x1D/+0x1E and float +0x20 are
// trivial. Table 0x00BCD6B0 proves the names. Element types follow the
// ctor TU stand-in (BfmeE16 for +0x24) with +0x10 using the CameraMarker
// vector shape whose rowed dtor shares the 16-byte stride; true texture
// and condition elements remain unproven.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class CameraMarker
{
public:
	~CameraMarker();
};

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
	_STL::vector<CameraMarker> m_weatherTexture;
	bool m_staticModelLODMode;
	bool m_forceToBack;
	bool m_startHidden;
	float m_floorFadeRateOnObjectDeath;
	_STL::vector<BfmeE16> m_hideIfModelConditions;
};

W3DFloorDrawModuleData::~W3DFloorDrawModuleData()
{
}
