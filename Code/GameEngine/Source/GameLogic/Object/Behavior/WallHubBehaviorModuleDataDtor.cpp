// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1WallHubBehaviorModuleData@@UAE@XZ, retail 0x00452F9F, 129 bytes.
// ModuleData dtor: reinstalls the vtable 0x00C3FF98, tears down the six
// template-name strings at +0x28/+0x24/+0x20/+0x1C/+0x18/+0x14 through the
// folded AsciiString dtor at 0x36410, tears down the segment template name
// vector at +0x08 through the rowed vector<AsciiString> dtor at 0x0002CC70,
// then restores the Snapshot base vtable 0x00BBB554 through the TU-local
// inline base dtor. Seven EH states for the seven members; frameless
// companion ctor at 0x453020 proves the layout (vptr +0, vector +0x08,
// strings +0x14..+0x28, size 0x3C per the factory at 0x24A94C). Table
// 0x00C3FED8 names the members; the ??_G caller at 0x4530B4 is the slot-0
// deleting dtor. Shape follows the landed W3DLaserDrawModuleDataDtor and
// BuffNuggetFXNuggetDtor TUs; the own vtable resolves through the ??_7 pin
// at 0x00C3FF98.

#include <vector>

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class WallHubBehaviorModuleData : public Snapshot
{
public:
	virtual ~WallHubBehaviorModuleData();

private:
	unsigned char m_pad04[4]; // +0x04
	_STL::vector<AsciiString> m_segmentTemplateNames; // +0x08
	AsciiString m_hubCapTemplateName; // +0x14
	AsciiString m_defaultSegmentTemplateName; // +0x18
	AsciiString m_cliffCapTemplateName; // +0x1C
	AsciiString m_shoreCapTemplateName; // +0x20
	AsciiString m_borderCapTemplateName; // +0x24
	AsciiString m_elevatedSegmentTemplateName; // +0x28
	float m_builderRadius; // +0x2C
	float m_maxBuildoutDistance; // +0x30
	int m_options; // +0x34
	int m_staggeredBuildFactor; // +0x38
};

typedef char AsciiExtent[sizeof(AsciiString) == 4 ? 1 : -1];

WallHubBehaviorModuleData::~WallHubBehaviorModuleData()
{
}
