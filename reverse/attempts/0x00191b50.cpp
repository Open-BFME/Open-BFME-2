// ??0SegLineRendererClass@@QAE@ABV0@@Z
// partial score=0.92 date=2026-09-10
// cl: /O2 /G7 /arch:SSE2 /EHsc /MD
//
// SegLineRendererClass copy constructor, retail 0x00191B50, 183 bytes.
// Default-like member init, LastUsedSyncTime from that, then operator=.

class TextureBaseClass
{
public:
	virtual ~TextureBaseClass();
	void Release_Ref();
	unsigned short Refs;
};

class TextureHolder
{
public:
	TextureHolder() : Ptr(0) {}
	~TextureHolder();
	TextureBaseClass *Ptr;
};

class ShaderClass
{
public:
	static ShaderClass _PresetAdditiveSpriteShader;
	unsigned ShaderBits;
};

class SegLineRendererClass
{
public:
	SegLineRendererClass(const SegLineRendererClass &that);
	~SegLineRendererClass();
	SegLineRendererClass &operator=(const SegLineRendererClass &that);

private:
	TextureHolder Texture;
	unsigned ShaderBits;
	float Width;
	float ColorX;
	float ColorY;
	float ColorZ;
	float Opacity;
	float _BFME_Unknown_Member;
	unsigned SubdivisionLevel;
	float NoiseAmplitude;
	float MergeAbortFactor;
	float TextureTileFactor;
	unsigned LastUsedSyncTime;
	float CurrentUVOffsetX;
	float CurrentUVOffsetY;
	float UVOffsetDeltaPerMSX;
	float UVOffsetDeltaPerMSY;
	unsigned Bits;
	unsigned m_vertexBufferSize;
	void *m_vertexBuffer;
};

SegLineRendererClass::SegLineRendererClass(const SegLineRendererClass &that) :
	Texture(),
	ShaderBits(ShaderClass::_PresetAdditiveSpriteShader.ShaderBits),
	Width(0.0f),
	ColorX(1.0f),
	ColorY(1.0f),
	ColorZ(1.0f),
	Opacity(1.0f),
	_BFME_Unknown_Member(0.0f),
	SubdivisionLevel(0),
	NoiseAmplitude(0.0f),
	MergeAbortFactor(1.5f),
	TextureTileFactor(1.0f),
	LastUsedSyncTime(that.LastUsedSyncTime),
	CurrentUVOffsetX(0.0f),
	CurrentUVOffsetY(0.0f),
	UVOffsetDeltaPerMSX(0.0f),
	UVOffsetDeltaPerMSY(0.0f),
	Bits(1),
	m_vertexBufferSize(0),
	m_vertexBuffer(0)
{
	*this = that;
}
