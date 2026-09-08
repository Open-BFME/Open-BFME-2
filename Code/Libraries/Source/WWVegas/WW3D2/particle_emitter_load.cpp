// cl: /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

// Select the BFME2 legacy kernel32 import declarations before reference headers.
#include <sweep/winbase_shim.h>

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
// Particle system loader, adapted from the Generals Zero Hour reference.
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : WW3D                                                         *
 *                                                                                             *
 *                     $Archive:: /VSS_Sync/ww3d2/part_ldr.cpp              $*
 *                                                                                             *
 *                       Author:: Patrick Smith                                                
 *                                                                                             *
 *                     $Modtime:: 10/26/01 2:57p                                              $*
 *                                                                                             *
 *                    $Revision:: 11                                                          $*
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#include "part_ldr.h"
#include "part_emt.h"
#include "w3derr.h"
#include "chunkio.h"
#include "win.h"		// for lstrcpy, can this be improved?
#include "assetmgr.h"
#include "texture.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) {	\
		delete pointer; \
		pointer = 0; \
	} \
}
#endif //SAFE_DELETE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(pointer)	\
	if (pointer) {					\
		delete [] pointer;			\
		pointer = 0;				\
	}									\

#endif //SAFE_DELETE


///////////////////////////////////////////////////////////////////////////////////
//
//	Global variable initialization
//
ParticleEmitterLoaderClass	_ParticleEmitterLoader;

//	This array is declared in "W3D_File.H"
const char *EMITTER_TYPE_NAMES[EMITTER_TYPEID_COUNT] = 
{
	"Default"
};


bool
ParticleEmitterDefClass::Load_W3D (ChunkLoadClass &chunk_load)
{
	// Assume error
	bool ret_val = false;
	Initialize_To_Ver2 ();

	// Attempt to read the different sections of the emitter definition
	if ((Read_Header (chunk_load)) &&
		 (Read_User_Data (chunk_load)) &&
		 (Read_Info (chunk_load))) {
		
		if (m_Version > 0x00010000) {
			
			//
			// Read the version 2.0 structures from the chunk
			//
			if ((Read_InfoV2 (chunk_load)) &&
				 (Read_Props (chunk_load))) {

				// Success!
				ret_val = true;
			}
		} else {

			// Make sure the data fits version 2
			Convert_To_Ver2 ();
			ret_val = true;
		}
	}

	// (gth) Handle all future additions to the particle emitter file format
	// in the typical chunk fashion.  
	while (chunk_load.Open_Chunk() && ret_val) {
		
		switch (chunk_load.Cur_Chunk_ID()) 
		{
			case W3D_CHUNK_EMITTER_LINE_PROPERTIES:
				ret_val = Read_Line_Properties(chunk_load);
				break;
			
			case W3D_CHUNK_EMITTER_ROTATION_KEYFRAMES:
				ret_val = Read_Rotation_Keyframes(chunk_load);
				break;

			case W3D_CHUNK_EMITTER_FRAME_KEYFRAMES:
				ret_val = Read_Frame_Keyframes(chunk_load);
				break;

			case W3D_CHUNK_EMITTER_BLUR_TIME_KEYFRAMES:
				ret_val = Read_Blur_Time_Keyframes(chunk_load);
				break;

			case W3D_CHUNK_EMITTER_EXTRA_INFO:
				ret_val = Read_Extra_Info(chunk_load);
				break;
				
			default: 
				WWDEBUG_SAY(("Unhandled Chunk! File: %s Line: %d\r\n",__FILE__,__LINE__));
				break;
		}
		
		chunk_load.Close_Chunk();
	}

	// Return the bool return code
	return ret_val;
}
