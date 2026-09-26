// cl: /O1 /MD /arch:SSE /G7
//
// ?Rva0027D815@Rva0062AF7@@UAEMMM@Z retail 0x0027D815 70 bytes.
// Vslot 25 (offset 0x64) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ
// whose slot 2 returns W3DTerrainLogic and slot 15 is isClearLineOfSight.
// Shared with base TerrainLogic vtable 0x007FB2C8 at same address. Calls slot
// 19 (offset 0x4C unclaimed 0x0027D77D 5-arg bool) with x y and two float outs
// plus 0 and returns a minus b on true else pooled 0.0f at retail 0x007BAEAC.
// Identity is class plus slot and method name is honest address name.
// Secondary MI vptrs plus 0x04 plus 0x10 plus 0x14 omitted as body touches
// primary only. Flags per section 4.1: /O1 for EBP frame plus /arch:SSE for
// xorps and movss float zeroing.
class Rva0062AF7
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual bool Rva0027D77D(float x, float y, float *a, float *b, bool *c);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual float Rva0027D815(float x, float y);
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual float Rva0027D85B(void *water);
	virtual void slot31();
	virtual void Rva0027D88E(void *water, float finalHeight, float transitionTime, float damageAmount);

private:
	char m_pad04[0x64];
	struct WaterEntry
	{
		void *waterTable;
		float changePerFrame;
		float targetHeight;
		float damageAmount;
		float currentHeight;
	};
	WaterEntry m_entries[64];
	int m_count;
};
float Rva0062AF7::Rva0027D815(float x, float y)
{
	float a = 0.0f;
	float b = 0.0f;
	if (!Rva0027D77D(x, y, &a, &b, 0))
		return 0.0f;
	return a - b;
}

//
// ?Rva0027D88E@Rva0062AF7@@UAEXPAXMMM@Z retail 0x0027D88E 210 bytes.
// Vslot 32 (offset 0x80) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ.
// Donor: BFME1 TerrainLogic::changeWaterHeightOverTime in
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// (dedup swap-with-last via rep movsd, getWaterHeight via slot 0x78, then
// (final-current)/(LogicFrames*transition) with LogicFrames global 0x00DBA4E4).
// Array at +0x68 stride 0x14 count at +0x568 max 64. Identity class plus slot,
// honest address name. Flags: /O1 for EBP frame plus /arch:SSE for movss
// float moves plus /G7 for imul 0x14 and edx loop index (section 4.1).
void Rva0062AF7::Rva0027D88E(void *water, float finalHeight, float transitionTime, float damageAmount)
{
#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)
	enum { MAX_DYNAMIC_WATER = 64 };
	if (m_count >= MAX_DYNAMIC_WATER)
		return;
	if (water == 0)
		return;
	for (int i = 0; i < m_count; ++i)
	{
		if (m_entries[i].waterTable == water)
		{
			m_entries[i] = m_entries[m_count - 1];
			--m_count;
			--i;
		}
	}
	float currentHeight = Rva0027D85B(water);
	m_entries[m_count].waterTable = water;
	m_entries[m_count].changePerFrame = (finalHeight - currentHeight) / (LogicFramesPerSecond * transitionTime);
	m_entries[m_count].targetHeight = finalHeight;
	m_entries[m_count].damageAmount = damageAmount;
	m_entries[m_count].currentHeight = currentHeight;
	++m_count;
}
