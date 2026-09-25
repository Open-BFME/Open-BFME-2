// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// List-valued string-map insertion support for GameSpyLoginPreferences'
// nick and clan maps (+0x2c/+0x38). Retail's list-map operator[] 0x5CAC49
// builds a temporary pair from the key and a default list through the
// pair two-value constructor 0x5C9F08 below, then hint-inserts it. The
// pair holds the AsciiString key at +0x00 (copied through the pinned copy
// at 0x365F0) and the list value at +0x04 (copied through the landed list
// copy at 0x54D800). The key destructor stays declared-only so the pair
// keeps retail's out-of-line key-teardown call.
#include <map>
#include <list>
#include <new>

template <typename T> class StringBase
{
	void releaseBuffer();

public:
	~StringBase();

protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
};

bool operator<(const AsciiString &left, const AsciiString &right);

typedef _STL::list<AsciiString> AsciiStringList;
typedef _STL::pair<const AsciiString, AsciiStringList> ListPair;

// Anchor: emits the pair two-value constructor COMDAT (retail 0x005C9F08)
// via placement new; the anchor itself never shipped.
void listPairTwoValueAnchor(ListPair *at, const AsciiString &key, const AsciiStringList &value)
{
	new (at) ListPair(key, value);
}
