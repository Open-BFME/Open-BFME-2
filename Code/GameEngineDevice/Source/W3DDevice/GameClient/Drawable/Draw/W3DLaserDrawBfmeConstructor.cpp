// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /I.
// stlport
// BFME1 donor f98983a7d: W3DLaserDrawBfmeConstructor.cpp supplies laser setup,
// texture acquisition and beam interpolation. Target factory 0x6492A calls
// 0xC9D38 and names W3DLaserDraw; its 849-byte RET8 extent ends at 0xCA089.
// Target agrees with the donor field layout and OrnamentData envelope copy.
// Native SegmentedLineClass allocation is 0x12C and Set_Visible is slot105.
// AssetReference is the existing vector provider spelling; original template
// type identity remains provisional. Native texture loads and WORD refcount
// ownership agree with the established BFME2ParticleTextureHandle view.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

#define TRUE 1

typedef char Char;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int Color;

#include "ascii_string.h"
#include "Code/GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"
class SurfaceClass {
public:
 struct SurfaceDescription { unsigned Format,Width,Height; };
 void Get_Description(SurfaceDescription &);
};
class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	void Get_Description(SurfaceClass::SurfaceDescription &desc)
	{
		((SurfaceClass *)this)->Get_Description(desc);
	}

private:
	void *m_surface;
};

class W3DRadarResetTexture { public: W3DRadarResetSurface getSurfaceLevel(); };
extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, Int, Int);
class AssetReference {
public:
 AssetReference(); AssetReference(const AssetReference &); ~AssetReference();
 AssetReference &operator=(const AssetReference &);
 TextureClass *m_ref;
};
class Thing;
class Matrix3D;
class ModuleData
{
	char m_pad00[8];
};

struct OrnamentData {
 OrnamentData *init() throw();
 OrnamentData() { init(); }
 Real m_f00,m_f04,m_f08; Int m_f0c,m_f10,m_f14,m_f18,m_i1c,m_i20,m_i24;
};
class W3DLaserDrawModuleData : public ModuleData
{
public:
	Color m_innerColor;
	Color m_outerColor;
	Real m_innerBeamWidth;
	Real m_outerBeamWidth;
	Real m_scrollRate;
	Bool m_tile;
	char m_pad1d[3];
	UnsignedInt m_numBeams;
	UnsignedInt m_maxIntensityFrames;
	UnsignedInt m_fadeFrames;
	std::vector<AsciiString> m_textureNames;
	UnsignedInt m_segments;
	Real m_arcHeight;
	Real m_segmentOverlapRatio;
	Real m_tilingScalar;
	Int m_field48;
	Int valueAtUnmodelled0048() const { return m_field48; }
	OrnamentData m_params;
};

class DrawableModule
{
public:
	virtual ~DrawableModule();

protected:
	W3DLaserDrawModuleData *m_moduleData;
	Int m_bfmeField;
};

class DrawModule : public DrawableModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
	virtual void doDrawModule(const Matrix3D *transform) = 0;
};

class LaserDrawInterface
{
public:
	virtual void bfmeLaserDrawInterfaceSlot(void);
};

class ShaderClass
{
public:
	static ShaderClass _PresetAdditiveShader;
	Int m_bits;

	ShaderClass(const ShaderClass &other) { m_bits = other.m_bits; }
};


// Retail thunk 0x0094F960 adjusts ECX by 0xE0 then jumps to Set_Texture.
// This view passes the TextureClass pointer by reference.
class Rva0094F960
{
public:
	void apply(TextureClass *const &texture);
};

class SegLineRendererClass
{
public:
	enum TextureMapMode
	{
		TILED_TEXTURE_MAP = 2
	};

};

class Vector3
{
public:
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) { }

	Real X;
	Real Y;
	Real Z;
};

class Vector2
{
public:
	Vector2(Real x, Real y) : X(x), Y(y) { }

	Real X;
	Real Y;
};

class SegmentedLineClass
{
public:
	SegmentedLineClass(void);

	char m_pad04[0x128];

	virtual void bfmeVpad000();
	virtual void bfmeVpad001();
	virtual void bfmeVpad002();
	virtual void bfmeVpad003();
	virtual void bfmeVpad004();
	virtual void bfmeVpad005();
	virtual void bfmeVpad006();
	virtual void bfmeVpad007();
	virtual void bfmeVpad008();
	virtual void bfmeVpad009();
	virtual void bfmeVpad010();
	virtual void bfmeVpad011();
	virtual void bfmeVpad012();
	virtual void bfmeVpad013();
	virtual void bfmeVpad014();
	virtual void bfmeVpad015();
	virtual void bfmeVpad016();
	virtual void bfmeVpad017();
	virtual void bfmeVpad018();
	virtual void bfmeVpad019();
	virtual void bfmeVpad020();
	virtual void bfmeVpad021();
	virtual void bfmeVpad022();
	virtual void bfmeVpad023();
	virtual void bfmeVpad024();
	virtual void bfmeVpad025();
	virtual void bfmeVpad026();
	virtual void bfmeVpad027();
	virtual void bfmeVpad028();
	virtual void bfmeVpad029();
	virtual void bfmeVpad030();
	virtual void bfmeVpad031();
	virtual void bfmeVpad032();
	virtual void bfmeVpad033();
	virtual void bfmeVpad034();
	virtual void bfmeVpad035();
	virtual void bfmeVpad036();
	virtual void bfmeVpad037();
	virtual void bfmeVpad038();
	virtual void bfmeVpad039();
	virtual void bfmeVpad040();
	virtual void bfmeVpad041();
	virtual void bfmeVpad042();
	virtual void bfmeVpad043();
	virtual void bfmeVpad044();
	virtual void bfmeVpad045();
	virtual void bfmeVpad046();
	virtual void bfmeVpad047();
	virtual void bfmeVpad048();
	virtual void bfmeVpad049();
	virtual void bfmeVpad050();
	virtual void bfmeVpad051();
	virtual void bfmeVpad052();
	virtual void bfmeVpad053();
	virtual void bfmeVpad054();
	virtual void bfmeVpad055();
	virtual void bfmeVpad056();
	virtual void bfmeVpad057();
	virtual void bfmeVpad058();
	virtual void bfmeVpad059();
	virtual void bfmeVpad060();
	virtual void bfmeVpad061();
	virtual void bfmeVpad062();
	virtual void bfmeVpad063();
	virtual void bfmeVpad064();
	virtual void bfmeVpad065();
	virtual void bfmeVpad066();
	virtual void bfmeVpad067();
	virtual void bfmeVpad068();
	virtual void bfmeVpad069();
	virtual void bfmeVpad070();
	virtual void bfmeVpad071();
	virtual void bfmeVpad072();
	virtual void bfmeVpad073();
	virtual void bfmeVpad074();
	virtual void bfmeVpad075();
	virtual void bfmeVpad076();
	virtual void bfmeVpad077();
	virtual void bfmeVpad078();
	virtual void bfmeVpad079();
	virtual void bfmeVpad080();
	virtual void bfmeVpad081();
	virtual void bfmeVpad082();
	virtual void bfmeVpad083();
	virtual void bfmeVpad084();
	virtual void bfmeVpad085();
	virtual void bfmeVpad086();
	virtual void bfmeVpad087();
	virtual void bfmeVpad088();
	virtual void bfmeVpad089();
	virtual void bfmeVpad090();
	virtual void bfmeVpad091();
	virtual void bfmeVpad092();
	virtual void bfmeVpad093();
	virtual void bfmeVpad094();
	virtual void bfmeVpad095();
	virtual void bfmeVpad096();
	virtual void bfmeVpad097();
	virtual void bfmeVpad098();
	virtual void bfmeVpad099();
	virtual void bfmeVpad100();
	virtual void bfmeVpad101();
	virtual void bfmeVpad102();
	virtual void bfmeVpad103();
	virtual void bfmeVpad104();
	virtual void Set_Visible(Int visible);

	void Set_Texture(const RefCountPtr<TextureClass> &texture);
	void Set_Shader(ShaderClass shader);
	void Set_Width(Real width);
	void Set_Color(const Vector3 &color);
	void Set_UV_Offset_Rate(const Vector2 &rate);
	void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode);
};

class RTS3DScene
{
public:
	virtual void bfmeSceneSlot0(void);
	virtual void bfmeSceneSlot1(void);
	virtual void Add_Render_Object(SegmentedLineClass *line);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};


class W3DLaserDraw : public DrawModule, public LaserDrawInterface
{
public:
	W3DLaserDraw(Thing *thing, const ModuleData *moduleData);
	virtual void doDrawModule(const Matrix3D *transform);

protected:
	virtual ~W3DLaserDraw(void);
	SegmentedLineClass **m_line3D;
	std::vector<AssetReference> m_textureVector;
	Real m_textureAspectRatio;
	Bool m_selfDirty;
	char m_pad25[3];
	Int m_field28;
	Real m_field2c;
	Int m_field30;
	OrnamentData m_params;
};

extern void GameGetColorComponentsReal(
	Color color, Real *red, Real *green, Real *blue, Real *alpha);

W3DLaserDraw::W3DLaserDraw( Thing *thing, const ModuleData* moduleData ) :
	DrawModule( thing, moduleData ),
	m_line3D(NULL),
	m_textureVector(),
	m_textureAspectRatio(1.0f),
	m_selfDirty(TRUE),
	m_field28(0),
	m_field2c(1.0f),
	m_field30(m_moduleData->valueAtUnmodelled0048())
{
	const W3DLaserDrawModuleData *data = m_moduleData;
	const std::vector<AsciiString> *textureNames = &data->m_textureNames;

	m_params = data->m_params;

	Int numTextures = textureNames->size();
	for (Int i = 0; i < numTextures; i++)
	{
		const Char *name = (textureNames->begin() + i)->str();
		BFME2ParticleTextureHandle handle = BFME2LoadParticleTexture(name, 0, 0);
		if (handle.Ptr)
		{
			SurfaceClass::SurfaceDescription surfaceDesc;
			((W3DRadarResetTexture *)&handle)->getSurfaceLevel().Get_Description(surfaceDesc);
			m_textureAspectRatio = (Real)surfaceDesc.Width/(Real)surfaceDesc.Height;
		}
		m_textureVector.push_back(*(AssetReference *)&handle);
	}

	Real innerRed, innerGreen, innerBlue, innerAlpha, outerRed, outerGreen, outerBlue, outerAlpha;
	GameGetColorComponentsReal( data->m_innerColor, &innerRed, &innerGreen, &innerBlue, &innerAlpha );
	GameGetColorComponentsReal( data->m_outerColor, &outerRed, &outerGreen, &outerBlue, &outerAlpha );

	m_line3D = new SegmentedLineClass *[ *(const volatile UnsignedInt *)&data->m_numBeams * data->m_segments ];

	for( UnsignedInt segment = 0; segment < data->m_segments; segment++ )
	{
		for( Int i = data->m_numBeams - 1; i >= 0; i-- )
		{
			Int index = segment * data->m_numBeams + i;

			Real red, green, blue, alpha, width;

			if( data->m_numBeams == 1 )
			{
				width = data->m_innerBeamWidth;
				alpha = innerAlpha;
				red = innerRed * innerAlpha;
				green = innerGreen * innerAlpha;
				blue = innerBlue * innerAlpha;
			}
			else
			{
				Real scale = i / ( data->m_numBeams - 1.0f);

				width		= data->m_innerBeamWidth	+ scale * (data->m_outerBeamWidth - data->m_innerBeamWidth);
				alpha		= innerAlpha							+ scale * (outerAlpha - innerAlpha);
				red			= innerRed								+ scale * (outerRed - innerRed) * innerAlpha;
				green		= innerGreen							+ scale * (outerGreen - innerGreen) * innerAlpha;
				blue		= innerBlue								+ scale * (outerBlue - innerBlue) * innerAlpha;
			}

			m_line3D[ index ] = new SegmentedLineClass;

			SegmentedLineClass *line = m_line3D[ index ];
			if( line )
			{
				line->Set_Texture(*(const RefCountPtr<TextureClass> *)m_textureVector.begin());
				line->Set_Shader( ShaderClass::_PresetAdditiveShader );
				line->Set_Width( width );
				line->Set_Color( Vector3( red, green, blue ) );
				line->Set_UV_Offset_Rate( Vector2(0.0f, data->m_scrollRate) );
				if( m_textureVector.begin()->m_ref )
				{
					line->Set_Texture_Mapping_Mode(SegLineRendererClass::TILED_TEXTURE_MAP);
				}

				W3DDisplay::m_3DScene->Add_Render_Object( line );

				line->Set_Visible( 1 );
			}

		}  // end for i

	} //end segment loop

}
