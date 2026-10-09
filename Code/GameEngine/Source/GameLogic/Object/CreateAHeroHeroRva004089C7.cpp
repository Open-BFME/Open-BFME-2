// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE
// ?rva004089C7@Rva0021937DTarget@@QAEXHH@Z retail 0x004089C7..0x00408A55 (142 bytes).
// A CreateAHeroHero member (this goes to the rowed
// CreateAHeroHero::UpdateAwardEarnedFlags 0x00407F05) kept under the pinned
// host name its 0x0021937D triple forward uses. WB twin 0x0107CE10: unless
// TheGameLogic's mode word (+0x110) is 3 and when the award store
// 0x00E02F74 knows the key (pinned 0x0040AAF8) it adds the delta to the
// hero's counter for the key's name in the AsciiString map at +0x50 (rowed
// operator[] 0x002C6F8C read then written) and refreshes the earned flags.
// The name is copied from NameKeyGenerator::keyToName into the key's
// argument slot (EH state 0). Callers 0x0021939A..0x00219424 and 0x0021A537..
// 0x0021A61A pass the owner member and 1.
#include "ascii_string.h"

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva0040AAD5;
extern Rva0040AAD5 *g_00E02F74;

class Rva0040BAD0
{
public:
	int rva0040AAF8(int key);
};

struct TreeHintPayload001F8ACB
{
	int m_count;
};

namespace _STL
{
template <class _Tp> struct less {};
template <class _T1, class _T2> struct pair {};
template <class _Tp> class allocator {};
template <class _Key, class _Tp, class _Compare = less<_Key>, class _Alloc = allocator<pair<const _Key, _Tp> > >
class map
{
public:
	_Tp &operator[](const _Key &k);
private:
	void *m_header;
	unsigned int m_count;
	unsigned int m_pad;
};
}

class CreateAHeroHero
{
public:
	void UpdateAwardEarnedFlags();
};

class Rva0021937DTarget
{
public:
	void rva004089C7(int key, int delta);

private:
	unsigned char m_pad00[0x50];
	_STL::map<AsciiString, TreeHintPayload001F8ACB> m_counts;	// +0x50
};

void Rva0021937DTarget::rva004089C7(int key, int delta)
{
	if (TheGameLogic->m_110 != 3 && ((Rva0040BAD0 *)g_00E02F74)->rva0040AAF8(key) != 0)
	{
		AsciiString name = TheNameKeyGenerator->keyToName((NameKeyType)key);
		int count = m_counts[name].m_count;
		count += delta;
		m_counts[name].m_count = count;
		((CreateAHeroHero *)this)->UpdateAwardEarnedFlags();
	}
}
