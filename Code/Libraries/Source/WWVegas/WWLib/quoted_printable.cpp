// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: QuotedPrintable.cpp /////////////////////////////////////////////////////////
// Author: Matt Campbell, February 2002
// Description: Quoted-printable encode/decode
////////////////////////////////////////////////////////////////////////////
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "prerts.h"

// The retail WWLib StringBase header is four fields wide: its character data
// starts eight bytes after the object-owned data header.  Keep this TU-local
// ABI view so the conversion bodies inline the proven retail access.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	void *m_data;
public:
	AsciiString();
	AsciiString(const char *);
	AsciiString(const AsciiString &);
	bool hasData() const { return m_data != 0; }
	const char *str() const
	{
		return m_data ? (const char *)((const char *)m_data + 8)
		              : (const char *)0x0107388B;
	}
	const char *data() const { return (const char *)((const char *)m_data + 8); }
	~AsciiString();
};

// WWLib's retail string header stores the data header at +0x00 and its UTF-16
// payload at +0x08.  This TU only needs that proven view for the encoder; the
// destructor remains the existing WWLib ABI call emitted by the compiler.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "../../../../../reference/shims/bfme2_ascii/unicode_string.h"

#include "quoted_printable.h"

#define MAGIC_CHAR '_'

// takes an integer and returns an ASCII representation
static char intToHexDigit(int num)
{
	if (num<0 || num >15) return '\0';
	if (num<10)
	{
		return '0' + num;
	}
	return 'A' + (num-10);
}

// convert an ASCII representation of a hex digit into the digit itself
static int hexDigitToInt(char c)
{
	if (c <= '9' && c >= '0') return (c - '0');
	if (c <= 'f' && c >= 'a') return (c - 'a' + 10);
	if (c <= 'F' && c >= 'A') return (c - 'A' + 10);
	return 0;
}

// Convert unicode strings into ascii quoted-printable strings
// Defined in quoted_printable_encoders.cpp.
AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

// Convert ascii strings into ascii quoted-printable strings
// Defined in quoted_printable_encoders.cpp.
AsciiString AsciiStringToQuotedPrintable(AsciiString original);

// Convert ascii quoted-printable strings into unicode strings
// Owned by quoted_printable_unicode.cpp.

// Convert ascii quoted-printable strings into ascii strings
// Defined in quoted_printable_ascii.cpp.
AsciiString QuotedPrintableToAsciiString(AsciiString original);

#pragma inline_depth(0)
// ?bfmeEmitQuotedPrintableHelpers@@YAXXZ present-unmatched
void bfmeEmitQuotedPrintableHelpers()
{
	(void)intToHexDigit(0);
	(void)hexDigitToInt(0);
	AsciiString *asciiString = (AsciiString *)0;
	(void)asciiString->hasData();
}
#pragma inline_depth()
