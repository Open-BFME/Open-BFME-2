// cl: /O1 /DNDEBUG /MD
//
// MultiIniFieldParse::MultiIniFieldParse, retail 0x0002BAA0, 26 bytes.
// Dedicated TU so INI wrappers cannot inline this zeroing loop.

#include "../../../Include/Common/INI/FieldParse.h"

inline MultiIniFieldParse::MultiIniFieldParse()
	: m_count(0)
{
	for (int i = 0; i < 16; i++)
	{
		m_extraOffset[i] = 0;
		m_fieldParse[i] = 0;
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeMultiIniFieldParseInlineAnchor@@YAXPAVMultiIniFieldParse@@@Z absent-from-retail
void _bfmeMultiIniFieldParseInlineAnchor(MultiIniFieldParse *multiIniFieldParse)
{
    multiIniFieldParse->MultiIniFieldParse::MultiIniFieldParse();
}
#pragma inline_depth()
