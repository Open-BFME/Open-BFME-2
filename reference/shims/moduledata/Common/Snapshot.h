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

// FILE: Snapshot.h ///////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Snapshot base. Retail vtable 0x00BBB554 has a
//         deleting destructor followed by three pure virtual slots, in
//         retail order: loadPostProcess, GetSnapshotName, xfer.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __SNAPSHOT_H_
#define __SNAPSHOT_H_

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Xfer;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class Snapshot
{

friend class GameState;
friend class XferLoad;
friend class XferSave;
friend class XferCRC;

public:
	
	Snapshot() {}
	Snapshot( const Snapshot &that ) {}
	virtual ~Snapshot( void ) {}

protected:

	// Retail order. Vtable 0x00BBB554 is the deleting destructor, then three
	// __purecall slots, and the overriders fix what each slot is:
	//  - the exports name every FXParticleSystem info's overriders
	//    LoadPostProcess, GetSnapshotName and DoXfer(Xfer &), and their
	//    vtables (e.g. 0x00BBB5C8) hold them in slots 1, 2 and 3;
	//  - Xfer::operator&(Snapshot &) (export, 0x0060B8C6) calls slot 3
	//    ([eax+0Ch]) with the Xfer;
	//  - Module and ModuleData vtables (0x00C59368, 0x00C52534, 0x00C594E0)
	//    hold loadPostProcess in slot 1, a getter returning the class-name
	//    literal in slot 2 and xfer in slot 3.
	// Retail has no crc. The Zero Hour classes still compiled against this
	// header override crc(Xfer *), so it stands in for GetSnapshotName in
	// slot 2 and keeps every derived table at four base slots; slots 1 and 3
	// keep the Zero Hour spellings the ledger's rows use.

	/** post process phase for loading save games.  All save systems have their xfer
	run using XferLoad mode, and then all systems each have their post process run */
	virtual void loadPostProcess( void ) = 0;

	/// slot 2: retail GetSnapshotName (see above)
	virtual void crc( Xfer *xfer ) = 0;

	/** run save, load, or deep CRC check on this data structure, the type depends on the
	setup of the Xfer pointer */
	virtual void xfer( Xfer *xfer ) = 0;

};

#endif // __SNAPSHOT_H_
