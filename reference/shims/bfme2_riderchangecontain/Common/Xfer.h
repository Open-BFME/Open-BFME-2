// Copied from reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h; each change is marked "// BFME 2:".
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

// FILE: Xfer.h ///////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, February 2002
// Desc:   The Xfer system is capable of setting up operations to work with blocks of data
//				 from other subsystems.  It can work things such as file reading, file writing,
//				 CRC computations etc
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __XFER_H_
#define __XFER_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/STLTypedefs.h"
#include "Common/ModelState.h"
#include "Common/Science.h"
#include "Common/Upgrade.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class Snapshot;
typedef Int Color;
enum ObjectID;
enum DrawableID;
enum KindOfType;
enum ScienceType;
class Matrix3D;

// ------------------------------------------------------------------------------------------------
typedef UnsignedByte XferVersion;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
enum XferMode
{
	XFER_INVALID = 0,

	XFER_SAVE,
	XFER_LOAD,
	XFER_CRC,

	NUM_XFER_TYPES  // please keep this last
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
enum XferStatus
{
	XFER_STATUS_INVALID = 0,
	
	XFER_OK,														///< all is green and good
	XFER_EOF,														///< end of file encountered
	XFER_FILE_NOT_FOUND,								///< requested file does not exist
	XFER_FILE_NOT_OPEN,									///< file was not open
	XFER_FILE_ALREADY_OPEN,							///< this xfer is already open
	XFER_READ_ERROR,										///< error reading from file
	XFER_WRITE_ERROR,										///< error writing to file
	XFER_MODE_UNKNOWN,									///< unknown xfer mode
	XFER_SKIP_ERROR,										///< error skipping file
	XFER_BEGIN_END_MISMATCH,						///< mismatched pair calls of begin/end block
	XFER_OUT_OF_MEMORY,									///< out of memory
	XFER_STRING_ERROR,									///< error with strings
	XFER_INVALID_VERSION,								///< invalid version encountered
	XFER_INVALID_PARAMETERS,						///< invalid parameters
	XFER_LIST_NOT_EMPTY,								///< trying to xfer into a list that should be empty, but isn't
	XFER_UNKNOWN_STRING,								///< unrecognized string value
	
	XFER_ERROR_UNKNOWN,									///< unknown error (isn't that useful!)

	NUM_XFER_STATUS  // please keep this last
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
enum XferOptions
{
	XO_NONE										= 0x00000000,
	XO_NO_POST_PROCESSING			= 0x00000001,

	XO_ALL										= 0xFFFFFFFF  // keep this last please
};

///////////////////////////////////////////////////////////////////////////////////////////////////
typedef Int XferBlockSize;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME 2: Xfer is the registered interface in Code/GameEngine/Include/Common/BfmeXfer.h (row
// ?xfer@RiderChangeContain@@MAEXPAVXfer@@@Z 0x0047E357 dispatches through its slots), which needs
// its operand types declared first.
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
#include "../../../../Code/GameEngine/Include/Common/BfmeXfer.h"

#endif // __XFER_H_

