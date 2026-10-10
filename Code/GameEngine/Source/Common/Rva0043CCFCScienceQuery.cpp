// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Native43CCFC..43CD3C: Apt spell-store holder's player at+4 and selected
// science range at+8/+C. parseSpellIndex_Thunk.cpp independently describes
// slot0 as the already-chosen science query. Owned2AB7D5 is Player::hasScience;
// owned20E873 is the admitted ScienceType find. The constructor's old BfmeE16
// vector spelling establishes storage only; this query proves four-byte IDs.
// Positive outer if preserves retail's cold null return and integer OR tail.
#include <algorithm>

enum ScienceType { SCIENCE_INVALID = 0 };
class Player { public: bool hasScience(ScienceType science) const; };

class Rva0043D16F
{
public:
    bool rva0043CCFC(ScienceType science);
private:
    void *m_vptr;
    Player *m_player;
    ScienceType *m_begin;
    ScienceType *m_end;
    ScienceType *m_capacity;
    int m_count;
};

bool Rva0043D16F::rva0043CCFC(ScienceType science)
{
    if (m_player)
        return m_player->hasScience(science) ||
            _STL::find(m_begin, m_end, science) != m_end;
    return false;
}
