// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Target predicate boundary 0x002AA04C-0x002AA08E; called by the native
// Player radar-removal notification at 0x002AA9C2. Target supplies the
// slot-0x40 boolean query and the +0x734 / +0x8C5 / +0x70 / +0x40 tests.
// Each global uses its existing ledger-backed definition; local classes
// describe only the native access surface. Original predicate and field
// names remain unasserted. The banked near miss is repaired by returning
// the conjunction directly, which preserves the early ECX zeroing.
class Rva002AA04C
{
public:
	int rva002AA04C();
private:
	char m_pad0[0x734];
	unsigned char m_734;
};

class Rva002AA04CCheckArg;
class Rva002AA04CUnknown
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual bool check(Rva002AA04C *p);
};
struct UnknownE03138;
extern UnknownE03138 *g_00E03138;

struct Rva002AA04CInGameUI
{
	char m_pad0[0x8c5];
	unsigned char m_8c5;
};
class InGameUI;
extern InGameUI *TheInGameUI;

struct Rva002AA04CGameLogic
{
	char m_pad0[0x40];
	unsigned int m_40;
	char m_pad1[0x70 - 0x44];
	unsigned char m_70;
};
class GameLogic;
extern GameLogic *TheGameLogic;

int Rva002AA04C::rva002AA04C()
{
	return (!reinterpret_cast<Rva002AA04CUnknown *>(g_00E03138)->check(this)
		&& m_734 == 0
		&& reinterpret_cast<Rva002AA04CInGameUI *>(TheInGameUI)->m_8c5 == 0
		&& reinterpret_cast<Rva002AA04CGameLogic *>(TheGameLogic)->m_70 != 0
		&& reinterpret_cast<Rva002AA04CGameLogic *>(TheGameLogic)->m_40 > 0);
}
