// cl: /O1 /DNDEBUG /MD /GX-
// Rva004C381C_ParseUpgradeOCL (retail 0x004C381C, 61 bytes). Parses a
// science/OCL pair through the rowed KillerScience parser at 0x003396D3
// into the first slot and the rowed parseObjectCreationList at 0x00338A6F
// into the second slot (instance and userData are NULL for both), then
// pushes the pair through the rowed vector<BfmeE8>::push_back at 0x00539A2E
// onto the store. The element is spelled BfmeE8 so the push_back reference
// mangles to the rowed instantiation name (opaque-8B-pod precedent); its
// int members are the science index plus the OCL pointer (OCLUpgradePair
// layout in OCLSpecialPowerModuleDataCtor). Serves the UpgradeOCL entry of
// the table at 0x85CDC0 (sibling UpgradeName). The callback name stays
// address-derived; BFME1 donor is OCLSpecialPower.cpp parseOCLUpgradePair,
// which BFME2 extends with a (-1, NULL) pre-init and routes science through
// the KillerScience parser instead of INI::parseScience.

struct BfmeE8
{
	int m_science;
	int m_ocl;
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
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C381C_ParseUpgradeOCL(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva004C381C_ParseUpgradeOCL@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004C381C_ParseUpgradeOCL(INI *ini, void *instance, void *store, const void *userData)
{
	BfmeE8 entry;
	entry.m_science = -1;
	entry.m_ocl = 0;
	INI::Rva003396D3_ParseKillerScience(ini, 0, &entry.m_science, 0);
	INI::parseObjectCreationList(ini, 0, &entry.m_ocl, 0);
	((_STL::vector<BfmeE8> *)store)->push_back(entry);
}
