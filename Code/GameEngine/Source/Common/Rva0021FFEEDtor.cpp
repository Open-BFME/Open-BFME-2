// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0021FFEE..00220105 (279B), vtable BE648C slot0's complete dtor.
// Target offsets and EH states establish the member destruction order below.
// CreateAHeroData's independently rowed provider establishes its 140B extent;
// container spellings follow the existing verified destructor providers.
// Lead: Rva0038454E's many-member destructor in Rva003844D7Dtor.cpp.
#include <vector>
#include <map>
#include "ascii_string.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	AsciiString m_name;
};

class CreateAHeroData
{
public:
	virtual ~CreateAHeroData();
private:
	char m_storage04[0x13c];
};

class Rva0021F876;
template <> _STL::vector<Rva0021F876>::~vector();

struct Rva0021DA18
{
	~Rva0021DA18();
	char m_storage[12];
};
struct Rva0021DA57
{
	~Rva0021DA57();
	char m_storage[12];
};

// Retain the existing provider's opaque value spelling. This parent observes
// the tree header and cleanup ABI, and supplies no new claim about its payload.
struct Rva0040A603Record { char bytes[1]; };
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva0040A603Record>,
	_STL::_Select1st<_STL::pair<const int, Rva0040A603Record> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Rva0040A603Record> > > CleanupTree;
template <> CleanupTree::~_Rb_tree();
template <> void CleanupTree::clear();

class Rva0021FFEE : public SubsystemInterface
{
public:
	virtual ~Rva0021FFEE();
private:
	CreateAHeroData m_hero0C;
	_STL::vector<Rva0021F876> m_vector14C;
	int m_158;
	Rva0021DA18 m_vector15C;
	Rva0021DA57 m_vector168;
	CleanupTree m_tree174;
	char m_pad180[8];
	AsciiString m_text188, m_text18C, m_text190;
	char m_pad194[0x30];
	AsciiString m_text1C4, m_text1C8, m_text1CC;
	char m_pad1D0[0xC];
	AsciiString m_text1DC;
	int m_state1E0;
	int m_1E4;
	AsciiString m_text1E8, m_text1EC;
};

Rva0021FFEE::~Rva0021FFEE()
{
	m_state1E0 = 0;
	m_tree174.clear();
}
