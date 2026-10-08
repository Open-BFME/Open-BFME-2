// ?ConstructHeroBlingList@CreateAHeroHero@@QAEXXZ
// partial score=0.69347 date=2026-10-08
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
    void InitButtonList();
    void ConstructHeroBlingList();

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


class CreateAHeroManager {
public:
    class CreateAHeroSubClass {
    public:
        void *GetBlingGroupNameKey(unsigned int);
        unsigned int GetBlingIndex(int, unsigned int);
        unsigned char opaque00[0x28];
        unsigned int groupCount;
    };
    const AsciiString &GetClassUpgradeName(unsigned int);
    const CreateAHeroSubClass *rva0021A1B6(unsigned int, unsigned int);
    bool FindBlingByUpgradeName(const AsciiString &, int *, int *);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class UpgradeTemplate { public: char opaque00[0x38]; unsigned int bit; };
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString &) const; };
extern UpgradeCenter *TheUpgradeCenter;
class Rva001EAE6FHelper { public: Rva001EAE6FHelper *clear80(); };
class Rva00406F9C { public: bool rva00406F9C(const void *); unsigned int words[32]; };
class InitCommandButtonView {
public:
    char opaque00[0x10];
    AsciiString name;
    unsigned int word14;
    InitCommandButtonView *next;
    char opaque1C[0x24C - 0x1C];
    Rva00406F9C mask;
};
class ControlBar { public: char opaque00[0x2C]; InitCommandButtonView *buttons; };
extern ControlBar *TheControlBar;
namespace _STL { template<> void vector<AsciiString>::push_back(const AsciiString &); }
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

// ?InitButtonList@CreateAHeroHero@@QAEXXZ
// WB107FB40 names InitButtonList. Retail409457..40952C rebuilds the string
// vector for buttons whose required upgrade mask intersects the class bit,
// then clears the 0x20 dirty flag. A local requirements view reproduces the
// native ordering of the two argument-address calculations. All helpers use
// their existing verified ABI; original CommandButton layout is not asserted
// beyond the retail name10, next18 and required-mask24C accesses here.
void CreateAHeroHero::InitButtonList()
{
    if (m_word38 & 0x20)
    {
        _STL::vector<AsciiString> *strings = &m_strings3C;
        strings->erase(strings->begin(), strings->end());
        AsciiString upgradeName(TheCreateAHeroManager->GetClassUpgradeName(m_word0C));
        const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(upgradeName);
        if (upgrade)
        {
            Rva00406F9C mask;
            reinterpret_cast<Rva001EAE6FHelper *>(&mask)->clear80();
            mask.words[upgrade->bit >> 5] |= 1U << (upgrade->bit & 31);
            for (InitCommandButtonView *button = TheControlBar->buttons; button; button = button->next)
            {
                Rva00406F9C &requirements = button->mask;
                if (requirements.rva00406F9C(&mask))
                    strings->push_back(button->name);
            }
        }
        m_word38 &= ~0x20;
    }
}

class Rva0021BC2C { public: int rva0021BC2C(int); };
class Rva00406E7D { public: int rva00406E7D(); };
class Rva00406E8F { public: int rva00406E8F(unsigned int); };
struct BfmePod40;
class Rva0040AAD5 { public: BfmePod40 *rva0040AAD5(int); };
extern Rva0040AAD5 *g_00E02F74;
class Rva0040AA27 { public: int rva0040AA27(int); };
class Rva0040A7F1 { public: int rva0040A7F1(int) const; };
class Rva004079D5 { public: char rva004079D5(int, int *); };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: const AsciiString &keyToName(NameKeyType); };
extern NameKeyGenerator *TheNameKeyGenerator;
struct HeroAwardBlingView {
    unsigned int unknown00;
    _STL::vector<int> upgradeKeys;
};
struct HeroBlingNodeView {
    unsigned char opaque00[0x14];
    _STL::vector<unsigned int> blingIds;
};
namespace _STL { template<> vector<unsigned int> &map<int, vector<unsigned int> >::operator[](const int &); }
// ?ConstructHeroBlingList@CreateAHeroHero@@QAEXXZ
void CreateAHeroHero::ConstructHeroBlingList()
{
    CreateAHeroManager::CreateAHeroSubClass *subClass = const_cast<CreateAHeroManager::CreateAHeroSubClass *>(TheCreateAHeroManager->rva0021A1B6(m_word0C, m_word10));
    m_word38 &= ~0x80;
    if (subClass)
    {
        m_bling74.clear();
        for (unsigned int groupIndex = 0; groupIndex < subClass->groupCount; ++groupIndex)
        {
            int groupKey = reinterpret_cast<int>(subClass->GetBlingGroupNameKey(groupIndex));
            for (unsigned int index = 0; index < static_cast<unsigned int>(reinterpret_cast<Rva0021BC2C *>(subClass)->rva0021BC2C(groupKey)); ++index)
            {
                unsigned int blingId = subClass->GetBlingIndex(groupKey, index);
                m_bling74[groupKey].push_back(blingId);
            }
        }
        for (unsigned int awardIndex = 0; awardIndex < static_cast<unsigned int>(reinterpret_cast<Rva00406E7D *>(this)->rva00406E7D()); ++awardIndex)
        {
            BfmePod40 *award = g_00E02F74->rva0040AAD5(reinterpret_cast<Rva00406E8F *>(this)->rva00406E8F(awardIndex));
            if (!award || !static_cast<unsigned char>(reinterpret_cast<Rva0040AA27 *>(award)->rva0040AA27(reinterpret_cast<int>(this))))
                continue;
            HeroAwardBlingView *awardView = reinterpret_cast<HeroAwardBlingView *>(award);
            for (unsigned int upgradeIndex = 0; upgradeIndex < awardView->upgradeKeys.size(); ++upgradeIndex)
            {
                AsciiString upgradeName(TheNameKeyGenerator->keyToName(static_cast<NameKeyType>(reinterpret_cast<Rva0040A7F1 *>(award)->rva0040A7F1(upgradeIndex))));
                int blingId = 0;
                int groupKey = 0;
                int nodeBits = 0;
                if (TheCreateAHeroManager->FindBlingByUpgradeName(upgradeName, &blingId, &groupKey) && reinterpret_cast<Rva004079D5 *>(this)->rva004079D5(groupKey, &nodeBits))
                {
                    _STL::vector<unsigned int> *ids = &reinterpret_cast<HeroBlingNodeView *>(nodeBits)->blingIds;
                    if (_STL::find(ids->begin(), ids->end(), reinterpret_cast<const unsigned int &>(blingId)) == ids->end())
                        m_bling74[groupKey].push_back(blingId);
                }
            }
        }
    }
}
