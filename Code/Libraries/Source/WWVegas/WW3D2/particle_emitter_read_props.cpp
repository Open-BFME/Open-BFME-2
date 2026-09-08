// cl: /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Select the BFME2 legacy kernel32 import declarations before reference headers.
#include <sweep/winbase_shim.h>

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
// Particle system loader, verbatim from Generals Zero Hour reference.
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
ParticleEmitterDefClass::Read_Props (ChunkLoadClass &chunk_load)
{
	// Assume error
	bool ret_val = false;
	Free_Props ();

	// Is this the user chunk?
	if (chunk_load.Open_Chunk () &&
	    (chunk_load.Cur_Chunk_ID () == W3D_CHUNK_EMITTER_PROPS)) {

		W3dEmitterPropertyStruct info = { 0 };
		if (chunk_load.Read (&info, sizeof (info)) == sizeof (info)) {

			unsigned int index=0;
			
			//ParticlePropertyStruct<Vector3>
			m_ColorKeyframes.NumKeyFrames		= info.ColorKeyframes - 1;
			m_OpacityKeyframes.NumKeyFrames	= info.OpacityKeyframes - 1;
			m_SizeKeyframes.NumKeyFrames		= info.SizeKeyframes - 1;
			m_ColorKeyframes.Rand	= RGBA_TO_VECTOR3 (info.ColorRandom);
			m_OpacityKeyframes.Rand	= info.OpacityRandom;
			m_SizeKeyframes.Rand		= info.SizeRandom;

			//
			//	Allocate the array of color keyframes
			//
			if (m_ColorKeyframes.NumKeyFrames > 0) {
				m_ColorKeyframes.KeyTimes = W3DNEWARRAY float[m_ColorKeyframes.NumKeyFrames];
				m_ColorKeyframes.Values = W3DNEWARRAY Vector3[m_ColorKeyframes.NumKeyFrames];
			}

			//
			//	Allocate the array of opacity keyframes
			//
			if (m_OpacityKeyframes.NumKeyFrames > 0) {
				m_OpacityKeyframes.KeyTimes = W3DNEWARRAY float[m_OpacityKeyframes.NumKeyFrames];
				m_OpacityKeyframes.Values = W3DNEWARRAY float[m_OpacityKeyframes.NumKeyFrames];
			}

			//
			//	Allocate the array of size keyframes
			//
			if (m_SizeKeyframes.NumKeyFrames > 0) {
				m_SizeKeyframes.KeyTimes = W3DNEWARRAY float[m_SizeKeyframes.NumKeyFrames];
				m_SizeKeyframes.Values = W3DNEWARRAY float[m_SizeKeyframes.NumKeyFrames];
			}
			
			//
			//	Read the color keyframes from the chunk
			//
			Read_Color_Keyframe (chunk_load, NULL, &m_ColorKeyframes.Start);
			for (index = 0; index < m_ColorKeyframes.NumKeyFrames; index ++) {
				Read_Color_Keyframe (chunk_load,
											&m_ColorKeyframes.KeyTimes[index],
											&m_ColorKeyframes.Values[index]);
			}

			//
			//	If the last keyframe is 'black' and we are using a color randomizer,
			// then make sure the last color is less then 0 so any randomized color
			// will end up as black
			//
			int last_keyframe = (m_ColorKeyframes.NumKeyFrames - 1);
			if (	last_keyframe > 0 &&
					m_ColorKeyframes.Values[last_keyframe].X == 0 &&
					m_ColorKeyframes.Values[last_keyframe].Y == 0 &&
					m_ColorKeyframes.Values[last_keyframe].Z == 0 &&
					(m_ColorKeyframes.Rand.X > 0 || m_ColorKeyframes.Rand.Y > 0 || m_ColorKeyframes.Rand.Z > 0))
			{
				m_ColorKeyframes.Values[last_keyframe].X = -m_ColorKeyframes.Rand.X;
				m_ColorKeyframes.Values[last_keyframe].Y = -m_ColorKeyframes.Rand.Y;
				m_ColorKeyframes.Values[last_keyframe].Z = -m_ColorKeyframes.Rand.Z;
			}

			//
			//	Read the opacity keyframes from the chunk
			//
			Read_Opacity_Keyframe (chunk_load, NULL, &m_OpacityKeyframes.Start);
			for (index = 0; index < m_OpacityKeyframes.NumKeyFrames; index ++) {
				Read_Opacity_Keyframe (chunk_load,
												&m_OpacityKeyframes.KeyTimes[index],
												&m_OpacityKeyframes.Values[index]);
			}

			//
			//	Read the size keyframes from the chunk
			//
			Read_Size_Keyframe (chunk_load, NULL, &m_SizeKeyframes.Start);
			for (index = 0; index < m_SizeKeyframes.NumKeyFrames; index ++) {
				Read_Size_Keyframe (chunk_load,
											&m_SizeKeyframes.KeyTimes[index],
											&m_SizeKeyframes.Values[index]);
			}
				
			// Success!
			ret_val = true;
		}

		// Close the chunk, so the next read will be successful.
		chunk_load.Close_Chunk ();
	}

	// Return whether the property chunk was read successfully
	return ret_val;
}
