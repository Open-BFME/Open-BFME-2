// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?getTooltipName@MultiplayerColorDefinition@@QBE?AVAsciiString@@XZ @0x002E4336
// Shard TU: the ctor/op= TU calls this out-of-line; defining it there
// inlines and breaks op=, so it lives here.

#include "ascii_string.h"

#include "../../Include/GameNetwork/MultiplayerColorDefinition.h"

// ?getTooltipName@MultiplayerColorDefinition@@QBE?AVAsciiString@@XZ
inline AsciiString MultiplayerColorDefinition::getTooltipName() const
{
	return m_tooltipName;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeMultiplayerColorDefinitionInlineAnchor@@YAXPAVMultiplayerColorDefinition@@@Z absent-from-retail
void _bfmeMultiplayerColorDefinitionInlineAnchor(MultiplayerColorDefinition *multiplayerColorDefinition)
{
    multiplayerColorDefinition->getTooltipName();
}
#pragma inline_depth()
