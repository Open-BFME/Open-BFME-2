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

ParticleEmitterDefClass *
ParticleEmitterClass::Build_Definition (void) const
{	
	// Allocate a new emitter definition object
	ParticleEmitterDefClass *pdefinition = W3DNEW ParticleEmitterDefClass;
	WWASSERT (pdefinition != NULL);
	if (pdefinition != NULL) {
		
		// Set the texture's filename
		BFME2ParticleTextureHandle ptexture = Get_Texture ();
		if (ptexture) {
			pdefinition->Set_Texture_Filename (ptexture.Get_Texture_Name());
		}
		
		// Now fill the definition with data from this emitter instance
		pdefinition->Set_Render_Mode (Get_Render_Mode());
		pdefinition->Set_Frame_Mode (Get_Frame_Mode());
		pdefinition->Set_Name (Get_Name ());
		pdefinition->Set_Lifetime (Get_Lifetime ());
		pdefinition->Set_Future_Start_Time (Get_Future_Start_Time());
		pdefinition->Set_Emission_Rate (Get_Emission_Rate ());
		pdefinition->Set_Max_Emissions (Get_Max_Particles ());
		pdefinition->Set_Fade_Time (Get_Fade_Time ());
		pdefinition->Set_Gravity (0);
		pdefinition->Set_Elasticity (0);
		pdefinition->Set_Velocity (Get_Start_Velocity ());
		pdefinition->Set_Acceleration (Get_Acceleration ());
		pdefinition->Set_Burst_Size (Get_Burst_Size ());
		pdefinition->Set_Outward_Vel (Get_Outwards_Vel ());
		pdefinition->Set_Vel_Inherit (Get_Velocity_Inherit ());
		pdefinition->Set_Shader (Get_Shader ());
		
		//
		//	Pass the creation volume onto the definition
		//
		Vector3Randomizer *randomizer = Get_Creation_Volume ();
		pdefinition->Set_Creation_Volume (randomizer);

		//
		//	Pass the velocity randomizer onto the definition
		//
		randomizer = Get_Velocity_Random ();
		pdefinition->Set_Velocity_Random (randomizer);

		//
		//	Pass the color keyframes onto the definition
		//
		ParticlePropertyStruct<Vector3> colors;
		Get_Color_Key_Frames (colors);
		pdefinition->Set_Color_Keyframes (colors);
		if (colors.KeyTimes != NULL) delete [] colors.KeyTimes;
		if (colors.Values != NULL) delete [] colors.Values;

		//
		//	Pass the opacity keyframes onto the definition
		//
		ParticlePropertyStruct<float> opacities;
		Get_Opacity_Key_Frames (opacities);
		pdefinition->Set_Opacity_Keyframes (opacities);
		if (opacities.KeyTimes != NULL) delete [] opacities.KeyTimes;
		if (opacities.Values != NULL) delete [] opacities.Values;

		//
		//	Pass the size keyframes onto the definition
		//
		ParticlePropertyStruct<float> sizes;
		Get_Size_Key_Frames (sizes);
		pdefinition->Set_Size_Keyframes (sizes);
		if (sizes.KeyTimes != NULL) delete [] sizes.KeyTimes;
		if (sizes.Values != NULL) delete [] sizes.Values;

		//
		//	Pass the rotation keyframes onto the definition
		//
		ParticlePropertyStruct<float> rotations;
		Get_Rotation_Key_Frames (rotations);
		pdefinition->Set_Rotation_Keyframes (rotations, Get_Initial_Orientation_Random());
		if (rotations.KeyTimes != NULL) delete [] rotations.KeyTimes;
		if (rotations.Values != NULL) delete [] rotations.Values;

		//
		//	Pass the frame keyframes onto the definition
		//
		ParticlePropertyStruct<float> frames;
		Get_Frame_Key_Frames (frames);
		pdefinition->Set_Frame_Keyframes (frames);
		if (frames.KeyTimes != NULL) delete [] frames.KeyTimes;
		if (frames.Values != NULL) delete [] frames.Values;

		//
		//	Pass the blur time keyframes onto the definition
		//
		ParticlePropertyStruct<float> blur_times;
		Get_Blur_Time_Key_Frames (blur_times);
		pdefinition->Set_Blur_Time_Keyframes (blur_times);
		if (blur_times.KeyTimes != NULL) delete [] blur_times.KeyTimes;
		if (blur_times.Values != NULL) delete [] blur_times.Values;


		//
		// Set up the line parameters 
		//
		pdefinition->Set_Line_Texture_Mapping_Mode(Get_Line_Texture_Mapping_Mode());
		pdefinition->Set_Merge_Intersections(Is_Merge_Intersections());
		pdefinition->Set_Freeze_Random(Is_Freeze_Random());
		pdefinition->Set_Disable_Sorting(Is_Sorting_Disabled());
		pdefinition->Set_End_Caps(Are_End_Caps_Enabled());
		pdefinition->Set_Subdivision_Level(Get_Subdivision_Level());
		pdefinition->Set_Noise_Amplitude(Get_Noise_Amplitude());
		pdefinition->Set_Merge_Abort_Factor(Get_Merge_Abort_Factor());
		pdefinition->Set_Texture_Tile_Factor(Get_Texture_Tile_Factor());
		pdefinition->Set_UV_Offset_Rate(Get_UV_Offset_Rate());

	}

	// Return a pointer to the new definition
	return pdefinition;
}

