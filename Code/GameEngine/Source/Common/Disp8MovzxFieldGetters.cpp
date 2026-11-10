// Disp8 zero-extending field getters: five-byte __thiscall members with one
// of two shapes:
//
//     movzx eax,word ptr [ecx+<DISP>] / ret
//     movzx eax,byte ptr [ecx+<DISP>] / ret
//
// One word (or byte) is read at a fixed displacement from `this`,
// zero-extended into eax and returned as an unsigned int. Members before the
// accessed one are spelled as a lead array because their types are not
// witnessed here, only their total size. Identity is not recovered: every
// name is derived from its address.
// No // cl: line (defaults match the frameless five-byte shapes; probe-verified
// `0fb7410cc3` / `0fb64120c3` for `unsigned int` returners over
// `unsigned short` / `unsigned char` members).
#include "../../Include/Common/BfmeAccessorMacros.h"


BFME_DISP8_MOVZX_WORD_GETTER(Rva00042F2BMovzxWordField, 0x0C)
BFME_DISP8_MOVZX_BYTE_GETTER(Rva0012606CMovzxByteField, 0x20)
BFME_DISP8_MOVZX_BYTE_GETTER(Rva001E3478MovzxByteField, 0x01)
