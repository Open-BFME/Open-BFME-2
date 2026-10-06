// cl: /DNDEBUG /MD /GX-
// ?Rva004C2918_ParseUpgradeMoneyAmount@INI@@SAXPAV1@PAX1PBX@Z (retail 0x004C2918, 61 bytes). Parses a
// science/amount pair through the rowed KillerScience parser at 0x003396D3
// into the first slot and the rowed parseInt at 0x0002EF56
// into the second slot (instance and userData are NULL for both), then
// pushes the pair through the rowed vector<BfmeE8>::push_back at 0x00539A2E
// onto the store. The element is spelled BfmeE8 so the push_back reference
// mangles to the rowed instantiation name (opaque-8B-pod precedent); its
// int members are the science index plus the money amount (CashHackUpgrades
// layout in CashHackSpecialPowerModuleDataCtor). Serves the UpgradeMoneyAmount
// entry of the table at 0x85C724 (sibling MoneyAmount). The callback name stays
// address-derived; shape follows INI_Rva004C381CParseUpgradeOCL (61B pair via
// rowed push_back).
struct BfmeE8
{
	int m_science;
	int m_amount;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class INI
{
public:
	static void Rva003396D3_ParseKillerScience(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C2918_ParseUpgradeMoneyAmount(INI *ini, void *instance, void *store, const void *userData);
};

void INI::Rva004C2918_ParseUpgradeMoneyAmount(INI *ini, void *instance, void *store, const void *userData)
{
	BfmeE8 entry;
	entry.m_science = -1;
	entry.m_amount = 0;
	INI::Rva003396D3_ParseKillerScience(ini, 0, &entry.m_science, 0);
	INI::parseInt(ini, 0, &entry.m_amount, 0);
	((_STL::vector<BfmeE8> *)store)->push_back(entry);
}
