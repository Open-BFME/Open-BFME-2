// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004080DD@CreateAHeroData@@QAE_NABVAsciiString@@PAI@Z @0x004080DD 44B. Identity: CreateAHeroData try-get via StringPayloadMap at +0x50; copies second.value at node+0x14 to out and returns true else false.
// Evidence: map50 at +0x50 in CreateAHeroDataDtor layout; callers 0x408109/0x40A99A pass key and out int and test al; callee _M_find rowed.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

struct TreeHintPayload001F8ACB
{
	unsigned int value;
};

typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> StringPayloadMap;

class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
};

enum NameKeyType;

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class CreateAHeroData : public Snapshot
{
public:
	bool rva004080DD(const AsciiString &key, unsigned int *out);
	unsigned int rva00408109(const NameKeyType *p);
private:
	unsigned char m_pad04[0x4C];
	StringPayloadMap m_map50;
};

bool CreateAHeroData::rva004080DD(const AsciiString &key, unsigned int *out)
{
	if (out == 0)
		return false;
	StringPayloadMap::iterator it = m_map50.find(key);
	if (it != m_map50.end())
	{
		*out = (*it).second.value;
		return true;
	}
	return false;
}

unsigned int CreateAHeroData::rva00408109(const NameKeyType *p)
{
	if (p == 0)
		return 0;
	AsciiString tmp = TheNameKeyGenerator->keyToName(*p);
	unsigned int out = 0;
	rva004080DD(tmp, &out);
	return out;
}
