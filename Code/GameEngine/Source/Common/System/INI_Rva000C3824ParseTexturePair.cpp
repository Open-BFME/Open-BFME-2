// cl: /O1 /DNDEBUG /MD /EHsc
// Rva000C3824_ParseTexturePair (retail 0x000C3824, 98 bytes). Reads two
// consecutive strings through the rowed parseAsciiString at 0x002F11E into
// the halves of a local 8-byte BfmeStringRecord000B94D2 (two AsciiStrings,
// inline zero-init), pushes the record through the rowed
// vector<BfmeStringRecord000B94D2>::push_back at 0x000C333B, then tears the
// record down through its dtor (pinned with its true struct name at
// 0x000B6CF1). Serves the Texture table entry. The record model mirrors the
// vector-allocate TU; the callback name stays address-derived.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

struct BfmeStringRecord000B94D2
{
	AsciiString text0;
	AsciiString text1;
	~BfmeStringRecord000B94D2();
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
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3824_ParseTexturePair(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva000C3824_ParseTexturePair@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva000C3824_ParseTexturePair(INI *ini, void *instance, void *store, const void *userData)
{
	BfmeStringRecord000B94D2 record;
	INI::parseAsciiString(ini, instance, &record.text0, userData);
	INI::parseAsciiString(ini, instance, &record.text1, userData);
	((_STL::vector<BfmeStringRecord000B94D2> *)store)->push_back(record);
}
