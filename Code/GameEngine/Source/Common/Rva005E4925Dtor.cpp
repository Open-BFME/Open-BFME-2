// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva005E4AE2@@UAE@XZ @0x005E4925 112B. Destructor of the two-base object
// Rva005E4AE2Ctor.cpp constructs (data ledger: vtables 0x00877CEC and
// 0x00877CE0 belong to Rva005E4AE2). Called by the owning-pointer reset
// 0x005E4B9D under the pin ??1Rva005E4925. Target facts: when +0x2C is set the
// owner's +0x78 object (at +0x10) drops this object from its list through the
// rowed erase 0x002B7250; the holder at +0x14 drops the +4 listener base; the
// +0x1C tree unwinds (0x005E4670, spelled with the SBServer twin that owns
// the address) and both inline base destructors restore their vtables. The
// tree is spelled as a declaration-only specialisation so the call stays out
// of line; the ctor TU views the same bytes as map<int, void *>.
#include <map>
struct SBServer;
namespace _STL
{
template <> class _Rb_tree<int, pair<const int, SBServer>, _Select1st<pair<const int, SBServer> >, less<int>, allocator<pair<const int, SBServer> > >
{
public:
	~_Rb_tree();
private:
	char m_data[12];
};
}
typedef _STL::_Rb_tree<int, _STL::pair<const int, SBServer>, _STL::_Select1st<_STL::pair<const int, SBServer> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, SBServer> > > Rva005E4AE2Map;

class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct Rva005E4AE2Obj78
{
	char m_pad[4];
	Rva002B7250 m_holder;
};
struct Rva005E4AE2Owner
{
	char m_pad[0x78];
	Rva005E4AE2Obj78 *m_78;
};
struct Rva005E4AE2Listener
{
	Rva005E4AE2Listener() {}
	virtual ~Rva005E4AE2Listener() {}
};
class Rva005E4AE2Base
{
public:
	Rva005E4AE2Base() {}
	virtual ~Rva005E4AE2Base() {}
};
class Rva005E4AE2 : public Rva005E4AE2Base, public Rva005E4AE2Listener
{
public:
	virtual ~Rva005E4AE2();
private:
	void *m_08;
	int m_0C;
	Rva005E4AE2Owner *m_10;
	Rva002B7250 *m_14;
	int m_18;
	Rva005E4AE2Map m_1C;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};
Rva005E4AE2::~Rva005E4AE2()
{
	if (m_2C)
	{
		Rva005E4AE2Obj78 *owner = m_10->m_78;
		if (owner)
			owner->m_holder.rva002B7250((CreateAHeroData *)this);
	}
	m_14->rva002B7250((CreateAHeroData *)static_cast<Rva005E4AE2Listener *>(this));
}
