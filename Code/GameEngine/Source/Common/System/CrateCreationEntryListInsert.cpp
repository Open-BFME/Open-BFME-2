// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<crateCreationEntry>::insert calls the out-of-line create_node rowed at
// 0x0035CAB4 from the companion CrateCreationEntryList TU, mirroring
// stlport_list_asciistring_insert.cpp. Retail 0x0035CB8D (37 bytes) is the
// insert worker and 0x0035CBFE (26 bytes) is push_back; the node is 16 bytes
// (8 links plus 8-byte crate entry) and create delegates per element to the
// crate _Construct twin pin at 0x0035CA02.
#include <list>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);
bool operator<(const crateCreationEntry &a, const crateCreationEntry &b);

template class _STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >;
