// cl: /O1 /EHsc /MD
// StrategicVeterancy.cpp -- StrategicVeterancy members at their WorldBuilder
// home (reverse/wb_name_leads.csv: WB's debug build names the file and each
// method); retail supplies the bytes.
//
// Layout (target evidence): the object holds its implementation at +0x00,
// which keeps the Apt level at +0x04, the display state at +0x08 (0 hidden,
// 1 shown, 2 fading in, 3-4 later states) and an enable word at +0x0C.

typedef int Int;
typedef bool Bool;

// The Apt player (VA 0x00DFE4CC, address-named in the ledger): WB names its
// slot callees AptPlayer::ShowLevel (rowed 0x002224FE) and HideLevel
// (pinned 0x0022277D); 0x00516F21 sends an Apt movie a state message.
class Rva00222A8BTarget
{
public:
	// Native provider compares the incoming 32-bit index with 14 and returns AL.
	bool rva0022277D(int index);			// 0x0022277D, WB AptPlayer::HideLevel
};

class Rva002224FE
{
public:
	Bool rva002224FE(Int level);			// 0x002224FE, WB AptPlayer::ShowLevel
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
void Rva00516F21Invoke(Rva00222A8BTarget *player, void *level, const char *message, const char *arg);	// 0x00516F21

// TheLivingWorldLogic (VA 0x00DFEF10) and its rowed check 0x002B254F.
class Rva002B254F
{
public:
	Int rva002B254F();					// 0x002B254F
};

extern Rva002B254F *g_00DFEF10;

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
};

// StrategicVeterancy::Hide, retail 0x005EC21D (33 bytes): a displayed level
// is hidden and the state cleared.
void StrategicVeterancy::Hide()
{
	if (m_impl->m_state != 0)
	{
		TheRva00222A8BTarget->rva0022277D(reinterpret_cast<int>(m_impl->m_level));
		m_impl->m_state = 0;
	}
}
