// cl: /O1 /DNDEBUG /MD /GX-
// Rva001FDD33_ParseResourceModifierValues (retail 0x001FDD33, 46 bytes).
// Reads a whitespace list where even the first token is optional: init and
// increment both go through the rowed getNextTokenOrNull at 0x002DEED
// (for-loop lowering with the entry jmp, DisabledSlots precedent), each
// token scanned through the rowed scanInt at 0x002ECCF into a stack temp
// pushed raw through the rowed vector<const ModuleData *>::push_back at
// 0x004DFCB0 (Percentage precedent for the element spelling). Serves the
// ResourceModifierValues entry of the table at 0x7E2070 (Faction table,
// sibling ResourceModifierObjectFilter). The callback name stays
// address-derived; the owning struct is BFME2-new (no BFME1 donor).

class ModuleData
{
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
	int scanInt(const char *token);
	const char *getNextTokenOrNull(const char *seps);
	static void Rva001FDD33_ParseResourceModifierValues(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva001FDD33_ParseResourceModifierValues@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva001FDD33_ParseResourceModifierValues(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token;
	for (token = ini->getNextTokenOrNull(0); token != 0; token = ini->getNextTokenOrNull(0)) {
		int value = ini->scanInt(token);
		((_STL::vector<const ModuleData *> *)store)->push_back((const ModuleData *&)value);
	}
}
