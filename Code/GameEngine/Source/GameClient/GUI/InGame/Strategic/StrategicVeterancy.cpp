// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// StrategicVeterancy.cpp -- StrategicVeterancy members at their WorldBuilder
// home (reverse/wb_name_leads.csv: WB's debug build names the file and each
// method); retail supplies the bytes.
//
// Layout (target evidence): the object holds its implementation at +0x00,
// which keeps the Apt level at +0x04, the display state at +0x08 (0 hidden,
// 1 shown, 2 fading in, 3-4 later states) and an enable word at +0x0C.

#include "ascii_string.h"
#include "unicode_string.h"
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *, unsigned int, const char *, ...);

class Image;
class Rva00524306
{
public:
	void rva00524725(const AsciiString &key, const Image *image);
private:
	char m_names[12];
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
typedef int Int;
typedef bool Bool;

// The Apt player (VA 0x00DFE4CC, address-named in the ledger): WB names its
// slot callees AptPlayer::ShowLevel (rowed 0x002224FE) and HideLevel
// (pinned 0x0022277D); 0x00516F21 sends an Apt movie a state message.
class Rva00222A8BTarget
{
public:
	bool rva0022277D(int level);	// 0x0022277D, WB AptPlayer::HideLevel
};

class Rva002224FE
{
public:
	Bool rva002224FE(Int level);			// 0x002224FE, WB AptPlayer::ShowLevel
};

class Rva00222A8BTarget; extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void Rva00516F21Invoke(Rva00222A8BTarget *player, void *level, const char *message, const char *arg);	// 0x00516F21

// TheLivingWorldLogic (VA 0x00DFEF10) and its rowed check 0x002B254F.
class Rva002B254F
{
public:
	Int rva002B254F();					// 0x002B254F
};

class StrategicVeterancy
{
public:
	Bool Show();						// 0x005EC1A4, banked near miss
	void Hide();

private:
	struct Impl
	{
		void *m_owner;
		void *m_level;					// +0x04
		Int m_state;					// +0x08
		Int m_numRows;					// +0x0C
		void OnFadeOut(const char *path);
		void OnContinue(const char *path);
		void ExternFunc(int index, char *buffer, bool lvalue);
		void OnInitialized(const char *path);
	};

	Impl *m_impl;						// +0x00

public:
	class Data
	{
	public:
		class AutoResolve;
		void rva005EC296(); // Original name unknown: populates the six labels per row.
	private:
		struct Row
		{
			UnicodeString name;
			int level, battles, killsInBattle, killsInWar;
			const Image *image;
		};
		void *m_vtbl;
		Row *m_begin, *m_end, *m_capacity;
		Rva00524306 m_images;
	};
};

// StrategicVeterancy::Data::AutoResolve (0x1C bytes; ctor 0x005ECE81,
// WorldBuilder name, pinned; its three arguments are passed through
// untyped).
class StrategicVeterancy::Data::AutoResolve : public StrategicVeterancy::Data
{
public:
	AutoResolve(void *a, void *b, void *c);

};

StrategicVeterancy::Data *__cdecl Rva005ED15DCreateAutoResolve(void *a, void *b, void *c);

// StrategicVeterancy::Hide, retail 0x005EC21D (33 bytes): a displayed level
// is hidden and the state cleared.
void StrategicVeterancy::Hide()
{
	if (m_impl->m_state != 0)
	{
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva0022277D((int)m_impl->m_level);
		m_impl->m_state = 0;
	}
}

// Retail 0x005ED15D (59 bytes, cdecl; unnamed in WorldBuilder): builds the
// auto-resolve veterancy data StrategicInGameUI::BattleResolver keeps.
StrategicVeterancy::Data *__cdecl Rva005ED15DCreateAutoResolve(void *a, void *b, void *c)
{
	return new StrategicVeterancy::Data::AutoResolve(a, b, c);
}

// Native 0x005EC296..0x005EC422; WB 0x015EB200 independently confirms
// the six binding strings and each 24-byte row field. Layout names describe
// those accesses; the original method and row type names are unknown.
void StrategicVeterancy::Data::rva005EC296()
{
	AsciiString key;
	UnicodeString number;
	int index = 0;
	for (Row *row = m_begin; row != m_end; ++row)
	{
		key.format("StrategicVeterancy:UnitName_%d", index);
		g_bfmeAptWindowManager->bfmeSetText(key, row->name, false);
		key.format("StrategicVeterancy:UnitLevel_%d", index);
		number.format((const unsigned short *)L"%d", row->level);
		g_bfmeAptWindowManager->bfmeSetText(key, number, false);
		key.format("StrategicVeterancy:UnitBattles_%d", index);
		number.format((const unsigned short *)L"%d", row->battles);
		g_bfmeAptWindowManager->bfmeSetText(key, number, false);
		key.format("StrategicVeterancy:UnitKillsInBattle_%d", index);
		number.format((const unsigned short *)L"%d", row->killsInBattle);
		g_bfmeAptWindowManager->bfmeSetText(key, number, false);
		key.format("StrategicVeterancy:UnitKillsInWar_%d", index);
		number.format((const unsigned short *)L"%d", row->killsInWar);
		g_bfmeAptWindowManager->bfmeSetText(key, number, false);
		key.format("StrategicVeterancy:UnitImage_%d", index);
		m_images.rva00524725(key, row->image);
		++index;
	}
}

// Constructor 5EC64E binds this exact member to
// AptStrategicVeterancy::OnFadeOut; WB15EA030 confirms the state store.
void StrategicVeterancy::Impl::OnFadeOut(const char *path)
{
	m_state = 4;
}

// Constructor 5EC64E binds this to AptStrategicVeterancy::OnContinue;
// WB15EA050 confirms state8=5 and the one-argument member ABI.
void StrategicVeterancy::Impl::OnContinue(const char *path)
{
	m_state = 5;
}

// Native5EC10A..5EC135, RET12. Constructor binding and WB15EA070
// name this ExternFunc, serving StrategicVeterancy::NumRows.
void StrategicVeterancy::Impl::ExternFunc(int index, char *buffer, bool lvalue)
{
	if (index == 0 && !lvalue)
		_snprintf(buffer, 255, "%d", m_numRows);
}

// WB15E9FA0 names this member and confirms the guarded 1->2 transition.
// Constructor5EC64E binds it at the exact 42D493 ICF owner body.
void StrategicVeterancy::Impl::OnInitialized(const char *path)
{
	if (m_state == 1)
		m_state = 2;
}
