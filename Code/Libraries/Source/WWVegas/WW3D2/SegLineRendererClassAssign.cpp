// cl: /O2 /G7 /MD
//
// SegLineRendererClass::operator=, retail 0x001912F0, 151 bytes.
// Dedicated TU so seglinerenderer.cpp keeps its matched bodies.
// Copies _BFME_Unknown_Member before Color so the 0x1C store lands early.

class TextureBaseClass
{
public:
	virtual ~TextureBaseClass();
	void Release_Ref();
	unsigned short Refs;
};

class SegLineRendererClass
{
public:
	SegLineRendererClass &operator=(const SegLineRendererClass &that);

private:
	TextureBaseClass *Texture;
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

SegLineRendererClass &SegLineRendererClass::operator=(const SegLineRendererClass &that)
{
	if (this != &that) {
		if (that.Texture)
			that.Texture->Refs++;
		if (Texture)
			Texture->Release_Ref();
		Texture = that.Texture;
		ShaderBits = that.ShaderBits;
		Width = that.Width;
		_BFME_Unknown_Member = that._BFME_Unknown_Member;
		ColorX = that.ColorX;
		ColorY = that.ColorY;
		ColorZ = that.ColorZ;
		Opacity = that.Opacity;
		SubdivisionLevel = that.SubdivisionLevel;
		NoiseAmplitude = that.NoiseAmplitude;
		MergeAbortFactor = that.MergeAbortFactor;
		TextureTileFactor = that.TextureTileFactor;
		LastUsedSyncTime = that.LastUsedSyncTime;
		CurrentUVOffsetX = that.CurrentUVOffsetX;
		CurrentUVOffsetY = that.CurrentUVOffsetY;
		UVOffsetDeltaPerMSX = that.UVOffsetDeltaPerMSX;
		UVOffsetDeltaPerMSY = that.UVOffsetDeltaPerMSY;
		Bits = that.Bits;
	}
	return *this;
}
