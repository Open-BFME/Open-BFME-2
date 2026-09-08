// cl: /Ireference/shims/bfmeshader /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims/bfmeparticlehandle /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
#define _CRTIMP
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


#include "shader.h"
#include "part_ldr.h"
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


ParticleEmitterDefClass::ParticleEmitterDefClass (const ParticleEmitterDefClass &src)
	:	m_pName (NULL),
		m_Version (0L),
		m_pUserString (NULL),	  
		m_iUserType (EMITTER_TYPEID_DEFAULT),
		m_InitialOrientationRandom (src.m_InitialOrientationRandom),
		m_pCreationVolume (NULL),
		m_pVelocityRandomizer (NULL)
{
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_InfoV2, 0, sizeof (m_InfoV2));	
	::memset (&m_ExtraInfo, 0, sizeof (m_ExtraInfo));	

	::memset (&m_ColorKeyframes, 0, sizeof (m_ColorKeyframes));
	::memset (&m_OpacityKeyframes, 0, sizeof (m_OpacityKeyframes));
	::memset (&m_SizeKeyframes, 0, sizeof (m_SizeKeyframes));
	::memset (&m_RotationKeyframes, 0, sizeof (m_RotationKeyframes));
	::memset (&m_FrameKeyframes, 0, sizeof (m_FrameKeyframes));
	::memset (&m_BlurTimeKeyframes, 0, sizeof (m_BlurTimeKeyframes));
	::memset (&m_LineProperties, 0, sizeof (m_LineProperties));

	(*this) = src;
	return ;
}
