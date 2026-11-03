// FILE: OpaqueRefCounted.h ///////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 OpaqueRefCounted, an atomically reference-counted object with a virtual
//         destructor.
//
// Target facts:
//  - Polymorphic: Release_Ref (0x00050ED3) loads the receiver's vptr, calls slot 0 with flags 0
//    and then scalar operator delete (0x0002FD60), the `::delete this` sequence of a class whose
//    destructor is virtual. No other slot is proven, so only the destructor is declared.
//  - +0x04 is a signed four-byte count: Add_Ref (0x00050EC8), Release_Ref (0x00050ED3) and
//    rva00050EFA (0x00050EFA) pass receiver+4 to kernel32 InterlockedIncrement and
//    InterlockedDecrement (IAT 0x00BBA214, 0x00BBA21C); Release_Ref deletes when the result is
//    not greater than zero, rva00050EFA undoes an increment whose result is not greater than one.
//  - Add_Ref is inline: OpaqueRefElement4::operator= (0x00239099) inlines the increment at
//    0x002390AB. Its out-of-line copy is the 11-byte body 0x00050EC8.
//  - Release_Ref and rva00050EFA are rowed and called out of line.
//  - sizeof 8 covers the proven vptr and count only; holders embed the object at +0x88 and
//    increment holder+0x8C (BfmePoolRef10 constructor 0x00051931).
// Zero Hour has no such class. The class name and m_04 are neutral spellings, not original names.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef BFME_OPAQUE_REF_COUNTED_H
#define BFME_OPAQUE_REF_COUNTED_H

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *addend);

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();

	void Add_Ref() { InterlockedIncrement(&m_04); }
	bool rva00050EFA();
	void Release_Ref();

	long m_04;
};

#endif
