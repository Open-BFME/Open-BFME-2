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
// Address-only view of the receiver returned by the native active-entry lookup.
// Its 27-byte folded getter copies the +4 AsciiString through the hidden result.
// Neither the record class nor the getter's original identity is established.
class Rva00564DF2NameView { public: AsciiString rva00564DF2() const; };

class Rva0052BFE1
{
public:
	Rva00564DF2NameView *rva0052C119();
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
	AsciiString rva003B8D06();
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

// The target's adjacent record lookup uses a separate structural view.
// Callers 0x004E1755 and 0x004E23C1 already use this address-derived
// receiver/key ABI; its original class relationship remains unknown.
struct Rva003B8E89Record
{
	unsigned char opaque_00[0x18];
	AsciiString name_18;
	unsigned char opaque_1c[0x4c];
};

class Rva003B8E89
{
public:
	void *rva003B8E89(void *key);
private:
	unsigned char opaque_00[0x20];
	CampaignVectorView<Rva003B8E89Record> m_records;
};

// ?rva003B8E89@Rva003B8E89@@QAEPAXPAX@Z
// Native Ghidra extent 0x003B8E89..0x003B8EDC; RET 4. Pointer difference
// divided by 0x68 proves the record stride, and the rowed compare worker
// at 0x000069D6 establishes the string view at each record's +0x18.
void *Rva003B8E89::rva003B8E89(void *key)
{
	for (UnsignedInt i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i].name_18.compare(*(const AsciiString *)key) == 0)
			return &m_records[i];
	}
	return 0;
}

// Native Ghidra extent 0x003B8D06..0x003B8D4D, 71 bytes, RET 4 hidden result.
// The existing index/vector layout gates access to the active campaign. Calls
// at 0x003B8D28 and 0x003B8D32 prove the no-argument entry lookup and AsciiString
// return ABI; invalid indices return the named AsciiString::TheEmptyString.
// Separate entry and return expressions preserve the native call ordering.
AsciiString LivingWorldCampaignManager::rva003B8D06()
{
    if (m_campaignIndex >= 0 && (UnsignedInt)m_campaignIndex < m_campaignVector.size())
        {
        Rva00564DF2NameView *entry = m_campaignVector[m_campaignIndex]->rva0052C119();
        return entry->rva00564DF2();
    }
    return AsciiString::TheEmptyString;
}
