// cl: /O1 /MD /GX /DNDEBUG
//
// ??0AnimalAIUpdateModuleData@@QAE@XZ, retail 0x0024BE43 (55 bytes).
// Frameless ctor over the pinned Transport base (0x26E5D7): three int
// defaults of 10 at +0x70/+0x74/+0x78 first (the push-pop constant idiom),
// then the compiler sinks the folded vtable 0x00C4B6C8 below those stores
// through the ??_7 pin (WanderAI precedent: virtual class with
// declared-only virtual dtor and no source store), then FleeRange 0x14 at
// +0x64 plus FleeDistance 0x64 at +0x68 plus WanderPercentage 0x32 at +0x6C
// matching the class parse table 0x00BEEB88 (rowed proc 0x24BE7A), then the
// true byte at +0x7C. Field identity is the chained table; the rowed
// AnimalAIUpdate pool key (0x47EC1A) names the family. Sole raw caller is
// the ModuleData factory 0x24BED0 which news 0x80.

class TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class AnimalAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	AnimalAIUpdateModuleData();
	virtual ~AnimalAIUpdateModuleData();

private:
	int m_fleeRange; // +0x64
	int m_fleeDistance; // +0x68
	int m_wanderPercentage; // +0x6C
	int m_unk70; // +0x70
	int m_unk74; // +0x74
	int m_unk78; // +0x78
	bool m_unk7C; // +0x7C
};

AnimalAIUpdateModuleData::AnimalAIUpdateModuleData()
{
	m_unk70 = 10;
	m_unk74 = 10;
	m_unk78 = 10;
	m_fleeRange = 0x14;
	m_fleeDistance = 0x64;
	m_wanderPercentage = 0x32;
	m_unk7C = true;
}
