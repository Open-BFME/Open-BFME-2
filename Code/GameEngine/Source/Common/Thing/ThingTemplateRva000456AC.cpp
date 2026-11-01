// cl: /MD
// ?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z @0x000456AC 21B: ThingTemplate kind-bit test via rowed helper.
// Evidence: caller Team countKind 0x0039DC05 passes Object+4 template with kind index; offset 0x108 is ThingTemplate kind bits per Handicap and Rva00290EFE and StatsCollector; helper rowed at 0x001E4426.
bool __cdecl Rva001E4426Test(unsigned int *bits, int bit);

enum KindOfType { KINDOF_INVALID = -1 };

#include "../../../Include/Common/ThingTemplate.h"

__declspec(noinline) inline bool ThingTemplate::isKindOf(KindOfType bit) const
{
	return Rva001E4426Test((unsigned int *)((const char *)this + 0x108), bit);
}

// ?rva000456C1@Rva000456C1Owner@@QAE_NH@Z @0x000456C1 8B, directly after
// rva000456AC: forwards the kind-bit test to the ThingTemplate pointer held
// at +4 (mov ecx, [ecx+4]; tail jump). Owner and name are address-derived.
class Rva000456C1Owner
{
public:
	bool rva000456C1(int bit);
private:
	void *m_00;
	const ThingTemplate *m_template04;
};

bool Rva000456C1Owner::rva000456C1(int bit)
{
	return m_template04->isKindOf((KindOfType)bit);
}
