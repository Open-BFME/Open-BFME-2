// cl: /O1 /DNDEBUG /MD /EHsc
// Rva004C3859_ParseUpgradeName (retail 0x004C3859, 63 bytes). Reads one
// AsciiString through the rowed getNextAsciiString at 0x002EA4F by value
// (hidden-pointer construction into a stack temp, no zero-init store),
// pushes it through the pinned vector<AsciiString>::push_back at 0x002DBE6
// onto the store, then tears the temp down through the pinned teardown at
// 0x00036410. Serves the UpgradeName entry of the table at 0x85CDC0
// (sibling UpgradeOCL). The callback name stays address-derived; the owning
// struct is BFME2-new (no BFME1 donor).

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
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
	AsciiString getNextAsciiString();
	static void Rva004C3859_ParseUpgradeName(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva004C3859_ParseUpgradeName@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004C3859_ParseUpgradeName(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString name = ini->getNextAsciiString();
	((_STL::vector<AsciiString> *)store)->push_back(name);
}
