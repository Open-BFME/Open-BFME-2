// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/shims/namekeygenerator /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
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

// FILE: NameKeyGeneratorNameToLowercaseKey.cpp
// Own TU for NameKeyGenerator::nameToLowercaseKey(const char*) at BFME2
// retail 0x00620500 (187B), transferred from the BFME1 reconstruction of
// the same method (lotrbfme.exe 0x9EDD70).
// Kept separate from Common/NameKeyGenerator.cpp because that file carries a
// pre-existing nonmatching row (parseStringAsNameKeyType, a different BFME
// function) that blocks whole-file byte verification, and this reconstruction
// byte-matches independently here.
//
// BFME retail compiled this method against a stale header (a real in-image
// inconsistency): its Bucket has NO vtable ({m_nextInSocket@0, m_key@4,
// m_nameString@8}, 12 bytes) and m_sockets starts at this+4 with m_nextID at
// this+0x2bf40 -- whereas the matched siblings (init/reset/nameToKey/
// freeSockets) use the vptr'd Bucket with m_sockets at this+8 and m_nextID at
// this+0x2bf44. Retail's early `if (!nameString) return NAMEKEY_INVALID;` is
// also proven by the absence of the `s ? strlen(s) : 0` test in the
// nameString store below. Model the stale layout locally so the shared shim
// (used by the matched siblings) stays untouched.

#include "ascii_string.h"
// Use the canonical one-pointer string view in the legacy name-key headers.
#define ASCIISTRING_H
#include "PreRTS.h"

// The lowercase hash this body calls lives at 0x0061FCA0 in BFME2 retail
// (case-insensitive DJB2, landed as calcHashForLowercaseString in
// namekey_hash_lowercase.cpp). Declared under that rowed name so the
// out-of-line call resolves.
unsigned int calcHashForLowercaseString(const char *p);

//------------------------------------------------------------------------------------------------- 
NameKeyType NameKeyGenerator::nameToLowercaseKey(const char* nameString)
{
	// Preserve the legacy inline length-taking assignment while sharing the
	// canonical string constructor and one-pointer storage.
	struct LegacyNameString : AsciiString
	{
		LegacyNameString &operator=(const char *s)
		{
			((StringBase<char> *)this)->set(s, s ? (int)strlen(s) : 0);
			return *this;
		}
	};
	struct LegacyBucket
	{
		LegacyBucket() : m_nextInSocket(NULL), m_key(NAMEKEY_INVALID) { }
		LegacyBucket *m_nextInSocket;
		NameKeyType m_key;
		LegacyNameString m_nameString;
	};
	LegacyBucket **const sockets = reinterpret_cast<LegacyBucket **>(reinterpret_cast<char *>(this) + 4);
	UnsignedInt *const nextID = reinterpret_cast<UnsignedInt *>(reinterpret_cast<char *>(this) + 0x2bf40);

	if (nameString == NULL)
		return NAMEKEY_INVALID;

	UnsignedInt hash = calcHashForLowercaseString(nameString) % SOCKET_COUNT;

	// hmm, do we have it already?
	for (LegacyBucket *legacyBucket = sockets[hash]; legacyBucket; legacyBucket = legacyBucket->m_nextInSocket)
	{
		if (_strcmpi(nameString, legacyBucket->m_nameString.str()) == 0)
			return legacyBucket->m_key; 
	}

	// nope, guess not. let's allocate it.
	LegacyBucket *legacyBucket = new LegacyBucket;
	legacyBucket->m_key = (NameKeyType)(*nextID)++;
	legacyBucket->m_nameString = nameString;
	legacyBucket->m_nextInSocket = sockets[hash];
	sockets[hash] = legacyBucket;

	return legacyBucket->m_key;

}  // end nameToLowercaseKey
