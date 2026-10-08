// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB107C200 names CreateAHeroHero::Reset; native4091F9..409285 proves the
// null guard, scalar resets and cleanup providers. BF1 ba7ddda and ZH have
// no clean hero Reset donor. Existing CreateAHeroData matches independently
// support this 0x140-byte layout; early map keys keep the cleanup provider's
// provisional spelling and are not recovered hero key identities.
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <vector>

struct Rva0021A917Element { short words[1]; };
struct TreeHintPayload001F8ACB { unsigned int value; };
typedef _STL::map<Rva0021A917Element, int> ResetWordMap;
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> ResetStringMap;
typedef _STL::map<int, _STL::vector<unsigned int> > ResetBlingMap;
// These cleanup definitions already have verified providers. Use their external
// specializations instead of emitting incidental container implementations here.
namespace _STL {
template<> void _Rb_tree<Rva0021A917Element, pair<const Rva0021A917Element, int>, _Select1st<pair<const Rva0021A917Element, int> >, less<Rva0021A917Element>, allocator<pair<const Rva0021A917Element, int> > >::clear();
template<> void _Rb_tree<AsciiString, pair<const AsciiString, TreeHintPayload001F8ACB>, _Select1st<pair<const AsciiString, TreeHintPayload001F8ACB> >, less<AsciiString>, allocator<pair<const AsciiString, TreeHintPayload001F8ACB> > >::clear();
template<> void _Rb_tree<int, pair<const int, vector<unsigned int> >, _Select1st<pair<const int, vector<unsigned int> > >, less<int>, allocator<pair<const int, vector<unsigned int> > > >::clear();
template<> void vector<bool>::clear();
template<> AsciiString *vector<AsciiString>::erase(AsciiString *, AsciiString *);
}


class CreateAHeroHero
{
public:
	void Reset();

private:
    unsigned int m_word00;
    unsigned int m_word04;
    UnicodeString m_name08;
    unsigned int m_word0C, m_word10;
    ResetWordMap m_map14, m_map20;
    unsigned int m_word2C, m_word30, m_word34, m_word38;
    _STL::vector<AsciiString> m_strings3C;
    bool m_flag48;
    AsciiString m_text4C;
    ResetStringMap m_map50;
    _STL::vector<bool> m_bits5C;
    bool m_flag70, m_flag71;
    unsigned short m_pad72;
    ResetBlingMap m_bling74;
    unsigned char m_opaque80[0x134 - 0x80];
    unsigned int m_word134, m_word138, m_word13C;
};

// WB107C200 Reset; native4091F9..409285. Container cleanup uses the existing
// owners' ABI views. The short-key map type is that provider's provisional
// spelling, not a recovered identity for the hero's two early maps.
// ?Reset@CreateAHeroHero@@QAEXXZ
void CreateAHeroHero::Reset()
{
    if (this)
    {
        m_word04 = 0;
        m_name08.clear();
        m_word0C = 0;
        m_word10 = 0;
        m_map14.clear();
        m_map20.clear();
        m_word2C = 0xffffffff;
        m_word30 = 0xff707070;
        m_word34 = 0xffffffff;
        m_word38 = 0x2ff;
        _STL::vector<AsciiString> *strings = &m_strings3C;
        strings->erase(strings->begin(), strings->end());
        m_flag48 = false;
        m_text4C.clear();
        m_map50.clear();
        m_bits5C.clear();
        m_flag70 = false;
        m_flag71 = false;
        m_bling74.clear();
        m_word134 = 0;
        m_word138 = 0;
        m_word13C = 0;
    }
}

typedef char CreateAHeroHeroLayoutCheck[sizeof(CreateAHeroHero) == 0x140 ? 1 : -1];
