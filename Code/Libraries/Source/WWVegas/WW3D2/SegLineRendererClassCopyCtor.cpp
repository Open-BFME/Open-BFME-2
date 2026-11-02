// ??0SegLineRendererClass@@QAE@ABV0@@Z
// cl: /EHsc /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// SegLineRendererClass copy constructor, retail 0x00191B50, 183 bytes.
// Zero Hour's initialiser list on the BFME2 layout, then *this = that. Kept in
// its own unit so seglinerenderer.cpp keeps its matched bodies.
//
// Color is a Vector3 built from a Vector3(1,1,1) temporary and the two UV
// offsets are Vector2 members with inline constructors, as in the reference
// class. Flattening them into loose floats makes MSVC 7.1 schedule the integer
// zero stores ahead of the float ones. BFME2 adds a float at +0x1C, which moves
// SubdivisionLevel to +0x20, and appends the vertex buffer size and pointer.

class TextureBaseClass
{
public:
	virtual ~TextureBaseClass();
	void Release_Ref();
	unsigned short Refs;
};

// The texture member's destructor is the rowed RefCountPtr<TextureClass> destructor
// (0x0017098D); this TU-local view spells that class so the unwind funclet calls it by name.
class TextureClass;
template<class T>
class RefCountPtr
{
public:
	RefCountPtr(TextureBaseClass *textureBase) : Ptr(textureBase) {}
	~RefCountPtr();
	TextureBaseClass *Ptr;
};

#include "ShaderClass.h"

#include "../../../../../reference/shims/wwmath/Vector2.h"

#include "../WWMath/Vector3Data.h"

class SegLineRendererClass
{
public:
	SegLineRendererClass(const SegLineRendererClass &that);
	~SegLineRendererClass();
	SegLineRendererClass &operator=(const SegLineRendererClass &that);

private:
	RefCountPtr<TextureClass> Texture;	// +0x00
	ShaderClass Shader;				// +0x04
	float Width;					// +0x08
	Vector3 Color;					// +0x0C
	float Opacity;					// +0x18
	float _BFME_Unknown_Member;		// +0x1C
	unsigned SubdivisionLevel;		// +0x20
	float NoiseAmplitude;			// +0x24
	float MergeAbortFactor;			// +0x28
	float TextureTileFactor;		// +0x2C
	unsigned LastUsedSyncTime;		// +0x30
	Vector2 CurrentUVOffset;		// +0x34
	Vector2 UVOffsetDeltaPerMS;		// +0x3C
	unsigned Bits;					// +0x44
	unsigned m_vertexBufferSize;	// +0x48
	void *m_vertexBuffer;			// +0x4C
};

SegLineRendererClass::SegLineRendererClass(const SegLineRendererClass &that) :
	Texture(0),
	Shader(ShaderClass::_PresetAdditiveSpriteShader),
	Width(0.0f),
	Color(Vector3(1, 1, 1)),
	Opacity(1.0f),
	_BFME_Unknown_Member(0.0f),
	SubdivisionLevel(0),
	NoiseAmplitude(0.0f),
	MergeAbortFactor(1.5f),
	TextureTileFactor(1.0f),
	LastUsedSyncTime(that.LastUsedSyncTime),
	CurrentUVOffset(0.0f, 0.0f),
	UVOffsetDeltaPerMS(0.0f, 0.0f),
	Bits(1),
	m_vertexBufferSize(0),
	m_vertexBuffer(0)
{
	*this = that;
}
