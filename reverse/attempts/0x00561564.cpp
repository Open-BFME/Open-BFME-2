// ?rva00561564@Rva00561564@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// partial score=0.717174 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class RenderInfoClass;

class Vector3
{
public:
	Real X, Y, Z;
};

class Vector4
{
public:
	Real X, Y, Z, W;
};

struct RGBColor
{
	Real red, green, blue;
};

template <class T> class ShareBufferClass
{
public:
	T *Get_Array(void) { return Array; }
private:
	char m_pad00[0xc];
	T *Array; // +0x0C
};
extern ShareBufferClass<Vector3> *g_00E065C8;
extern ShareBufferClass<Vector4> *g_00E065CC;
extern ShareBufferClass<float> *g_00E065D0;
extern ShareBufferClass<unsigned char> *g_00E065D4;

class ShaderClass
{
public:
	ShaderClass(const ShaderClass &s) { ShaderBits = s.ShaderBits; }
	ShaderClass &operator=(const ShaderClass &s) { ShaderBits = s.ShaderBits; return *this; }
	void Enable_Fog(const char *source);

	static ShaderClass _PresetAdditive2DShader;
	static ShaderClass _PresetAlpha2DShader;
	static ShaderClass _PresetAdditiveSpriteShader;
	static ShaderClass _PresetAlphaSpriteShader;
	static ShaderClass _PresetATestSpriteShader;
	static ShaderClass _PresetMultiplicativeSpriteShader;
private:
	unsigned int ShaderBits;
};
extern ShaderClass g_00DB6250;

class TextureClass
{
public:
	void Release_Ref();
};

class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
	TextureClass *Ptr;
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

class StreakLineClass
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void Render(RenderInfoClass &rinfo); // slot 12 (+0x30)
	void Reset_Line(void);
	void Set_Texture_Tile_Factor(float factor);
	void Set_Texture(TextureClass *texture);
	void Set_Shader(ShaderClass shader);
	void Set_LocsWidthsColors(unsigned int num_points, Vector3 *locs, float *widths,
		Vector4 *colors, unsigned int *personalities);
};
extern StreakLineClass *g_00E0626C;

class DX8Wrapper
{
public:
	static bool Get_Fog_Enable(void) { return FogEnable; }
protected:
	static bool FogEnable;
};

class Rva00561564;

class WW3D
{
	friend class Rva00561564;
	static bool IsCurrentlyRenderingShadowMap;
};

class Rva001F4E2D { public: bool rva001F4E2D(); };
class Rva001F4D2D { public: float rva001F4D2D(); };
class Rva001F4E1BSlot { public: const RGBColor *get() const; };
class Rva001F4DF9 { public: float rva001F4DF9(); };
class Rva001F4DC4 { public: float rva001F4DC4(); };

struct StreakParticle
{
	char m_pad00[0x1c];
	Vector3 m_pos; // +0x1C
	char m_pad28[0x3c];
	StreakParticle *m_next; // +0x64
	char m_pad68[0x20];
	UnsignedInt m_id; // +0x88
};

class StreakParticleStorage
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual StreakParticle *getFirstParticle(); // slot 8 (+0x20)
};

class Rva0004CABDSevenEight
{
public:
	int get() const;
};

class ParticleSystem
{
public:
	char m_pad00[8];
	Int m_shaderType; // +0x08
	char m_pad0C[4];
	AsciiString m_textureName; // +0x10
	char m_pad14[0x90];
	StreakParticleStorage *m_storage; // +0xA4
};
extern ParticleSystem *Make001FCBD7(void);


#include "Lib/Coord3D.h"
class WWMath {public: static float Random_Float();};
class GameClientRandomVariable {public:float getValue()const;private:unsigned data[3];};
struct LightningCounterView {char pad[0x54];int value54;int value58;};
class Rva00561564 {
public:
 virtual int rva00561564(RenderInfoClass &rinfo,void *bounds,int *particleCount);
private:
 ParticleSystem *getSystem()const {return m_system==0 ? Make001FCBD7() : m_system;}
 ParticleSystem *m_system;
 char pad08[0x1C-8];
 GameClientRandomVariable random0,random1,random2;
 float threshold40;
 bool tile44;char pad45[3];
 Vector3 points[3][30];
 Vector3 offsets[3][30];
 int lineCount;
 Vector3 direction,side,up;
 int lastID;
};
int Rva00561564::rva00561564(RenderInfoClass &rinfo,void*,int*)
{
 if(WW3D::IsCurrentlyRenderingShadowMap) return 0;
 int count=0;
 Vector3 *locs=g_00E065C8->Get_Array();
 float *widths=g_00E065D0->Get_Array();
 Vector4 *colors=g_00E065CC->Get_Array();
 unsigned char *angles=g_00E065D4->Get_Array();
 bool reset=false;
 int state=1;
 unsigned ids[512];
 if(!(unsigned char)((Rva0004CABDSevenEight*)getSystem())->get()) {
  StreakParticle *p=getSystem()->m_storage->getFirstParticle();
  if(p) {
   LightningCounterView *head=(LightningCounterView*)p;
   if(lastID!=head->value58) {
    lastID=head->value58; reset=true; state=head->value54;
    if(WWMath::Random_Float()<threshold40) lineCount=2;else lineCount=1;
   }
   for(;p;p=p->m_next) {
    float size=((Rva001F4D2D*)p)->rva001F4D2D();
    if(reset) ((LightningCounterView*)p)->value54=state;
    ids[count]=p->m_id;
    locs[count].X=p->m_pos.X;locs[count].Y=p->m_pos.Y;locs[count].Z=p->m_pos.Z;
    widths[count]=size;
    const RGBColor *color=((Rva001F4E1BSlot*)p)->get();
    if(color) {colors[count].X=color->red;colors[count].Y=color->green;colors[count].Z=color->blue;}
    else {colors[count].X=0;colors[count].Y=0;colors[count].Z=0;}
    colors[count].W=((Rva001F4DF9*)p)->rva001F4DF9();
    angles[count]=(unsigned char)(((Rva001F4DC4*)p)->rva001F4DC4()*255.0f/6.2831855f);
    ++count;if(count==512)break;
   }
  }
 }
 if(g_00E0626C && count>=2) {
  BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(getSystem()->m_textureName.str(),0,0);
  if(reset) {
   direction.X=locs[count-1].X-locs[0].X;direction.Y=locs[count-1].Y-locs[0].Y;direction.Z=locs[count-1].Z-locs[0].Z;
   ((Coord3D*)&direction)->normalize();
   up.X=0;up.Y=0;up.Z=1;
   side.X=up.Y*direction.Z-direction.Y*up.Z;side.Y=direction.X*up.Z-up.X*direction.Z;side.Z=up.X*direction.Y-up.Y*direction.X;
   up.X=side.Z*direction.Y-direction.Z*side.Y;up.Y=direction.Z*side.X-side.Z*direction.X;up.Z=direction.X*side.Y-side.X*direction.Y;
   for(int line=0;line<lineCount;++line) {
    Vector3 *linePoints=points[line];
    Vector3 *lineOffsets=offsets[line];
    for(int i=0;i<count;++i) {
     float a=0,b=0,c=0;
     if(i!=0 && i!=count-1) {
      a=random0.getValue();b=random1.getValue();c=random2.getValue();
      lineOffsets[i].X=a*side.X+b*up.X+c*direction.X;
      lineOffsets[i].Y=a*side.Y+b*up.Y+c*direction.Y;
      lineOffsets[i].Z=a*side.Z+b*up.Z+c*direction.Z;
      linePoints[i].X=locs[i].X+lineOffsets[i].X;linePoints[i].Y=locs[i].Y+lineOffsets[i].Y;linePoints[i].Z=locs[i].Z+lineOffsets[i].Z;
     } else {
      lineOffsets[i].X=locs[i].X;linePoints[i].X=locs[i].X;
      lineOffsets[i].Y=locs[i].Y;linePoints[i].Y=locs[i].Y;
      lineOffsets[i].Z=locs[i].Z;linePoints[i].Z=locs[i].Z;
     }
    }
   }
  } else {
   for(int line=0;line<lineCount;++line) {
    Vector3 *linePoints=points[line];
    Vector3 *lineOffsets=offsets[line];
    for(int i=0;i<count;++i) {
     if(i!=0 && i!=count-1) {
      linePoints[i].X=locs[i].X+lineOffsets[i].X;linePoints[i].Y=locs[i].Y+lineOffsets[i].Y;linePoints[i].Z=locs[i].Z+lineOffsets[i].Z;
     }else {linePoints[i].X=lineOffsets[i].X;linePoints[i].Y=lineOffsets[i].Y;linePoints[i].Z=lineOffsets[i].Z;}
    }
   }
  }
  g_00E0626C->Set_Texture((TextureClass*)&texture);
  g_00E0626C->Reset_Line();
  ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
  switch(getSystem()->m_shaderType) {
   case 2:shader=g_00DB6250;break;
   case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;
   case 4:shader=ShaderClass::_PresetATestSpriteShader;break;
   case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;
   case 6:shader=ShaderClass::_PresetAdditive2DShader;break;
   case 7:shader=ShaderClass::_PresetAlpha2DShader;break;
  }
  if(DX8Wrapper::Get_Fog_Enable())shader.Enable_Fog("HardwareFog");
  g_00E0626C->Set_Shader(shader);
  for(int line=0;line<lineCount;++line) {
   g_00E0626C->Set_LocsWidthsColors(count,points[line],g_00E065D0->Get_Array(),g_00E065CC->Get_Array(),ids);
   if(!tile44)g_00E0626C->Set_Texture_Tile_Factor(1.0f/(count-1));else g_00E0626C->Set_Texture_Tile_Factor(1.0f);
   g_00E0626C->Render(rinfo);
  }
 }
 return count;
}
