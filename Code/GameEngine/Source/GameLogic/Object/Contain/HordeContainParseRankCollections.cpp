// cl: /Oy- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Donor: Open-BFME-1 HordeContainParseRanksThatStopAdvance.cpp and
// HordeContainParseRankSets.cpp; donor RVAs are NOT BFME2 addresses.
// BFME2 PC table VA C45530 identifies these field callbacks. The PC bodies
// use INI separators at +418 (donor +414), imported atoi at IAT BBA624,
// and out-of-line STLport insertion rather than the donor's inlined nodes.
// Names describe table roles; original parser symbol names are not recovered.
// Xbox retail/TU2 schema correspondence is a lead, not PC ABI/byte proof.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <list>
#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

class INI
{
public:
    const char *getNextTokenOrNull(const char *);
    char unknown[0x418];
    const char *seps;
};

void parseHordeContainRanksThatStopAdvance(INI *ini, void *, void *store, const void *)
{
    for (const char *token = ini->getNextTokenOrNull(ini->seps); token;
         token = ini->getNextTokenOrNull(ini->seps))
        ((_STL::list<int> *)store)->push_back(_STL::atoi(token));
}

void parseHordeContainRankSets(INI *ini, void *, void *store, const void *)
{
    for (const char *token = ini->getNextTokenOrNull(ini->seps); token;
         token = ini->getNextTokenOrNull(ini->seps))
        ((_STL::set<int> *)store)->insert(_STL::atoi(token));
}
