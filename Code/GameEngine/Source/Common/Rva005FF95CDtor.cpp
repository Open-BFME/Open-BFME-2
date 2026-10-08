// cl: /MD
// C7A530 joins the constructor owner 005FF912 to destructor 005FF95C.
#include "BattlePromptMovieClipView.h"
class Rva005FF8F8 { public: void clear(); };
Rva005FF912::~Rva005FF912()
{
    ((Rva005FF8F8 *)&m_04)->clear();
}
