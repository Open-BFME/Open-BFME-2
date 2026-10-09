// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// LivingWorldCampaignManager.cpp -- campaign-manager members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and the index overload it calls (0x003B8C06); retail supplies the
// bytes. The name lookup (0x003B8E2B, unnamed in WB) returns -1 for an
// unknown campaign.
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef int Int;

typedef unsigned int UnsignedInt;

// A campaign of m_campaignVector: its spawn-army lookup (0x0052BFE1, unnamed
// in WB, unrowed) scans 0xB8-byte entries and returns the match or NULL.
// Address-only view of the receiver returned by the native active-entry lookup.
// Its 27-byte folded getter copies the +4 AsciiString through the hidden result.
// Neither the record class nor the getter's original identity is established.
class Rva00564DF2NameView { public: AsciiString rva00564DF2() const; };

class GlobalData
{
public:
	char m_pad[0x86];
	unsigned char m_86;
	char m_pad87[0x8C - 0x87];
	AsciiString m_8C;
};

extern GlobalData *TheWritableGlobalData;

class Rva0052C036
{
public:
	bool rva0052C036();
	bool rva0052C9F9();
};

class Rva0052BFE1 : public Rva0052C036
{
public:
	Rva00564DF2NameView *rva0052C119();
    Rva00564DF2NameView *rva0052C7A2(const AsciiString &name);
	void *rva0052BFE1(Int a, Int b);				// 0x0052BFE1
	unsigned char opaque_00[4];
	AsciiString m_name04;
	unsigned char opaque_08[0x4D - 0x08];
	unsigned char m_4D;
};

// The campaign's 15-byte const getter 0x0052BAB2 (rowed under an int return)
// supplies the name SelectCampaign takes.
class Rva0052BAB2
{
public:
	int rva0052BAB2() const;
};

class LivingWorldRegionManager;

class LivingWorldRegionCampaign
{
public:
	void rva0020F3E8(LivingWorldRegionManager *regionManager);	// 0x0020F3E8
};

class LivingWorldRegionManager
{
public:
	void SelectCampaign(const StringBase<char> &campaignName);
	unsigned char m_pad00[8];
	LivingWorldRegionCampaign *m_activeCampaign;	// +0x08 (WB GetActiveCampaign)
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0xB0];
	LivingWorldRegionManager *m_regionManager;	// +0xB0
};

extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldRegionEffectsManager;
class LivingWorldManager
{
public:
	void rva00210F96();
	unsigned char opaque_00[0x268];
	LivingWorldRegionEffectsManager *m_regionEffects;
};

extern LivingWorldManager *TheLivingWorldManager;

extern GameLogic *TheGameLogic;

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
	bool rva003B8CAC();
	Rva00564DF2NameView *rva003B8D4D(const AsciiString &name);
	AsciiString rva003B8D06();
	void StartNewCampaign(const AsciiString &campaignName);
	void CallActSubroutine(const AsciiString &name);
	void StartNewCampaign(Int campaignIndex);			// 0x003B8C06
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);
	Rva0052BFE1 *rva003B8EDC(const AsciiString &name);

private:
	Int rva003B8E2B(const AsciiString &campaignName);		// 0x003B8E2B

	unsigned char m_pad00[0x10];
	Int m_campaignIndex;					// +0x10 (WB assert name)
	CampaignVectorView<Rva0052BFE1 *> m_campaignVector;	// +0x14
	unsigned char m_pad20[0x2C - 0x20];
	unsigned char m_2C;
	unsigned char m_2D;
};

// LivingWorldCampaignManager::StartNewCampaign, retail 0x003B8E6C.
void LivingWorldCampaignManager::StartNewCampaign(const AsciiString &campaignName)
{
	Int index = rva003B8E2B(campaignName);
	if (index != -1)
		StartNewCampaign(index);
}

// LivingWorldCampaignManager::StartNewCampaign(Int), retail 0x003B8C06 (166
// bytes): WB 0x01031960 names it (asserts at :214 and :229). An index in range
// becomes current; the region manager selects that campaign by name, and when
// one is active the living-world manager (0x00210F96) and the campaign
// (0x0020F3E8, given the region manager) take it up. WB's following
// DebugValidateRegionINIData is debug-only. After GameLogic's 0x0023D033, a
// set flag at GlobalData+0x86 or a non-empty +0x8C string copies the
// campaign's +0x4D byte to +0x2C and runs its 0x0052C9F9.
void LivingWorldCampaignManager::StartNewCampaign(Int campaignIndex)
{
	if (campaignIndex < 0 || (UnsignedInt)campaignIndex >= m_campaignVector.size())
		return;
	m_campaignIndex = campaignIndex;
	LivingWorldRegionManager *regionManager = TheLivingWorldLogic->m_regionManager;
	if (regionManager)
	{
		const Rva0052BAB2 *named = reinterpret_cast<const Rva0052BAB2 *>(m_campaignVector[m_campaignIndex]);
		regionManager->SelectCampaign(*reinterpret_cast<const StringBase<char> *>(named->rva0052BAB2()));
		if (regionManager->m_activeCampaign)
		{
			TheLivingWorldManager->rva00210F96();
			regionManager->m_activeCampaign->rva0020F3E8(regionManager);
		}
	}
	TheGameLogic->rva0023D033();
	if (TheWritableGlobalData->m_86 == 0
		&& reinterpret_cast<const StringBase<char> *>(&TheWritableGlobalData->m_8C)->isEmpty())
		return;
	m_2C = m_campaignVector[m_campaignIndex]->m_4D;
	m_campaignVector[m_campaignIndex]->rva0052C9F9();
}

// ?rva003B8CAC@LivingWorldCampaignManager@@QAE_NXZ, retail 0x003B8CAC (52 bytes).
bool LivingWorldCampaignManager::rva003B8CAC()
{
	if (TheWritableGlobalData->m_86 != 0)
	{
		if (m_campaignIndex >= 0 && (UnsignedInt)m_campaignIndex < m_campaignVector.size())
		{
			m_2D = 0;
			return m_campaignVector[m_campaignIndex]->rva0052C036();
		}
	}
	return false;
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

// Native Ghidra extent 0x003B8D4D..0x003B8D71, 36 bytes, RET 4.
// It shares the active-campaign guard with the name getter and tail-forwards
// the string key to 0x0052C7A2. That callee's compare(AsciiString) at +0x3B
// and RET 4 establish the key ABI; its record class/name remain unknown.
Rva00564DF2NameView *LivingWorldCampaignManager::rva003B8D4D(const AsciiString &name)
{
    if (m_campaignIndex >= 0 && (UnsignedInt)m_campaignIndex < m_campaignVector.size())
        return m_campaignVector[m_campaignIndex]->rva0052C7A2(name);
    return 0;
}


class LivingWorldRegionEffectsManager
{
public:
    void rva003EF2FF();
};
class Gen_003bcb40
{
public:
    void m(int);
};
class Glo012F1024Item
{
public:
    void bfmeEnter();
};
inline int addressForEmptyCallback(const AsciiString &name)
{
    return (int)&name;
}

// WB10323B0 names CallActSubroutine and asserts the named act at line428.
// Native calls the established 27-byte +4 getter, the shared RET4 callback,
// the complete entry dispatcher and manager+268 effects reset. The callback
// argument is one pointer-sized word; its original purpose remains unknown.
void LivingWorldCampaignManager::CallActSubroutine(const AsciiString &name)
{
    Rva00564DF2NameView *entry = rva003B8D4D(name);
    if (!entry)
        return;
    ((Gen_003bcb40 *)TheLivingWorldLogic)->m(addressForEmptyCallback(entry->rva00564DF2()));
    ((Glo012F1024Item *)entry)->bfmeEnter();
    TheLivingWorldManager->m_regionEffects->rva003EF2FF();
}
