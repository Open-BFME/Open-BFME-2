// cl: /MD /DBFME_STRINGBASE_PUBLIC_COPY /DBFME_STRINGBASE_PUBLIC_DTOR /Ireference/shims/bfme2_ascii
//
// ??0Rva004FA830@@QAE@ABV?$StringBase@D@@@Z @0x004FA815 27B: ctor of the
// opaque AsciiString-holder at vtable 0x008633A0. Retail stores the vtable
// then copy-constructs the member at +4 via pinned StringBase<char> copy
// 0x000365F0 and returns this (ret 4). Sibling dtor at 0x004FA830 plus
// deleting dtor at 0x005C4537 in AsciiStringFoldDeleters.cpp (/O1 /MD).
// Caller 0x004FAC21 forwards its own single arg here. Layout read from
// retail lea ecx,[esi+4].

#include "Rva004FA830.h"

Rva004FA830::Rva004FA830(const StringBase<char> &name) : m_name(name)
{
}

void Rva004FA830::buildFieldParse(MultiIniFieldParse &)
{
}
