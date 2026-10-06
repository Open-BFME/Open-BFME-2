// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva004BADC1@EvacuateDamage@@QAEMXZ @ 0x004BADC1 92B
// EvacuateDamage pending-evacuation sum with expiry purge. Evidence: sole
// caller 0x004BAFB1 (EvacuateDamage::onDamage) plus ModuleData tracking span
// at +0x14 (PanicUpdateModuleDataCtor 0x004BAD10) plus list at +0x14
// (EvacuateDamage ctor 0x004BAE1D via List_base BfmePod8 0x35C9A6) plus
// TheGameLogic frame at +0x40 (global 0x00DFE78C) plus list<int> erase fold
// at 0x00438539. BFME1 donor EvacuateDamage_onDamage bfmeSum pattern.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct EvacuationRecord
{
	float m_amount;
	int m_frame;
};

#include "ascii_string.h"

class EvacuateDamageModuleData
{
public:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_evacuationWeapon;
	int m_damageTypeToTrack;
	float m_panicThreshold;
	int m_trackingTimeSpan;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	int m_frame;
};

extern GameLogic *TheGameLogic;

class EvacuateDamage
{
public:
	float rva004BADC1();
private:
	void *m_vtable;
	EvacuateDamageModuleData *m_moduleData;
	void *m_object;
	unsigned char m_pad0C[8];
	_STL::list<EvacuationRecord> m_pendingEvacuations;
};

float EvacuateDamage::rva004BADC1()
{
	int cutoff = TheGameLogic->m_frame - m_moduleData->m_trackingTimeSpan;
	float sum = 0.0f;
	for (_STL::list<EvacuationRecord>::iterator it = m_pendingEvacuations.begin(); it != m_pendingEvacuations.end(); )
	{
		if (it->m_frame <= cutoff)
		{
			it = m_pendingEvacuations.erase(it);
		}
		else
		{
			sum += it->m_amount;
			++it;
		}
	}
	return sum;
}
