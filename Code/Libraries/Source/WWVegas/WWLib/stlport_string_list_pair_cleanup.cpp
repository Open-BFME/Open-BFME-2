// cl: /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// List-valued string-map cleanup for GameSpyLoginPreferences' nick and
// clan maps (+0x2c/+0x38). Instantiating the list-pair _Rb_tree destructor
// emits the whole teardown chain with the same 56/41/53/53-byte EH shapes
// as the string-pair chain in stlport_string_pair_cleanup.cpp: the tree
// dtor 0x5CA918, its clear 0x5CA780, the node erase 0x5CA25C and the pair
// dtor 0x5C9ED3. The pair destroys the list value at +4 (the landed list
// teardown at 0x2FECBC) then the AsciiString key (the pinned teardown at
// 0x36410), and node release folds to the GameMemory free. The key
// destructor stays declared-only so the pair keeps retail's out-of-line
// key-teardown call.
#include <map>
#include <list>

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
typedef _STL::_Rb_tree<AsciiString, ListPair, _STL::_Select1st<ListPair>, _STL::less<AsciiString>, _STL::allocator<ListPair> > ListPairTree;
template ListPairTree::~_Rb_tree();
