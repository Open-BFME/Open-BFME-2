// cl: /DNDEBUG /MD /EHsc
// stlport
//
// ?initRopeParms@W3DRopeDraw@@UAEXMMABURGBColor@@MMM@Z @0x000CAC25 131B: W3DRopeDraw::initRopeParms (vslot 68 of 0x007CBC40).
// Donor BFME1 game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp verbatim: m_maxLen=max(1,length)
// m_curLen=0 m_width=width m_color=color m_wobbleLen=min(m_maxLen wobbleLen) m_wobbleAmp/Rate m_curZOffset=0 then tossSegments
// (rowed 0x000CA84D) plus buildSegments (pinned 0x000CA9F1). MI layout from W3DRopeDrawTossSegments.cpp (DrawModule 12 + second
// base at +0xC); the body addresses members from the second-base this and calls on full this (ecx-0xC).
#include <vector>

typedef float Real;

struct RGBColor
{
	float r, g, b;
};

struct BfmePod16 { int a[4]; };

class Line3DClass
{
public:
	virtual void Release();
};

class BfmeScene
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void Remove_Render_Object(Line3DClass *obj);
};

class W3DDisplay
{
public:
	static BfmeScene *m_3DScene;
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();
	void *m_moduleData;
	void *m_drawable;
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class RopeDrawInterface
{
public:
	virtual void initRopeParms(Real length, Real width, const RGBColor &color, Real wobbleLen, Real wobbleAmp, Real wobbleRate) = 0;
};

struct SegInfo
{
	Line3DClass *line;
	Line3DClass *softLine;
	float wobbleAxisX;
	float wobbleAxisY;
};

class W3DRopeDraw : public DrawModule, public RopeDrawInterface
{
public:
	virtual void initRopeParms(Real length, Real width, const RGBColor &color, Real wobbleLen, Real wobbleAmp, Real wobbleRate);

private:
	_STL::vector<BfmePod16> m_segments;
	float m_curLen;
	float m_maxLen;
	float m_width;
	RGBColor m_color;
	float m_curSpeed;
	float m_maxSpeed;
	float m_accel;
	float m_wobbleLen;
	float m_wobbleAmp;
	float m_wobbleRate;
	float m_curWobblePhase;
	float m_curZOffset;

	void tossSegments();
	void buildSegments();
};

static const Real &bfmeMax(const Real &a, const Real &b)
{
	return a > b ? a : b;
}

static const Real &bfmeMin(const Real &a, const Real &b)
{
	return a < b ? a : b;
}

void W3DRopeDraw::initRopeParms(Real length, Real width, const RGBColor &color, Real wobbleLen, Real wobbleAmp, Real wobbleRate)
{
	const Real one = 1.0f;
	m_maxLen = bfmeMax(one, length);
	m_curLen = 0.0f;
	m_width = width;
	m_color = color;
	m_wobbleLen = bfmeMin(m_maxLen, wobbleLen);
	m_wobbleAmp = wobbleAmp;
	m_wobbleRate = wobbleRate;
	m_curZOffset = 0.0f;

	tossSegments();
	buildSegments();
}
