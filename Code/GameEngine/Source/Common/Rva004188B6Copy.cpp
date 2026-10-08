// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHs /MD
//
// ??0Rva004188B6@@QAE@ABU0@@Z @0x004188B6 89B: copy constructor of a 32-byte
// record: two 12-byte members copied through the existing address-derived
// call view at 0x004186F2 (now rowed as a tree copy under its template name)
// (+0, +0xC; address-derived pin), an AsciiString at +0x18 and bytes +0x1C/+0x1D,
// each constructed member advancing the EH state. Callers 0x00418935 and
// 0x0041896F; record identity not recovered.

#include "Common/Rva00418A12StringHash.h"

Rva004188B6::Rva004188B6(const Rva004188B6 &other) :
	m_00(other.m_00),
	m_0C(other.m_0C),
	m_18(other.m_18),
	m_1C(other.m_1C),
	m_1D(other.m_1D)
{
}
