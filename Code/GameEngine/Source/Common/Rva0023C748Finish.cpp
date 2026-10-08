// ?rva0023C748@Rva0023C748@@QAEDXZ
// partial score=0.95 date=2026-09-30
// ?rva0023C748@Rva0023C748@@QAEDXZ
// partial score=0.95 date=2026-09-30
//
// ?rva0023C748@Rva0023C748@@QAEDXZ @0x0023C748, 97B.
// Predicate on this+0x110 mode 5/1/2 with selection-locked gate and 939 helper.
// Evidence: __thiscall ret no args returns al 1/0; callees rowed isSelectionLocked
// and NetWrapperCommandMsg::getData; helper state +0xE74 2/1/5 like sibling
// BfmeConv939Call939D; globals g_009FEF10 and g_bfme939Helper in use.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

class Rva002BA8F1Logic
{
public:
	char _pad[4];
};

class NetWrapperCommandMsg
{
public:
	unsigned char *getData();
};

struct Bfme939Helper
{
	char m_lead[0x1C];
	int m_value;
	char m_pad[0xE54];
	int m_state;
};

extern Bfme939Helper *g_bfme939Helper;

class Rva0023C748
{
public:
	char _pad[0x110];
	int m_mode;
	char rva0023C748();
};

char Rva0023C748::rva0023C748()
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) != 0 && ((BfmeSelectionState *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->isSelectionLocked())
		return 0;
	if (m_mode == 5)
		return 1;
	if (m_mode == 1)
		return 1;
	if (m_mode == 2)
		return 1;
	if (g_bfme939Helper != 0 && ((NetWrapperCommandMsg *)g_bfme939Helper)->getData() == (unsigned char *)1)
	{
		int state = g_bfme939Helper->m_state;
		if (state == 2)
			return 1;
		if (state != 1 && state != 5)
			return 0;
		return 1;
	}
	return 0;
}
