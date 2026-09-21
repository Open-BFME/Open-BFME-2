// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0DynamicShroudClearingRangeUpdateModuleData@@QAE@XZ, retail 0x0048B5C6,
// 82 bytes. ModuleData-side ctor in the DynamicShroud file-unit: the
// RadiusDecalTemplate member at +0x28 builds through the pinned 0x330E5D
// ctor (BFME1 RadiusDecal.h donor class, 0x34 bytes), then the six interval
// words at +8/+0xC/+0x10/+0x14/+0x1C/+0x20 zero, the spy-sat flag at +0x24
// clears and FinalVision at +0x18 is 0.0. Table 0xC4BE20 carries eight of
// these fields at identical offsets (BFME1 donor vote); factory 0x24CE44
// news 0x5C with this ctor as sole caller. Shape follows GiantBird (empty
// base, init-list holds only the vtable store so it lands between the
// implicit base call and the implicit member call, body assignments follow
// retail order); the +4 gap is unstored.

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();

private:
	unsigned char m_data[0x34];
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class DynamicShroudClearingRangeUpdateModuleData : public UpdateModuleData
{
public:
	DynamicShroudClearingRangeUpdateModuleData();

private:
	const void *m_vtable; // +0x00
	unsigned int m_unused04; // +0x04, unstored gap
	int m_shrinkDelay; // +0x08
	int m_shrinkTime; // +0x0C
	int m_growDelay; // +0x10
	int m_growTime; // +0x14
	float m_finalVision; // +0x18
	int m_changeInterval; // +0x1C
	int m_growInterval; // +0x20
	bool m_doSpySatFX; // +0x24
	unsigned char m_pad25[3];
	RadiusDecalTemplate m_gridDecalTemplate; // +0x28
};

// ??0DynamicShroudClearingRangeUpdateModuleData@@QAE@XZ @0x48B5C6
DynamicShroudClearingRangeUpdateModuleData::DynamicShroudClearingRangeUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4BEF8))
{
	m_shrinkDelay = 0;
	m_shrinkTime = 0;
	m_growDelay = 0;
	m_growTime = 0;
	m_changeInterval = 0;
	m_growInterval = 0;
	m_doSpySatFX = false;
	m_finalVision = 0.0f;
}
