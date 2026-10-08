// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD GameClient/Water.cpp WaterSetting::WaterSetting.
// ??0WaterSetting@@QAE@XZ @0x00309CF8 166B. The static initializer at
// 0x007AE6C2 hands this constructor and the destructor right behind it
// (0x00309D9E, rowed as ??1Rva00309D9E@@UAE@XZ) to the eh vector constructor
// iterator for six 0x7C-byte elements at 0x00DFF1A0, which
// INI::parseWaterSettingDefinition (0x00200BEB) indexes as WaterSettings.
// The Zero Hour body, built /O1 /arch:SSE, places uniquely; the stores
// follow the source order 00, 01, 10, 11 over the declared 00, 10, 11, 01
// member layout. The vptr is 0x00C082E8.

#include "ascii_string.h"

typedef int Int;
typedef float Real;

struct RGBAColorInt
{
	Int red, green, blue, alpha;
};

class WaterSetting
{

public:

	WaterSetting( void );
	virtual ~WaterSetting( void );

	AsciiString m_skyTextureFile;
	AsciiString m_waterTextureFile;
	Int m_waterRepeatCount;
	Real m_skyTexelsPerUnit;	//texel density of sky plane (higher value repeats texture more).
	RGBAColorInt m_vertex00Diffuse;
	RGBAColorInt m_vertex10Diffuse;
	RGBAColorInt m_vertex11Diffuse;
	RGBAColorInt m_vertex01Diffuse;
	RGBAColorInt m_waterDiffuseColor;
	RGBAColorInt m_transparentWaterDiffuse;
	Real m_uScrollPerMs;
	Real m_vScrollPerMs;

};

// ------------------------------------------------------------------------------------------------
/** Constructor */
// ------------------------------------------------------------------------------------------------
WaterSetting::WaterSetting( void )
{

	m_skyTextureFile.clear();
	m_waterTextureFile.clear();
	m_waterRepeatCount = 0;
	m_skyTexelsPerUnit = 0.0f;

	m_vertex00Diffuse.red = 0;
	m_vertex00Diffuse.green = 0;
	m_vertex00Diffuse.blue = 0;
	m_vertex00Diffuse.alpha = 0;

	m_vertex01Diffuse.red = 0;
	m_vertex01Diffuse.green = 0;
	m_vertex01Diffuse.blue = 0;
	m_vertex01Diffuse.alpha = 0;

	m_vertex10Diffuse.red = 0;
	m_vertex10Diffuse.green = 0;
	m_vertex10Diffuse.blue = 0;
	m_vertex10Diffuse.alpha = 0;

	m_vertex11Diffuse.red = 0;
	m_vertex11Diffuse.green = 0;
	m_vertex11Diffuse.blue = 0;
	m_vertex11Diffuse.alpha = 0;

	m_waterDiffuseColor.red = 0;
	m_waterDiffuseColor.green = 0;
	m_waterDiffuseColor.blue = 0;
	m_waterDiffuseColor.alpha = 0;

	m_transparentWaterDiffuse.red = 0;
	m_transparentWaterDiffuse.green = 0;
	m_transparentWaterDiffuse.blue = 0;
	m_transparentWaterDiffuse.alpha = 0;

	m_uScrollPerMs = 0.0f;
	m_vScrollPerMs = 0.0f;

}  // end WaterSetting

// ------------------------------------------------------------------------------------------------
/** Destructor. ??1WaterSetting@@UAE@XZ @0x00309D9E 60B, right behind the
 * constructor: it restores the same vptr 0x00C082E8 and releases the two
 * strings, and the static initializer 0x007AE6C2 passes it with the
 * constructor to the eh vector constructor iterator. */
// ------------------------------------------------------------------------------------------------
WaterSetting::~WaterSetting( void )
{

}
