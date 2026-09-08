// cl: /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims/bfmeparticlehandle /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
//
ParticleEmitterLoaderClass	_ParticleEmitterLoader;

const char *EMITTER_TYPE_NAMES[EMITTER_TYPEID_COUNT] = 
{
	"Default"
};


#include "texture_handle.h"
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
void
ParticleEmitterDefClass::Convert_To_Ver2 (void)
{
	if (m_Version < 0x00020000) {		
		m_InfoV2.BurstSize = 1;
		m_InfoV2.OutwardVel = 0;
		m_InfoV2.VelInherit = 0;		

		//
		//	Determine which shader to use...
		//
		ShaderClass shader = ShaderClass::_PresetAdditiveSpriteShader;
		BFME2ParticleTextureHandle ptexture = BFME2LoadParticleTexture(m_Info.TextureFilename,0,0);
		if (ptexture) {
			// If texture has an alpha channel do alpha blending instead of additive
			// (which is the default for point groups):
			if (ptexture.Use_Alpha_Shader()) {
				shader = ShaderClass::_PresetAlphaSpriteShader;
			}
		}
		W3dUtilityClass::Convert_Shader (shader, &m_InfoV2.Shader);

				
		//
		//	Convert the randomziers
		//
		m_InfoV2.CreationVolume.ClassID = Vector3Randomizer::CLASSID_SOLIDBOX;
		m_InfoV2.CreationVolume.Value1 = m_Info.PositionRandom / 1000.0f;
		m_InfoV2.CreationVolume.Value2 = m_Info.PositionRandom / 1000.0f;
		m_InfoV2.CreationVolume.Value3 = m_Info.PositionRandom / 1000.0f;

		m_InfoV2.VelRandom.ClassID = Vector3Randomizer::CLASSID_SOLIDBOX;
		m_InfoV2.VelRandom.Value1 = m_Info.VelocityRandom;
		m_InfoV2.VelRandom.Value2 = m_Info.VelocityRandom;
		m_InfoV2.VelRandom.Value3 = m_Info.VelocityRandom;

		//
		//	Recreate the randomizers
		//
		if (m_pCreationVolume) { ::delete m_pCreationVolume; m_pCreationVolume = NULL; }
		if (m_pVelocityRandomizer) { ::delete m_pVelocityRandomizer; m_pVelocityRandomizer = NULL; }
		m_pCreationVolume = Create_Randomizer (m_InfoV2.CreationVolume);
		m_pVelocityRandomizer = Create_Randomizer (m_InfoV2.VelRandom);

		//
		//	Convert the colors, opacities, and sizes
		//		
		Free_Props ();
		m_ColorKeyframes.Start = RGBA_TO_VECTOR3 (m_Info.StartColor);
		m_ColorKeyframes.Rand = Vector3 (0, 0, 0);
		m_ColorKeyframes.NumKeyFrames = 1;
		m_ColorKeyframes.KeyTimes = W3DNEW float(m_Info.FadeTime);
		m_ColorKeyframes.Values = W3DNEW Vector3(RGBA_TO_VECTOR3 (m_Info.EndColor));

		m_OpacityKeyframes.Start = ((float)(m_Info.StartColor.A)) / 255;
		m_OpacityKeyframes.Rand = 0;
		m_OpacityKeyframes.NumKeyFrames = 1;
		m_OpacityKeyframes.KeyTimes = W3DNEW float(m_Info.FadeTime);
		m_OpacityKeyframes.Values = W3DNEW float(((float)(m_Info.EndColor.A)) / 255);

		m_SizeKeyframes.Start = m_Info.StartSize;
		m_SizeKeyframes.Rand = 0;
		m_SizeKeyframes.NumKeyFrames = 0;
	}

	return ;
}
