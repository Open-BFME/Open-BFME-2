// Word-field getters: eight-byte __thiscall members with one shape:
//
//     mov ax,[ecx+<DISP>] / ret
//
// One word is read at a fixed displacement from `this` and returned in ax.
// Ported from Open-BFME-1 (Code/GameEngine/Source/Common/TinyWordFieldGetters.cpp):
// the BFME_WORD_FIELD_GETTER macro is verbatim (unsigned short get() const
// over a lead array), only the class names follow this tree's Disp* convention
// (address-derived Rva<addr>WordField, identity unrecoverable from 8 bytes).
// Every displacement here is a disp32 (MSVC 7.1 uses disp8 whenever the
// offset fits, so every offset is at least 0x80).
// No // cl: line (defaults match the frameless 8-byte shape).
#include "../../Include/Common/BfmeAccessorMacros.h"

BFME_WORD_FIELD_GETTER(Rva0028A873WordField, 0x5D8)
BFME_WORD_FIELD_GETTER(Rva005686B1WordField, 0xE0)
BFME_WORD_FIELD_GETTER(Rva005686B9WordField, 0xE2)
BFME_WORD_FIELD_GETTER(Rva0059EAE8WordField, 0x1008)
