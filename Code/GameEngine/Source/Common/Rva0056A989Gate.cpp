// cl: /MD
// RVA 0x0056A989: false only when the +0x38 count is negative and LivingWorldBattle::rva003F459A is nonzero.
class LivingWorldBattle
{
public:
	int rva003F459A();
};

class Rva0056A989
{
public:
	bool rva0056A989();
	char m_lead[0x38];
	int m_38;
};

bool Rva0056A989::rva0056A989()
{
	return m_38 >= 0 || ((LivingWorldBattle *)this)->rva003F459A() == 0;
}
