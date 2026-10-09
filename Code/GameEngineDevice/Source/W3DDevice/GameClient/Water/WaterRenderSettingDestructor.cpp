// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// BFME1 donor 0bef414b52a39a3ab1ec98dca60d8a214de4260e; native BFME2 7EF35..7F0F9.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// BFME2 owns six 0x7C-byte WaterSetting records at VA 0x00DFF1A0.
// The configuration view below preserves every field offset read by retail.
class WaterSetting;
extern WaterSetting WaterSettings[];

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class BFME2ParticleTextureHandle {
public:
 TextureBaseClass *Ptr;
 ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *,int,int);
class W3DRadarResetSurface;
class CursorTextureSlot {
public:
 TextureBaseClass *Ptr;
 ~CursorTextureSlot() { if (Ptr) reinterpret_cast<TextureClass *>(Ptr)->Release_Ref(); }
 void operator=(const BFME2ParticleTextureHandle &);
 W3DRadarResetSurface Get_Surface_Level();
};

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		UnsignedInt Format;
		UnsignedInt Width;
		UnsignedInt Height;
	};

	void Get_Description(SurfaceDescription &surfaceDesc);
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual unsigned long __stdcall addRef(void);
	virtual unsigned long __stdcall release(void);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	W3DRadarResetSurface(void) : m_surface(0) {}
	W3DRadarResetSurface(SurfaceResource *surface);
	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) :
		m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}
	~W3DRadarResetSurface(void);

private:
	SurfaceResource *m_surface;
};

class WaterSettingColorView
{
public:
	UnsignedInt red;
	UnsignedInt green;
	UnsignedInt blue;
	UnsignedInt alpha;
};

class WaterSettingLoadView
{
public:
	virtual ~WaterSettingLoadView(void);

	AsciiString m_skyTextureFile;
	AsciiString m_waterTextureFile;
	Int m_waterRepeatCount;
	Real m_skyTexelsPerUnit;
	WaterSettingColorView m_vertex00Diffuse;
	WaterSettingColorView m_vertex10Diffuse;
	WaterSettingColorView m_vertex11Diffuse;
	WaterSettingColorView m_vertex01Diffuse;
	WaterSettingColorView m_waterDiffuseColor;
	WaterSettingColorView m_transparentWaterDiffuse;
	Real m_uScrollPerMs;
	Real m_vScrollPerMs;
};

enum TimeOfDay;

class WaterRenderObjClass
{
public:
	struct Setting
	{
		Setting();
		~Setting();
		CursorTextureSlot skyTexture;
		CursorTextureSlot waterTexture;
		Int waterRepeatCount;
		Real skyTexelsPerUnit;
		UnsignedInt vertex00Diffuse;
		UnsignedInt vertex10Diffuse;
		UnsignedInt vertex11Diffuse;
		UnsignedInt vertex01Diffuse;
		UnsignedInt waterDiffuse;
		UnsignedInt transparentWaterDiffuse;
		Real uScrollPerMs;
		Real vScrollPerMs;
	};

protected:
	void loadSetting(Setting *setting, TimeOfDay timeOfDay);
};

// WB 0x00744120 names loadSetting (W3DWater.cpp:2990); native uses the
// named WaterSettings global, counted texture-loader/assignment providers,
// surface description width, four RGB colors, two ARGB colors, and scrolls.
// Native boundaries: 0x0007EF35..0x0007F0F9, including three EH cleanups.
// ?loadSetting@WaterRenderObjClass@@IAEXPAUSetting@1@W4TimeOfDay@@@Z
void WaterRenderObjClass::loadSetting(
	Setting *setting, TimeOfDay timeOfDay)
{
 setting->skyTexture = BFME2LoadParticleTexture(((WaterSettingLoadView *)WaterSettings)[(unsigned)timeOfDay].m_skyTextureFile.str(),0,0);
 setting->waterTexture = BFME2LoadParticleTexture(((WaterSettingLoadView *)WaterSettings)[(unsigned)timeOfDay].m_waterTextureFile.str(),0,0);

	setting->skyTexelsPerUnit = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_skyTexelsPerUnit;
	SurfaceClass::SurfaceDescription surfaceDesc;
	setting->waterTexture.Get_Surface_Level().Get_Description(surfaceDesc);
	setting->skyTexelsPerUnit /= (Real)surfaceDesc.Width;

	setting->waterRepeatCount = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterRepeatCount;
	setting->uScrollPerMs = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_uScrollPerMs;
	setting->vScrollPerMs = ((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vScrollPerMs;

	setting->vertex00Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex00Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex00Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex00Diffuse.blue;
	setting->vertex01Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex01Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex01Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex01Diffuse.blue;
	setting->vertex10Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex10Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex10Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex10Diffuse.blue;
	setting->vertex11Diffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex11Diffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex11Diffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_vertex11Diffuse.blue;
	setting->waterDiffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.alpha << 24) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_waterDiffuseColor.blue;
	setting->transparentWaterDiffuse =
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.alpha << 24) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.red << 16) |
		(((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.green << 8) |
		((WaterSettingLoadView *)WaterSettings)[(unsigned int)timeOfDay].m_transparentWaterDiffuse.blue;
}

// Existing 61-byte setting cleanup at BFME2 0x0007E7E2, originally ported
// from BFME1 WaterRenderSettingDestructor.cpp revision
// 6583b3c1ff21db4a561285717028fdafc780b7db; both textures own references.
WaterRenderObjClass::Setting::~Setting() {}

template <class T>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
};

class Vector3;

class Rva0007E7DD
{
public:
	void rva0007E7DD();
};

void Rva0007E7DD::rva0007E7DD()
{
	((SimpleDynVecClass<Vector3> *)this)->SimpleDynVecClass<Vector3>::~SimpleDynVecClass();
}


