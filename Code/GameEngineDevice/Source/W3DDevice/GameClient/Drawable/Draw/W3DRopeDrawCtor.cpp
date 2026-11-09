// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??0W3DRopeDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000CA752 164B: W3DRopeDraw
// public ctor. Donor BFME1 W3DRopeDraw.cpp ctor body verbatim plus m_wobbleRate:
// base DrawModule(thing, moduleData) through rowed 0x000B19A1, RopeDrawInterface's
// own pure-call table lands at [esi+0xC] before the derived secondary overwrites
// it, the rowed _Vector_base ctor 0x00211E58 takes the allocator temp over the
// outgoing-args area ([ebp+0xF]), the inlined vector clear runs through rowed
// BfmePod16 erase 0x002BF70F, and the 14 float stores carry m_curLen..m_wobbleAmp
// before it (m_maxLen's 1.0f at VA 0x00BBB8D8, m_width's 0.5f at VA 0x00BC26F0)
// then m_wobbleRate/m_curWobblePhase/m_curZOffset after (the donor omits
// m_wobbleRate; its store sits at +0x48 in the post-erase group).
// Class kit verbatim from the verified W3DRopeDrawDtor.cpp.
#include <vector>
#include "../../../../../../Libraries/Include/Lib/RGBColor.h"

struct BfmePod16 { int a[4]; };

class Thing;
class ModuleData;

#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"
inline DrawModule::~DrawModule() {} // retail inlines this into the derived destructors

class RopeDrawInterface
{
public:
	virtual void initRopeParms(float length, float width, const RGBColor &color, float wobbleLen, float wobbleAmp, float wobbleRate) = 0;
	virtual void setRopeCurLen(float length) = 0;
	virtual void setRopeSpeed(float curSpeed, float maxSpeed, float accel) = 0;
};

class W3DRopeDrawPrimary : public DrawModule
{
public:
	__forceinline W3DRopeDrawPrimary(Thing *thing, const ModuleData *moduleData)
		: DrawModule(thing, moduleData)
	{
	}
};

class W3DRopeDraw : public W3DRopeDrawPrimary, public RopeDrawInterface
{
public:
	W3DRopeDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DRopeDraw();
	virtual void initRopeParms(float length, float width, const RGBColor &color,
		float wobbleLen, float wobbleAmp, float wobbleRate);
	virtual void setRopeCurLen(float length);
	virtual void setRopeSpeed(float curSpeed, float maxSpeed, float accel);
private:
	_STL::vector<BfmePod16> m_segments; // +0x10
	void tossSegments();
	float m_curLen; // +0x1C
	float m_maxLen; // +0x20
	float m_width; // +0x24
	RGBColor m_color; // +0x28
	float m_curSpeed; // +0x34
	float m_maxSpeed; // +0x38
	float m_accel; // +0x3C
	float m_wobbleLen; // +0x40
	float m_wobbleAmp; // +0x44
	float m_wobbleRate; // +0x48
	float m_curWobblePhase; // +0x4C
	float m_curZOffset; // +0x50
};

W3DRopeDraw::W3DRopeDraw( Thing *thing, const ModuleData* moduleData )
	: W3DRopeDrawPrimary( thing, moduleData )
	, m_segments(_STL::allocator<BfmePod16>())
{
	m_curLen = 0.0f;
	m_maxLen = 1.0f;
	m_width = 0.5f;
	m_color.red = 0.0f;
	m_color.green = 0.0f;
	m_color.blue = 0.0f;
	m_curSpeed = 0.0f;
	m_maxSpeed = 0.0f;
	m_accel = 0.0f;
	m_wobbleLen = m_maxLen;	// huge
	m_wobbleAmp = 0.0f;
	m_segments.clear();
	m_wobbleRate = 0.0f;
	m_curWobblePhase = 0.0f;
	m_curZOffset = 0.0f;
}
