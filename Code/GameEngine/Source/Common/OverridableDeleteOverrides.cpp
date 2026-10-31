// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Zero Hour Overridable.h donor with target global-delete semantics.
// Target layout: destructor slot 0, next override +4, override flag +8.
#include "../../Include/Common/Overridable.h"
inline Overridable *Overridable::deleteOverrides() {
    if (m_isOverride) {
        ::delete this;
        return 0;
    }
    if (m_nextOverride)
        m_nextOverride = m_nextOverride->deleteOverrides();
    return this;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeOverridableInlineAnchor@@YAXPAVOverridable@@@Z absent-from-retail
void _bfmeOverridableInlineAnchor(Overridable *overridable)
{
    overridable->deleteOverrides();
}
#pragma inline_depth()

// Native assignment callers reach the folded return-this body at 1FD28E.
// Template copying preserves destination override-chain/allocation state.
// This provider stays separate from the callers: a visible empty definition
// lets VC7.1 remove their native base-assignment call even with noinline.
Overridable &Overridable::operator=(const Overridable &that)
{
    return *this;
}
