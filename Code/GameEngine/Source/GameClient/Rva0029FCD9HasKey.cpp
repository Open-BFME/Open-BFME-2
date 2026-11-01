// cl: /O1 /arch:SSE /G7 /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0029FCD9@InGameUI@@QAE_NPBD@Z @0x0029FCD9 66B: whether the name is a known key of the
// name-key hash table at +0x874 (the lookup the radius-cursor INI parser 0x0035AED4 calls
// through): empty names are unknown; otherwise the name is turned into a key and looked
// up through the shared int-keyed hash lookup (ICF 0x002888D4). Layout views are neutral.
#include <hash_map>

// The hash table's bucket-vector begin()/size() const copies here differed
// from retail's; declared imported and force-inlined they are not emitted.
namespace _STL {
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}

enum NameKeyType { NAMEKEY_INVALID = 0 };
#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
typedef std::hash_map<int, Relationship, std::hash<int>, std::equal_to<int> > PlayerRelationMapType;

class InGameUI
{
public:
	bool rva0029FCD9(const char *name);
private:
	char m_pad[0x874];
	PlayerRelationMapType m_keys;
};

bool InGameUI::rva0029FCD9(const char *name)
{
	if (name && *name)
	{
		int key = TheNameKeyGenerator->nameToKey(name);
		return m_keys.find(key) != m_keys.end();
	}
	return false;
}
