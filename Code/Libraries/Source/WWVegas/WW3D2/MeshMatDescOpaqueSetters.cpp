// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Retain native inlined reference operations without competing external
// copies; whole-body verification also checks that no imported call remains.
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// The reader at188AF0 installs these per-pass references at descriptor+B8.
// Its call at188B54 passes a context entry and the current pass. The pointee's
// original type is unknown; its RefCountClass prefix is established by target.
#include "MeshMatDescClass.h"

void MeshMatDescClass::Set_Single_Rva0015A800(void *entry, int pass)
{
    RefCountClass *value = (RefCountClass *)entry;
    if (value) value->Add_Ref();
    if (field_B8[pass]) field_B8[pass]->Release_Ref();
    field_B8[pass] = value;
}
