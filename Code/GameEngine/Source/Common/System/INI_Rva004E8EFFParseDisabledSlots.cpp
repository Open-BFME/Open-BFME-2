// cl: /O1 /DNDEBUG /MD /GX-
// Rva004E8EFF_ParseDisabledSlots (retail 0x004E8EFF, 56 bytes). Reads a
// whitespace list: first token through the rowed getNextToken at 0x002DF97,
// each token scanned through the rowed scanInt at 0x002ECCF into a stack
// temp pushed raw through the rowed vector<const ModuleData *>::push_back
// at 0x004DFCB0 (Percentage precedent for the element spelling), continuing
// through the rowed getNextTokenOrNull at 0x002DEED while non-null
// (do-while, retail's single jne). Serves the
// AnyTypeTemplateDisabledSlots entry of the table at 0x7FDA50. The callback
// name stays address-derived; the owning struct is BFME2-new (no BFME1 donor).

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
	const char *getNextToken(const char *seps);
	int scanInt(const char *token);
	const char *getNextTokenOrNull(const char *seps);
	static void Rva004E8EFF_ParseDisabledSlots(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva004E8EFF_ParseDisabledSlots@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004E8EFF_ParseDisabledSlots(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token;
	for (token = ini->getNextToken(0); token != 0; token = ini->getNextTokenOrNull(0)) {
		int slot = ini->scanInt(token);
		((_STL::vector<const ModuleData *> *)store)->push_back((const ModuleData *&)slot);
	}
}
