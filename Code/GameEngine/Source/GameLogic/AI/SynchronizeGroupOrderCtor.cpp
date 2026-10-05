// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0SynchronizeGroupOrder@@QAE@XZ @0x00546982 59B evidence: stores vtable 0x0086A314; base GroupOrder default rowed 0x005488C5; set<AsciiString> at +0x18 via rowed 0x000D3A71; bool at +0x24 false; caller 0x00355060.
// Honest-address ctor via vtable store (naming rule).
#include <set>

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL {
template <> struct less<AsciiString> {
	bool operator()(const AsciiString &left, const AsciiString &right) const {
		return left < right;
	}
};
}

class GroupOrder
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);
	virtual ~GroupOrder();
private:
	unsigned char m_pad04[0x18 - 4];
};

class SynchronizeGroupOrder : public GroupOrder
{
public:
	SynchronizeGroupOrder();
	SynchronizeGroupOrder(const SynchronizeGroupOrder &other);
	virtual ~SynchronizeGroupOrder();
	SynchronizeGroupOrder *rva005469FD();
private:
	_STL::set<AsciiString> m_18;
	bool m_24;
};

SynchronizeGroupOrder::SynchronizeGroupOrder()
	: GroupOrder()
	, m_18()
{
	m_24 = false;
}

SynchronizeGroupOrder::SynchronizeGroupOrder(const SynchronizeGroupOrder &other)
	: GroupOrder(other)
	, m_18()
{
	m_24 = false;
}

SynchronizeGroupOrder *SynchronizeGroupOrder::rva005469FD()
{
	return new SynchronizeGroupOrder(*this);
}
