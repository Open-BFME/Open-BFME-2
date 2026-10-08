// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x005990A0. The outlined "SpellNN" name parser that sits one
// slot above the three BfmeAptScreenSpellStore callbacks at 0x005990E0,
// 0x00599180 and 0x005991E0, each of which spells the same test inline.
// Nothing in the image calls this copy, so it keeps a descriptive free name.

class InGameUI;
extern InGameUI *TheInGameUI;
extern "C" __declspec(dllimport) int __cdecl atoi( const char * );
extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int );

// @?parseSpellIndex@@YAHPBD@Z 0x005990A0
static __declspec(noinline) int parseSpellIndex( const char *name )
{
	if( strncmp( name, "Spell", 5 ) != 0 )
		return -1;
	return atoi( name + 5 ) - 1;
}

int parseSpellIndexCall( const char *name )
{
	return parseSpellIndex( name );
}

// BFME2's spell store screen callbacks around the parser (0x0043C78A ..
// 0x0043D5F5), bound by name ("AptSpellStore::OnInitialized" ...) by the
// screen's registration 0x0043D686; the static parser above is what lets
// them pass the name in EAX. The view below covers only the fields they
// touch. The rowed OnBttnClose 0x0043C7C9 and OnBttnReset 0x0043D3DA view
// the same screen as Rva0043D3DA.
enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ModuleData;

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void push_back(const T &value);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// The +0x288 member (Rva0043D3DAClear.cpp's Rva0043D3A8): vslot 0 tells
// whether a science is already chosen; the rowed 0x0043D5CB adds one.
class Rva0043D3A8
{
public:
	virtual bool v00(ScienceType science);
	void rva0043D5CB(ScienceType science);
};

class ScienceStore
{
public:
	// Unrowed 0x001FF4D3 (58 bytes; ret 8): the prerequisites check
	// 0x001FF47D, then the holder's vslot 1 points against
	// getSciencePurchaseCost; pinned by address.
	bool rva001FF4D3(Rva0043D3A8 *holder, ScienceType science) const;
};

extern ScienceStore *TheScienceStore;

extern int g_Va009FE78C;

extern "C" char *__cdecl _mbscpy(char *dest, const char *src);

// Rva0050E9D3Enable.cpp's 0x0043C96F.
void Rva0043C96FEnable(void);

// A spell button's entry: its science list at +0xA4.
struct SpellStoreEntry
{
	unsigned char m_pad[0xA4];
	ScienceType *m_sciences; // +0xA4
};

struct SpellStoreSlot
{
	const ModuleData *m_entry;
	int m_04;
};

class AptSpellStore
{
public:
	void OnInitialized(const char *unused);
	void OnRollOverBttnSpell(const char *name);
	void OnRollOutBttnSpell(const char *name);
	void InputEnabled(int query, char *result, bool skip);
	void OnClosed(const char *unused);
	void OnBttnSpell(const char *name);

private:
	unsigned char m_pad000[0x27C];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_chosen; // +0x27C
	Rva0043D3A8 m_sciences; // +0x288
	unsigned char m_pad28c[0x2A0 - 0x28C];
	bool m_2a0; // +0x2A0
	bool m_2a1;
	bool m_2a2; // +0x2A2
	int m_2a4; // +0x2A4
	SpellStoreSlot m_slots[20]; // +0x2A8
	int m_348; // +0x348
	int m_34c; // +0x34C
	int m_350; // +0x350
	int m_hovered; // +0x354
	bool m_358; // +0x358
	bool m_359; // +0x359
};

// Retail 0x0043C78A, 63 bytes: "AptSpellStore::OnInitialized".
void AptSpellStore::OnInitialized(const char *unused)
{
	m_2a2 = false;
	m_348 = -1;
	m_34c = -1;
	m_350 = -1;
	m_hovered = -1;
	m_358 = false;
	m_359 = false;
	m_2a4 = 0;
	m_2a0 = true;
}

// Retail 0x0043C85D, 38 bytes: "AptSpellStore::OnRollOverBttnSpell".
void AptSpellStore::OnRollOverBttnSpell(const char *name)
{
	int index = parseSpellIndex(name);
	if (index >= 0 && index < 20)
	{
		m_hovered = index;
		m_359 = false;
	}
}

// Retail 0x0043C883, 32 bytes: "AptSpellStore::OnRollOutBttnSpell".
void AptSpellStore::OnRollOutBttnSpell(const char *name)
{
	int index = parseSpellIndex(name);
	if (index >= 0 && index < 20)
		m_hovered = -1;
}

// Retail 0x0043C8A3, 65 bytes: "AptSpellStore::InputEnabled", an Apt
// query callback like AptMpGameSetup's 0x00442F65.
void AptSpellStore::InputEnabled(int query, char *result, bool skip)
{
	if (query == 0 && !skip)
		_mbscpy(result, *(int *)(g_Va009FE78C + 0x110) == 6 || *(unsigned char *)((reinterpret_cast<int>(TheInGameUI)) + 0x16) ? "1" : "0");
}

// Retail 0x0043C9E5, 24 bytes: "AptSpellStore::OnClosed".
void AptSpellStore::OnClosed(const char *unused)
{
	if (m_2a2)
	{
		Rva0043C96FEnable();
		m_2a2 = false;
	}
}

// Retail 0x0043D5F5, 145 bytes: "AptSpellStore::OnBttnSpell". Under the
// same gate as OnBttnReset, a valid "SpellNN" button whose entry's first
// science is not chosen yet and is purchasable gets recorded and added.
void AptSpellStore::OnBttnSpell(const char *name)
{
	if (*(int *)(g_Va009FE78C + 0x110) == 6)
	{
		if (*(unsigned char *)((reinterpret_cast<int>(TheInGameUI)) + 0x16) == 0)
			return;
	}
	int index = parseSpellIndex(name);
	if (index < 0 || index >= 20)
		return;
	if (m_2a2)
		return;
	const ModuleData *entry = m_slots[index].m_entry;
	if (!entry)
		return;
	ScienceType science = *((const SpellStoreEntry *)entry)->m_sciences;
	if (!m_sciences.v00(science) && TheScienceStore->rva001FF4D3(&m_sciences, science))
	{
		m_chosen.push_back(entry);
		m_sciences.rva0043D5CB(science);
	}
}

// ?g_Va009FE78C@@3HA: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE78C@@3HA=?TheGameLogic@@3PAVGameLogic@@A")
