// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport
//
// ?push_back@?$deque@UGen_t_00595870_p12cd@@V?$allocator@UGen_t_00595870_p12cd@@@_STL@@@_STL@@QAEXABUGen_t_00595870_p12cd@@@Z
// retail 0x00586204, 45 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/Gen00595870DequePushBackAux.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor emits this body
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// definitions are omitted.
//
// Retail's shape is the STLport deque push_back for this element: the element
// is twelve bytes (one dword string-family subobject plus two copied inline),
// the cursor and the node-end live at +0x10 and +0x18, and a full node tail
// jumps to the auxiliary body. The auxiliary is left unnamed here because no
// target evidence in this clone identifies it; the in-node construct callee
// 0x0002CA82C is rowed and resolves.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
// BFME2's shared AsciiString (reference/shims/bfme2_ascii/ascii_string.h).
// Retail's own copy body is the forwarder at 0x0005EE50 delegating to the
// StringBase<char> copy, and this header is the view that encodes the same call
// at a member copy site.
#include "ascii_string.h"

// The generated payload name records the observed 12-byte copy-and-destroy
// shape. Its first dword is a string-family subobject; the remaining two
// dwords are copied inline by MSVC 7.1.
struct Gen_t_00595870_p12cd
{
	AsciiString m_name;
	int m_first;
	int m_second;
};

typedef _STL::deque<Gen_t_00595870_p12cd> Rva00586204Deque;

// Nothing else in this unit uses the deque, so a scope-exit handler is what
// keeps the push_back from being discarded as unused. Not retail data.
void Rva00586204Anchor(Rva00586204Deque &values, const Gen_t_00595870_p12cd &value)
{
	values.push_back(value);
}