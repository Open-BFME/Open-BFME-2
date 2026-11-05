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

// A campaign in the +0x14 vector: its spawn-army lookup (0x0052BFE1, unnamed
// in WB, unrowed) scans 0xB8-byte entries and returns the match or NULL.
// Address-only view of the receiver returned by the native active-entry lookup.
// Its 27-byte folded getter copies the +4 AsciiString through the hidden result.
// Neither the record class nor the getter's original identity is established.
class Rva00564DF2NameView { public: AsciiString rva00564DF2() const; };

#include "../../../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;

template<class T> class StringBase;
struct Rva005657FEElement;
struct Rva005657FEHolder;

class Rva0052C036
{
public:
	bool rva0052C036();
	bool rva0052C9F9();
};

class Rva0052BFE1 : public Rva0052C036
{
public:
	Rva00564DF2NameView *getCurrentEntry();
    Rva00564DF2NameView *rva0052C7A2(const AsciiString &name);
	Rva005657FEElement *rva0052BFE1(const StringBase<char> &key, const Rva005657FEHolder *holder);	// 0x0052BFE1
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

// The campaign's regions (+0x2C vector of region pointers): each region's id
// at +0x12C and, at +0x198, the object whose +0x10 point the region manager
// fills (0x0020F27E, WB GetRegionCenterPoint).
struct Rva0020F3E8Point { int x, y; };
struct Rva0020F3E8Marker
{
	unsigned char m_pad00[0x10];
	Rva0020F3E8Point m_point;		// +0x10
};
struct Rva0020F3E8Region
{
	unsigned char m_pad000[0x12c];
	int m_id;						// +0x12C
	unsigned char m_pad130[0x198 - 0x130];
	Rva0020F3E8Marker *m_marker;	// +0x198
};
#include "../../../Common/RegionCenterPointDispatchView.h"	// 0x0020F27E, WB GetRegionCenterPoint
template<class T> struct Rva0020F3E8Vector
{
	T *begin;
	T *end;
	T *capacity;
	unsigned size() const { return (unsigned)(end - begin); }
	T &operator[](unsigned i) { return begin[i]; }
};

class LivingWorldRegionCampaign
{
public:
	void rva0020F3E8(LivingWorldRegionManager *regionManager);	// 0x0020F3E8

	unsigned char m_pad00[0x2c];
	Rva0020F3E8Vector<Rva0020F3E8Region *> m_regions;	// +0x2C
};

class LivingWorldRegionManager
{
public:
	void SelectCampaign(const StringBase<char> &campaignName);
	unsigned char m_pad00[8];
	LivingWorldRegionCampaign *m_activeCampaign;	// +0x08 (WB GetActiveCampaign)
};

#include "../../../../Include/GameLogic/LivingWorldLogic.h"

extern LivingWorldLogic *TheLivingWorldLogic;

#include "../../../../Include/GameLogic/LivingWorldManager.h"

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

#include "../../../../Include/Common/LivingWorldCampaignManager.h"

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
	if (campaignIndex < 0 || (UnsignedInt)campaignIndex >= (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size())
		return;
	field10 = campaignIndex;
	LivingWorldRegionManager *regionManager = TheLivingWorldLogic->fieldB0;
	if (regionManager)
	{
		const Rva0052BAB2 *named = reinterpret_cast<const Rva0052BAB2 *>((*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10]);
		regionManager->SelectCampaign(*reinterpret_cast<const StringBase<char> *>(named->rva0052BAB2()));
		if (regionManager->m_activeCampaign)
		{
			TheLivingWorldManager->rva00210F96();
			regionManager->m_activeCampaign->rva0020F3E8(regionManager);
		}
	}
	TheGameLogic->rva0023D033();
	if (TheWritableGlobalData->m_liveCampaignMode == 0
		&& reinterpret_cast<const StringBase<char> *>(&TheWritableGlobalData->m_livingWorldCampaignOverrride)->isEmpty())
		return;
	field2C = (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10]->m_4D;
	(*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10]->rva0052C9F9();
}

// ?rva003B8CAC@LivingWorldCampaignManager@@QAE_NXZ, retail 0x003B8CAC (52 bytes).
bool LivingWorldCampaignManager::rva003B8CAC()
{
	if (TheWritableGlobalData->m_liveCampaignMode != 0)
	{
		if (field10 >= 0 && (UnsignedInt)field10 < (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size())
		{
			field2D = 0;
			return (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10]->rva0052C036();
		}
	}
	return false;
}

// LivingWorldCampaignManager::UseGenericSpawnArmyForPlayer, retail 0x003B8CE0
// (38 bytes): WB names it (assert at LivingWorldCampaignManager.cpp:318, "no
// active campaign"); the active campaign answers, NULL without one.
void *LivingWorldCampaignManager::UseGenericSpawnArmyForPlayer(Int playerName, Int player)
{
	if (field10 >= 0 && (UnsignedInt)field10 < (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size())
	{
		Rva0052BFE1 *campaign = (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10];
		return campaign->rva0052BFE1(*(const StringBase<char> *)playerName, (const Rva005657FEHolder *)player);
	}
	return 0;
}

// ?rva003B8EDC@LivingWorldCampaignManager@@QAEPAVRva0052BFE1@@ABVAsciiString@@@Z
// Native Ghidra extent 0x003B8EDC..0x003B8F20; RET 4. It walks the
// existing campaign pointer vector and calls the verified string compare
// worker at 0x000069D6 on each entry's +4 member. The method name is unknown.
Rva0052BFE1 *LivingWorldCampaignManager::rva003B8EDC(const AsciiString &name)
{
	for (UnsignedInt i = 0; i < (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size(); ++i)
	{
		if ((*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[i]->m_name04.compare(name) == 0)
			return (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[i];
	}
	return 0;
}

// ?rva003B8E2B@LivingWorldCampaignManager@@AAEHABVAsciiString@@@Z
// Native Ghidra extent 0x003B8E2B..0x003B8E6C; RET 4. The same scan as
// 0x003B8EDC returns the matched index instead, or -1 for an unknown name.
Int LivingWorldCampaignManager::rva003B8E2B(const AsciiString &campaignName)
{
	for (UnsignedInt i = 0; i < (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size(); ++i)
	{
		if ((*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[i]->m_name04.compare(campaignName) == 0)
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
	AsciiString m_name;
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
		if (m_records[i].m_name.compare(*(const AsciiString *)key) == 0)
			return &m_records[i];
	}
	return 0;
}

// Native Ghidra extent 0x003B8D06..0x003B8D4D, 71 bytes, RET 4 hidden result.
// The existing index/vector layout gates access to the active campaign. Calls
// at 0x003B8D28 and 0x003B8D32 prove the no-argument entry lookup and AsciiString
// return ABI; invalid indices return the named AsciiString::TheEmptyString.
// Separate entry and return expressions preserve the native call ordering.
AsciiString LivingWorldCampaignManager::GetCurrentActName()
{
    if (field10 >= 0 && (UnsignedInt)field10 < (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size())
        {
        Rva00564DF2NameView *entry = (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10]->getCurrentEntry();
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
    if (field10 >= 0 && (UnsignedInt)field10 < (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14)).size())
        return (*reinterpret_cast<CampaignVectorView<Rva0052BFE1 *> *>(&field14))[field10]->rva0052C7A2(name);
    return 0;
}


class LivingWorldRegionEffectsManager
{
public:
    void rva003EF2FF();
};
class Glo012F1024Item
{
public:
    void bfmeEnter();
};
// WB10323B0 names CallActSubroutine and asserts the named act at line428.
// Native calls the established 27-byte +4 getter, the shared RET4 callback,
// the complete entry dispatcher and manager+268 effects reset. The callback
// argument is the getter's AsciiString temporary, passed by reference (WB's
// debug callee 0x00D834C0 formats it into "Calling Act Subroutine'%s'").
void LivingWorldCampaignManager::CallActSubroutine(const AsciiString &name)
{
    Rva00564DF2NameView *entry = rva003B8D4D(name);
    if (!entry)
        return;
    TheLivingWorldLogic->rva0047A69C(entry->rva00564DF2());
    ((Glo012F1024Item *)entry)->bfmeEnter();
    TheLivingWorldManager->field268->rva003EF2FF();
}

// Retail 0x0020F3E8, 90 bytes (RET 4; callers StartNewCampaign and
// 0x003B8DD7): asks the region manager for each campaign region's point by
// the region's id and stores it in the region's +0x198 marker.
void LivingWorldRegionCampaign::rva0020F3E8(LivingWorldRegionManager *regionManager)
{
	for (unsigned i = 0; i < m_regions.size(); ++i)
	{
		Rva0020F3E8Point point;
		((Rva0020F27EHost *)regionManager)->rva0020F27E(m_regions[i]->m_id, (int)&point);
		m_regions[i]->m_marker->m_point = point;
	}
}
