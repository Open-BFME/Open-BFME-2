// cl: /O1 /EHsc /MD
// StrategicVeterancy.cpp -- StrategicVeterancy members at their WorldBuilder
// home (reverse/wb_name_leads.csv: WB's debug build names the file and each
// method); retail supplies the bytes.
//
// Layout (target evidence): the object holds its implementation at +0x00,
// which keeps the Apt level at +0x04, the display state at +0x08 (0 hidden,
// 1 shown, 2 fading in, 3-4 later states) and an enable word at +0x0C.

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
		void *m_vtbl;
		void *m_level;					// +0x04
		Int m_state;					// +0x08
		Int m_enabled;					// +0x0C
	};

	Impl *m_impl;						// +0x00

public:
	class Data
	{
	public:
		class AutoResolve;
	};
};

// StrategicVeterancy::Data::AutoResolve (0x1C bytes; ctor 0x005ECE81,
// WorldBuilder name, pinned; its three arguments are passed through
// untyped).
class StrategicVeterancy::Data::AutoResolve : public StrategicVeterancy::Data
{
public:
	AutoResolve(void *a, void *b, void *c);

private:
	char m_data[0x1C];
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
