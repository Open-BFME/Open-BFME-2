// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??0W3DLaserDrawModuleData@@QAE@XZ, retail 0x000C9A6F, 120 bytes.
// Frameless ModuleData ctor over an inline base holding the two colors at
// +0x08/+0x0C (orl -1 each, no base call since the base has no virtuals and
// its ctor inlines): implicit derived vtable 0x00BCB960 at +0x00, texture
// vector at +0x2C through the ICF-folded BfmeE16 Vector_base at 0x00211E58
// (allocator temp on esp, Floor precedent for the true AsciiString elements),
// OrnamentData envelope at +0x4C through the pinned init() at 0x000C9251
// (53B leaf, FadeAndDieOrnament precedent; the layout matches the BFME1
// BfmeEnvelope donor), then the INI-table fields in donor order with the two
// envelope resets (+0x58/+0x70) inlined and grouped with the ecx-zero stores.
// Table 0x00BCB840 proves the names (NumBeams/Inner/OuterBeamWidth/
// Inner/OuterColor/MaxIntensityLifetime/FadeLifetime/Texture/ScrollRate/Tile/
// Segments/ArcHeight/SegmentOverlapRatio/TilingScalar/FanWidth/Envelope,
// matching the BFME1 W3DLaserDraw donor plus the FanWidth/Envelope tail).
// Factory 0x00064962 news 0x74 (sole caller). Row supersedes the ctor pin.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

typedef unsigned int Color;
typedef unsigned int UnsignedInt;
typedef float Real;

struct OrnamentData
{
	void init() throw();
	unsigned char m_pad00[0x0C];
	int m_reset0C;
	unsigned char m_pad10[0x24 - 0x10];
	int m_reset24;
};

class W3DLaserDrawModuleDataBase
{
public:
	W3DLaserDrawModuleDataBase()
		: m_innerColor((Color)-1),
		  m_outerColor((Color)-1)
	{
	}

private:
	unsigned char m_pad04[4];	// +0x04
	Color m_innerColor;		// +0x08 InnerColor
	Color m_outerColor;		// +0x0C OuterColor
};

class W3DLaserDrawModuleData : public W3DLaserDrawModuleDataBase
{
public:
	W3DLaserDrawModuleData();
	virtual ~W3DLaserDrawModuleData();

private:
	Real m_innerBeamWidth;			// +0x10 InnerBeamWidth
	Real m_outerBeamWidth;			// +0x14 OuterBeamWidth
	Real m_scrollRate;			// +0x18 ScrollRate
	bool m_tile;				// +0x1C Tile
	UnsignedInt m_numBeams;			// +0x20 NumBeams
	UnsignedInt m_maxIntensityFrames;	// +0x24 MaxIntensityLifetime
	UnsignedInt m_fadeFrames;		// +0x28 FadeLifetime
	_STL::vector<BfmeE16> m_textureName;	// +0x2C Texture
	UnsignedInt m_segments;			// +0x38 Segments
	Real m_arcHeight;			// +0x3C ArcHeight
	Real m_segmentOverlapRatio;		// +0x40 SegmentOverlapRatio
	Real m_tilingScalar;			// +0x44 TilingScalar
	Real m_fanWidth;			// +0x48 FanWidth
	OrnamentData m_envelope;		// +0x4C Envelope
};

// ??0W3DLaserDrawModuleData@@QAE@XZ @0x000C9A6F
W3DLaserDrawModuleData::W3DLaserDrawModuleData()
{
	float fzero = 0.0f;
	OrnamentData *envelope = &m_envelope;
	envelope->init();
	m_innerBeamWidth = fzero;
	m_outerBeamWidth = 1.0f;
	m_numBeams = 1;
	m_maxIntensityFrames = 0;
	m_fadeFrames = 0;
	m_scrollRate = fzero;
	m_tile = false;
	m_segments = 1;
	m_arcHeight = fzero;
	m_segmentOverlapRatio = fzero;
	m_tilingScalar = 1.0f;
	m_fanWidth = fzero;
	envelope->m_reset0C = 0;
	envelope->m_reset24 = 0;
}
