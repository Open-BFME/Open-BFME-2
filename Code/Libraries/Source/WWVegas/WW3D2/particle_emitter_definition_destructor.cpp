// cl: /Ireference/shims/bfmeshader /EHsc /Ireference/shims/bfmeparticlehandle /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /D_X86_ /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
// platformsdk
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
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

#define _CRTIMP
// SDK components avoid the reference windows.h stand-in and keep the SDK
// persist.h from shadowing WWSaveLoad. /D_X86_ replaces windows.h target setup.
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
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


#include "shader.h"
#include "./part_ldr.h"	// this directory's: the plain spelling reads the reference copy in this unit
#include "part_emt.h"
#include "w3derr.h"
#include "chunkio.h"
#include "assetmgr.h"
#include "texture.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) {	\
		::delete pointer; \
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


ParticleEmitterDefClass::~ParticleEmitterDefClass (void)
{
	// Free the name buffer if necessary
	if (m_pName != NULL) {
		
		// free() is used because the buffer was allocated with ::_strdup().
		::free (m_pName);
		m_pName = NULL;
	}	

	// Free the user-string buffer if necessary
	if (m_pUserString != NULL) {
		
		// free() is used because the buffer was allocated with ::malloc() or ::_strdup().
		::free (m_pUserString);
		m_pUserString = NULL;
	}

	Free_Props ();

	SAFE_DELETE (m_pCreationVolume);
	SAFE_DELETE (m_pVelocityRandomizer);
	return ;
}
