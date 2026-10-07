// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// LivingWorldCampaignManager.cpp -- campaign-manager members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and the index overload it calls (0x003B8C06); retail supplies the
// bytes. The name lookup (0x003B8E2B, unnamed in WB) returns -1 for an
// unknown campaign.
#include "ascii_string.h"

typedef int Int;

typedef unsigned int UnsignedInt;

// A campaign of m_campaignVector: its spawn-army lookup (0x0052BFE1, unnamed
// in WB, unrowed) scans 0xB8-byte entries and returns the match or NULL.
class Rva0052BFE1
{
public:
	void *rva0052BFE1(Int a, Int b);				// 0x0052BFE1
	unsigned char opaque_00[4];
	AsciiString m_name04;
};

// STLport vector view: three pointers, inline size() and operator[].
template <class T> class CampaignVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { return m_start[i]; }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

class LivingWorldCampaignManager
{
public:
	void StartNewCampaign(const AsciiString &campaignName);
	void StartNewCampaign(Int campaignIndex);			// 0x003B8C06
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);
	Rva0052BFE1 *rva003B8EDC(const AsciiString &name);

private:
	Int rva003B8E2B(const AsciiString &campaignName);		// 0x003B8E2B

	unsigned char m_pad00[0x10];
	Int m_campaignIndex;					// +0x10 (WB assert name)
	CampaignVectorView<Rva0052BFE1 *> m_campaignVector;	// +0x14
};

// LivingWorldCampaignManager::StartNewCampaign, retail 0x003B8E6C.
void LivingWorldCampaignManager::StartNewCampaign(const AsciiString &campaignName)
{
	Int index = rva003B8E2B(campaignName);
	if (index != -1)
		StartNewCampaign(index);
}

// LivingWorldCampaignManager::UseGenericSpawnArmyForPlayer, retail 0x003B8CE0
// (38 bytes): WB names it (assert at LivingWorldCampaignManager.cpp:318, "no
// active campaign"); the active campaign answers, NULL without one.
void *LivingWorldCampaignManager::UseGenericSpawnArmyForPlayer(Int a, Int b)
{
	if (m_campaignIndex >= 0 && (UnsignedInt)m_campaignIndex < m_campaignVector.size())
	{
		Rva0052BFE1 *campaign = m_campaignVector[m_campaignIndex];
		return campaign->rva0052BFE1(a, b);
	}
	return 0;
}

// ?rva003B8EDC@LivingWorldCampaignManager@@QAEPAVRva0052BFE1@@ABVAsciiString@@@Z
// Native Ghidra extent 0x003B8EDC..0x003B8F20; RET 4. It walks the
// existing campaign pointer vector and calls the verified string compare
// worker at 0x000069D6 on each entry's +4 member. The method name is unknown.
Rva0052BFE1 *LivingWorldCampaignManager::rva003B8EDC(const AsciiString &name)
{
	for (UnsignedInt i = 0; i < m_campaignVector.size(); ++i)
	{
		if (m_campaignVector[i]->m_name04.compare(name) == 0)
			return m_campaignVector[i];
	}
	return 0;
}

// ?rva003B8E2B@LivingWorldCampaignManager@@AAEHABVAsciiString@@@Z
// Native Ghidra extent 0x003B8E2B..0x003B8E6C; RET 4. The same scan as
// 0x003B8EDC returns the matched index instead, or -1 for an unknown name.
Int LivingWorldCampaignManager::rva003B8E2B(const AsciiString &campaignName)
{
	for (UnsignedInt i = 0; i < m_campaignVector.size(); ++i)
	{
		if (m_campaignVector[i]->m_name04.compare(campaignName) == 0)
			return i;
	}
	return -1;
}
