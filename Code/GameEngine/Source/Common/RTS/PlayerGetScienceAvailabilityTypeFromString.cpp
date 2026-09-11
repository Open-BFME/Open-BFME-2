// cl: /O1 /DNDEBUG /MD /EHsc
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

// Player::getScienceAvailabilityTypeFromString at 0x002ABEC9, 40 bytes.
//
// Anchor: the retail body loops i=0..2, pushing a table entry and calling
// StringBase<char>::compareNoCase(const char*) (0x00037980, pinned in
// reverse/symbols.csv) against the AsciiString argument, returning i on the
// first match or -1. anchor_unclaimed.py tied it to the string literal
// "Available", which -- with "Disabled" and "Hidden" -- is exactly
// ScienceAvailabilityNames[] from
// GeneralsMD/Code/GameEngine/Include/Common/Player.h
// (DEFINE_SCIENCE_AVAILABILITY_NAMES), indexed by ScienceAvailabilityType
// (SCIENCE_AVAILABLE=0, SCIENCE_DISABLED=1, SCIENCE_HIDDEN=2,
// SCIENCE_AVAILABILITY_COUNT=3). The matching ZH source is
// GameEngine/Source/Common/RTS/Player.cpp,
// Player::getScienceAvailabilityTypeFromString, which this body reproduces
// verbatim.
//
// Includes the real Common/Player.h here instead: its AsciiString::compareNoCase
// is defined inline in the ZH header, so cl folds the call away and the shape
// no longer matches. BFME2's AsciiString derives from a real out-of-line
// StringBase<char>::compareNoCase (the pinned callee above), so a minimal
// AsciiString/Player stand-in -- same pattern as
// GameEngine/Source/GameClient/GUI/AptMapPreviewSetMapTitle.cpp -- reproduces
// retail's out-of-line call instead of ZH's inlined compare. The retail body
// never touches Player's own data (ecx/this arrives unused), so the stand-in
// carries no members. Kept in its own translation unit rather than folded
// into the already-huge converted Player.cpp, which other agents may be
// touching concurrently.

template <typename T> class StringBase
{
public:
    int compareNoCase(const char *s) const;
};

class AsciiString : public StringBase<char>
{
};

enum ScienceAvailabilityType
{
    SCIENCE_AVAILABILITY_INVALID = -1,

    SCIENCE_AVAILABLE,
    SCIENCE_DISABLED,
    SCIENCE_HIDDEN,

    SCIENCE_AVAILABILITY_COUNT,
};

static const char *ScienceAvailabilityNames[] =
{
    "Available",
    "Disabled",
    "Hidden",
    0
};

class Player
{
public:
    ScienceAvailabilityType getScienceAvailabilityTypeFromString( const AsciiString& name );
};

ScienceAvailabilityType Player::getScienceAvailabilityTypeFromString( const AsciiString& name )
{
	for( int i = 0; i < SCIENCE_AVAILABILITY_COUNT; i++ )
	{
		if( !name.compareNoCase( ScienceAvailabilityNames[ i ] ) )
		{
			return (ScienceAvailabilityType)i;
		}
	}
	return SCIENCE_AVAILABILITY_INVALID;
}
