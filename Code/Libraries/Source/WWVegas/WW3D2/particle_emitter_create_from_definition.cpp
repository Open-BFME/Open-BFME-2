// cl: /G7 /EHsc /Ireference/shims/bfmeshader /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

/*************************************************************************** 
 ***    C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S     *** 
 *************************************************************************** 
 *                                                                         * 
 *                 Project Name : G                                        * 
 *                                                                         * 
 *                     $Archive:: /Commando/Code/ww3d2/part_emt.cpp       $* 
 *                                                                         * 
 *                  $Org Author:: Jani_p                                  $* 
 *                                                                         * 
 *                      $Author:: Kenny_m                                  $* 
 *                                                                         * 
 *                     $Modtime:: 08/05/02 10:44a                          $* 
 *                                                                         * 
 *                    $Revision:: 14                                      $* 
 *                                                                         * 
 * 08/05/02 KM Texture class redesign
 *-------------------------------------------------------------------------* 
 * Functions:                                                              * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "shader.h"
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "part_emt.h"
#include "wwdebug.h"
#include "ww3d.h"
#include "assetmgr.h"
#include "part_ldr.h"
#include "w3derr.h"
#include "scene.h"
#include "texture.h"
#include "wwprofile.h"
#include <limits.h>
#include "gcd_lcm.h"
#include "texture.h"
#include "part_ldr.h"


#include "texture_handle.h"

// Descriptive identity: cached texture lookup or creation at retail RVA 0x132D89.
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
ParticleEmitterClass *
ParticleEmitterClass::Create_From_Definition (const ParticleEmitterDefClass &definition)
{
	// Assume failure
	ParticleEmitterClass *pemitter = NULL;

	// Attempt to load the texture for this emitter
	const char *ptexture_filename = definition.Get_Texture_Filename ();
	BFME2ParticleTextureHandle ptexture;
	if (ptexture_filename && ptexture_filename[0]) {
		ptexture = BFME2LoadParticleTexture(ptexture_filename,0,0);
	}

	ShaderClass shader;
	definition.Get_Shader (shader);


	//
	//	Peek at the definition's keyframes
	//
	ParticlePropertyStruct<Vector3> color_keys;
	ParticlePropertyStruct<float> opacity_keys;
	ParticlePropertyStruct<float> size_keys;
	ParticlePropertyStruct<float> rotation_keys;
	ParticlePropertyStruct<float> frame_keys;
	ParticlePropertyStruct<float> blur_time_keys;

	definition.Get_Color_Keyframes (color_keys);
	definition.Get_Opacity_Keyframes (opacity_keys);
	definition.Get_Size_Keyframes (size_keys);
	definition.Get_Rotation_Keyframes (rotation_keys);
	definition.Get_Frame_Keyframes (frame_keys);
	definition.Get_Blur_Time_Keyframes (blur_time_keys);

	//
	//	Create the emitter
	//
	pemitter = NEW_REF( ParticleEmitterClass, (	definition.Get_Emission_Rate (),
																definition.Get_Burst_Size (),
																definition.Get_Creation_Volume (),
																definition.Get_Velocity (), 
																definition.Get_Velocity_Random (),
																definition.Get_Outward_Vel (),
																definition.Get_Vel_Inherit (), 
																color_keys,
																opacity_keys,
																size_keys,
																rotation_keys,
																definition.Get_Initial_Orientation_Random(),
																frame_keys,
																blur_time_keys,
																definition.Get_Acceleration (),
																definition.Get_Lifetime (),
																definition.Get_Future_Start_Time(),
																ptexture,
																shader, 
																definition.Get_Max_Emissions (),
																0,
																false,
																definition.Get_Render_Mode (),
																definition.Get_Frame_Mode (),
																definition.Get_Line_Properties ()) );

	if (color_keys.KeyTimes != NULL) delete [] color_keys.KeyTimes;
	if (color_keys.Values != NULL) delete [] color_keys.Values;
	if (opacity_keys.KeyTimes != NULL) delete [] opacity_keys.KeyTimes;
	if (opacity_keys.Values != NULL) delete [] opacity_keys.Values;
	if (size_keys.KeyTimes != NULL) delete [] size_keys.KeyTimes;
	if (size_keys.Values != NULL) delete [] size_keys.Values;
	if (rotation_keys.KeyTimes != NULL) delete [] rotation_keys.KeyTimes;
	if (rotation_keys.Values != NULL) delete [] rotation_keys.Values;
	if (frame_keys.KeyTimes != NULL) delete [] frame_keys.KeyTimes;
	if (frame_keys.Values != NULL) delete [] frame_keys.Values;
	if (blur_time_keys.KeyTimes != NULL) delete [] blur_time_keys.KeyTimes;
	if (blur_time_keys.Values != NULL) delete [] blur_time_keys.Values;

	// Pass the name along to the emitter
	pemitter->Set_Name (definition.Get_Name ());


	ptexture = NULL;
	// Return a pointer to the new emitter
	return pemitter;
}
