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
    friend class Rva005FF13A;
    friend class Rva005FAF9FOwner;
public:
    Rva005FEF65(int, int, const Rva005FEF11Input **);
    virtual ~Rva005FEF65();
    void setClipSelected(bool value) { m_08.rva005FF4CD(value); }
private:
    Rva005FED2A m_08;
    const Rva005FEF11Input *m_input14;
    _STL::vector<ScienceType, _STL::allocator<ScienceType> > m_types18;
    int m_selected24;
};

// Native 005FF0F6 constructs this derived panel and sets its clip state to 0.
// Its existing destructor at 005FF13A installs C7A478 and destroys the base.
class Rva005FF13A : public Rva005FEF65
{
public:
    Rva005FF13A(int, int, const Rva005FEF11Input **);
    virtual ~Rva005FF13A();
};

class Rva005FED59;
class BattlePromptOwnerDisplay;
class BattlePromptOwnerActions;
class Rva005FAF9FOwner
{
public:
    char m_pad00[8];
    int m_context08;
    BattlePromptOwnerDisplay *m_display0C;
    BattlePromptOwnerActions *m_actions10;
    void *m_active14;
    // The native callback list/map starts here. Only its address is used;
    // this prefix deliberately makes no claim about the owner's full size.
    unsigned char m_observers18[1];
    void rva005FADEF(Rva005FED59 *);
};
struct Rva005FA89CC
{
    int m_00;
    Rva005FAF9FOwner *m_04;
};
// Native 005FA89C and 005FAF5D share C79E30. The owner at +28 clears its
// active panel on destruction. These names preserve the opaque identities.
class Rva005FAF5D : public Rva005FF13A
{
public:
    Rva005FAF5D(int, int, Rva005FA89CC *);
    virtual ~Rva005FAF5D();
    void rva005FAF9F();
private:
    Rva005FAF9FOwner *m_owner28;
};

#endif
