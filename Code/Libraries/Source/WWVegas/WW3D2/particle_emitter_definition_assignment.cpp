// cl: /Ireference/shims/bfmeshader /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims/bfmeparticlehandle /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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


const ParticleEmitterDefClass &
ParticleEmitterDefClass::operator= (const ParticleEmitterDefClass &src)
{
	//
	//	Copy the user structures
	//
	Set_Name (src.Get_Name ());
	Set_User_String (src.Get_User_String ());
	Set_User_Type (src.Get_User_Type ());
	m_Version = src.m_Version;

	//
	//	Copy the information structures
	//
	::memcpy (&m_Info, &src.m_Info, sizeof (m_Info));
	::memcpy (&m_InfoV2, &src.m_InfoV2, sizeof (m_InfoV2));
	::memcpy (&m_ExtraInfo, &src.m_ExtraInfo, sizeof (m_ExtraInfo));
	::memcpy (&m_LineProperties, &src.m_LineProperties, sizeof(m_LineProperties));

	//
	//	Copy the keyframes
	//
	Free_Props ();
	::Copy_Emitter_Property_Struct (m_ColorKeyframes, src.m_ColorKeyframes);
	::Copy_Emitter_Property_Struct (m_OpacityKeyframes, src.m_OpacityKeyframes);
	::Copy_Emitter_Property_Struct (m_SizeKeyframes, src.m_SizeKeyframes);
	::Copy_Emitter_Property_Struct (m_RotationKeyframes, src.m_RotationKeyframes);
	::Copy_Emitter_Property_Struct (m_FrameKeyframes, src.m_FrameKeyframes);
	::Copy_Emitter_Property_Struct (m_BlurTimeKeyframes, src.m_BlurTimeKeyframes);
	m_InitialOrientationRandom = src.m_InitialOrientationRandom;

	//
	//	Create the randomizers
	//
	SAFE_DELETE (m_pCreationVolume);
	SAFE_DELETE (m_pVelocityRandomizer);
	m_pCreationVolume			= Create_Randomizer (m_InfoV2.CreationVolume);
	m_pVelocityRandomizer	= Create_Randomizer (m_InfoV2.VelRandom);
	return (*this);
}
