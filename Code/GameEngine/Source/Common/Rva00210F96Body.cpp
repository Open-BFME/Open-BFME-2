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
#include "ascii_string.h"

// The target body reads the pointer at 0x00DFEF10, then offsets +0xB0 and +8.
// Keep the pointee opaque here; only the offsets and direct call targets are
// established by retail bytes. The +0x2C value is passed to 0x003EEDD6 with
// this as ECX. Its name remains address-derived and its semantics unresolved.
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;
extern AsciiString g_Rva00E02E84;

class Rva003EEDD6
{
public:
	void rva003EEDD6(int value);
};

class Rva004E3629
{
public:
	void rva004E3629(const AsciiString &name, int value);
};

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

void Rva003EF008::rva003EF008()
{
	void *entry = *(void **)((char *)g_009FEF10 + 0xB0);
	entry = *(void **)((char *)entry + 8);
	void *argument;
	if (entry)
		argument = (char *)entry + 0x2C;
	else
		argument = 0;
	if (argument)
		((Rva003EEDD6 *)this)->rva003EEDD6((int)argument);
	((Rva004E3629 *)((char *)this + 8))->rva004E3629(g_Rva00E02E84, 0);
}

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
