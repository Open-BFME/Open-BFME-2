// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2

#pragma optimize("s", on)
#include "../WWMath/vector2.h"
#pragma optimize("", on)

class TextureClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	unsigned int ShaderBits;
	static ShaderClass _PresetAdditiveSpriteShader;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
	static unsigned int SyncTime;
};

class VertexFormatXYZUV1;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streakRender.h
class StreakRendererClass
{
public:
	StreakRendererClass();
	void Set_Merge_Intersections(int onoff);
	void Set_Freeze_Random(int onoff);
	void Set_Disable_Sorting(int onoff);
	void Set_End_Caps(int onoff);
	void Set_UV_Offset_Rate(const Vector2 &rate);

private:
	enum { DEFAULT_BITS = 1 };
	TextureClass *Texture;
	ShaderClass Shader;
	float Width;
	Vector3 Color;
	float Opacity;
	unsigned int SubdivisionLevel;
	float NoiseAmplitude;
	float MergeAbortFactor;
	float TextureTileFactor;
	unsigned int LastUsedSyncTime;
	Vector2 CurrentUVOffset;
	Vector2 UVOffsetDeltaPerMS;
	unsigned int Bits;
	unsigned int m_vertexBufferSize;
	VertexFormatXYZUV1 *m_vertexBuffer;
};

// StreakRendererClass::StreakRendererClass: defined in streakRender.cpp (its row's unit).

// StreakRendererClass::Set_Merge_Intersections: defined in streakRender.cpp (its row's unit).

// StreakRendererClass::Set_Freeze_Random: defined in streakRender.cpp (its row's unit).

// StreakRendererClass::Set_Disable_Sorting: defined in streakRender.cpp (its row's unit).

// StreakRendererClass::Set_End_Caps: defined in streakRender.cpp (its row's unit).

void StreakRendererClass::Set_UV_Offset_Rate(const Vector2 &rate)
{
	UVOffsetDeltaPerMS = rate * 0.001f;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?SyncTime@WW3D@@2IA=?SyncTime@WW3D@@0IA")
