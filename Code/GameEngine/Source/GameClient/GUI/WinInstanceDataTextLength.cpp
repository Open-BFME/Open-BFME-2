// cl: /O1 /MD
#include "../../../Include/GameClient/DisplayString.h"

class WinInstanceData
{
public:
    int getTextLength();

private:
    char m_prefix[0x19c];
    DisplayString *m_text;
};

inline int WinInstanceData::getTextLength()
{
    DisplayString * volatile *textSlot = &m_text;
    if (*textSlot)
        return (*textSlot)->getTextLength();
    return 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeWinInstanceDataInlineAnchorWinInstanceDataTextLength@@YAXPAVWinInstanceData@@@Z absent-from-retail
void _bfmeWinInstanceDataInlineAnchorWinInstanceDataTextLength(WinInstanceData *winInstanceData)
{
    winInstanceData->getTextLength();
}
#pragma inline_depth()
