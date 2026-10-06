// cl: /MD /EHsc
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

// FILE: DisplayStringManager.cpp /////////////////////////////////////////////////////////////////
// Created:    Colin Day, July 2001
// Desc:       Access for creating game managed display strings
//
// Ported from Zero Hour's GameEngine/Source/GameClient/DisplayStringManager.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
// Minimal BFME 2 view: the list head sits at +0x0C, and DisplayString's
// links at +0x0C/+0x10. BFME 2 turns ZH's assert(string) into a null guard.
///////////////////////////////////////////////////////////////////////////////////////////////////

class DisplayStringManager;

class DisplayString
{
	friend class DisplayStringManager;
public:
	virtual ~DisplayString( void );
protected:
	void *m_textString;																	///< 0x04
	void *m_font;																				///< 0x08
	DisplayString *m_next;															///< 0x0C
	DisplayString *m_prev;															///< 0x10
};

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager( void );
protected:
	void link( DisplayString *string );
	char m_opaque04[ 8 ];
	DisplayString *m_stringList;												///< 0x0C
	DisplayString *m_currentCheckpoint;									///< 0x10
};

//-------------------------------------------------------------------------------------------------
/** Link a display string to the master list */
//-------------------------------------------------------------------------------------------------
void DisplayStringManager::link( DisplayString *string )
{

	if( string == 0 )
		return;

	string->m_next = m_stringList;
	if( m_stringList )
		m_stringList->m_prev = string;

	m_stringList = string;

}  // end link
