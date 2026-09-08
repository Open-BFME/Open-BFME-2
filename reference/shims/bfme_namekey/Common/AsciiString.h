/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: AsciiString.h
//-----------------------------------------------------------------------------

// BFME shadow shim (TU-scoped; only Common/NameKeyGenerator.cpp uses this -I path).
//
// This TU-scoped shim models the one-pointer AsciiString ABI required by the
// BFME2 NameKeyGenerator reconstruction.  Its name-to-key path uses the
// StringBase<char> storage model; the declarations below keep unrelated
// AsciiString methods out of scope.
//
// AsciiString's data member is a single pointer (matches the already-proven
// "chars @ m_data+8" header size: StringBase<char>::Header is
// {int ref_count; ushort length; ushort capacity; T data[]} = 8 bytes), so
// Bucket's layout (vtbl@0, m_nextInSocket@4, m_key@8, m_nameString@0xc,
// sizeof 0x10) is UNCHANGED from the prior shim.

#pragma once

#ifndef ASCIISTRING_H
#define ASCIISTRING_H

#include <string.h>

// The real WWLib template this TU's AsciiString delegates to is already
// byte-matched via Code/Libraries/Source/WWVegas/WWLib/string_base.cpp.
#include "../../../../Code/Libraries/Source/WWVegas/WWLib/string_base.h"

class UnicodeString;

class AsciiString
{
public:
	AsciiString() { m_text = 0; }

	AsciiString(const AsciiString& that);

	// Only needed so reference/shims/sweep/Common/SubsystemInterface.h's
	// `AsciiString name=""` default argument (SubsystemInterfaceList::
	// initSubsystem, pulled in transitively but never called from this TU)
	// type-checks; not a call shape byte-verified against any retail body.
	AsciiString(const char* s);

	~AsciiString();

	AsciiString& operator=(const char* s)
	{
		((StringBase<char>*)this)->set(s);
		return *this;
	}

	// Dead code in this TU (never called from NameKeyGenerator.cpp) -- exists
	// only so SubsystemInterface::setName() and STLTypedefs.h's
	// rts::hash<AsciiString>/equal_to<AsciiString>/less_than_nocase<AsciiString>
	// full specializations (eagerly compiled, not lazily instantiated, since
	// they're non-template) type-check.
	AsciiString& operator=(const AsciiString& that);

	int compareNoCase(const AsciiString& that) const;

	// NOT delegated to StringBase<char>::str() (unlike the real
	// Code/Libraries/Source/WWVegas/WWLib/ascii_string.h): that method has no
	// standalone body anywhere in retail (zero matched rows for
	// ?str@?$StringBase@D@@) -- it is always fully inlined at its call sites,
	// which this TU-scoped delegation (calling an out-of-line, unseen .cpp
	// definition) can't reproduce. nameToKey(const char*)'s
	// `b->m_nameString.str()` disassembles to exactly this inline shape
	// (`mov eax,[bucket+0xc]; test eax,eax; lea esi,[eax+8]; jne ...; mov
	// esi,<empty-string literal>` -- no call at all), so inline the same
	// ternary here directly instead of forwarding.
	const char* str() const { return m_text ? (const char*)(m_text + 8) : ""; }

	static AsciiString TheEmptyString;

private:
	char* m_text;
};

// Dead code in this TU -- see the compareNoCase comment above.
inline bool operator==(const AsciiString& a, const AsciiString& b)
{
	return strcmp(a.str(), b.str()) == 0;
}

#endif // ASCIISTRING_H
