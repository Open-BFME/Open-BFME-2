#ifndef BFME2_BATTLE_PROMPT_ARMY_PANEL_VIEW_H
#define BFME2_BATTLE_PROMPT_ARMY_PANEL_VIEW_H

#include "BattlePromptMovieClipView.h"
#include "BattlePromptCounterView.h"
#include <vector>

// Use the existing 32-bit enum-vector provider by representation. These
// entries are counter-category indices; their original enum name is unknown.
enum ScienceType { SCIENCE_NONE = 0 };
namespace _STL {
template<> void vector<ScienceType, allocator<ScienceType> >::reserve(unsigned);
template<> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
}
class Rva005FEF65Base
{
public:
    Rva005FEF65Base() : m_04(0) {}
    virtual ~Rva005FEF65Base() {}
private:
    int m_04;
};
class Rva005FEF65 : public Rva005FEF65Base
{
public:
    Rva005FEF65(int, int, const Rva005FEF11Input **);
    virtual ~Rva005FEF65();
private:
    Rva005FED2A m_08;
    const Rva005FEF11Input *m_input14;
    _STL::vector<ScienceType, _STL::allocator<ScienceType> > m_types18;
    int m_selected24;
};

#endif
