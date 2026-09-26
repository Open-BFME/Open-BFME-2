// cl: /O1 /DNDEBUG /MD /GX-
// Rva004B60D5_ParsePercentage (retail 0x004B60D5, 37 bytes). Parses a
// fraction through the rowed parsePercentToReal at 0x002F1BA into a stack
// temp (instance forwarded, store and userData 0), then pushes the raw 4
// bytes through the rowed vector<const ModuleData *>::push_back at
// 0x004DFCB0 onto the store (spelled through the ledger's element type so
// the reference mangles to the rowed instantiation name; the rowed float
// push_back at 0x0054E89C is a different 51-byte body). Serves the
// Percentage entry of the table at 0x858460. The callback name stays
// address-derived; the owning class is BFME2-new (no BFME1 donor).

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
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004B60D5_ParsePercentage(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva004B60D5_ParsePercentage@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004B60D5_ParsePercentage(INI *ini, void *instance, void *store, const void *userData)
{
	float percent;
	INI::parsePercentToReal(ini, 0, &percent, 0);
	((_STL::vector<const ModuleData *> *)store)->push_back((const ModuleData *&)percent);
}
