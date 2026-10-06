// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /G7 /EHsc /MD /DNDEBUG
//
// ?rva00210F96@LivingWorldManager@@QAEXXZ @ 0x00210F96 (48B).
// Unlock lane: missing callee of free functions; landing unblocks 0x003B8C06.
// Evidence: __thiscall reads ecx into esi; global theRadarWindowOverrideSource
// (?theRadarWindowOverrideSource@@3PAVRadarWindowOverrideSource@@A) then rowed
// Rva002D43A0Owner::rva002D43A0 0x002D43A0 and LivingWorldManager::
// SetUpRegionEffectsManager 0x00210D68 on this; +0x268 manager null gate then
// pinned Rva003EF008::rva003EF008 0x003EF008 call plus rowed
// LivingWorldRegionEffectsManager::rva003EF2FF 0x003EF2FF tail jmp; callers
// 0x003B8C59 0x003B8DF2 unclaimed so class from this-layout plus
// LivingWorldManager callee and +0x268 same as rowed 0x00210D68.
class Rva002D43A0Owner
{
public:
	void rva002D43A0();
};

class RadarWindowOverrideSource : public Rva002D43A0Owner
{
};

extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Rva003EF008
{
public:
	void rva003EF008();
};

class LivingWorldRegionEffectsManager : public Rva003EF008
{
public:
	void rva003EF2FF();
};

class LivingWorldManager
{
public:
	void rva00210F96();
	void SetUpRegionEffectsManager();
private:
	char m_pad[0x268];
	LivingWorldRegionEffectsManager *m_ptr268;
};

void LivingWorldManager::rva00210F96()
{
	theRadarWindowOverrideSource->rva002D43A0();
	SetUpRegionEffectsManager();
	if (!m_ptr268)
		return;
	m_ptr268->rva003EF008();
	return m_ptr268->rva003EF2FF();
}
