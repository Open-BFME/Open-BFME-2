// cl: /MD /GX
// stlport
// GameClient::addIconLayer (WorldBuilder name, GameClient.cpp lines 1605..1606: push_back onto the indexed icon-layer list at +0xF8).
// was ?rva00239FCC@Rva00239FCC@@QAEXHPAVDrawable@@@Z @0x00239FCC (24B):
// indexed list push_back. Retail: eax=&arg2; push eax; eax=arg1;
// ecx=this+eax*4+0xF8; call list<Drawable*>::push_back (0x239E0B); ret 8.
// Manual index*4 arithmetic forces the scale-4 lea; the list call is a
// TU-local declaration pinned to the rowed 0x239E0B (see symbols.csv);
// address-derived outer name; the canonical DrawableList brings STLport's list.
#include "../../Include/GameClient/Drawable.h"

#include "../../Include/GameClient/DrawableList.h"

#include "../../Include/GameClient/GameClientClass.h"

// was ?rva00239FCC@Rva00239FCC@@QAEXHPAVDrawable@@@Z
void GameClient::addIconLayer(int index, Drawable *value)
{
	((DrawableList *)((char *)this + 0xF8 + index * 4))->pushBack((const Drawable *&)value);
}

// The retail call in this body reads 0x00239E0B, an address the ledger already
// carries as ?push_back@?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QAEXABQAVDrawable@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?pushBack@DrawableList@@QAEXAAPBVDrawable@@@Z=?push_back@?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QAEXABQAVDrawable@@@Z")
