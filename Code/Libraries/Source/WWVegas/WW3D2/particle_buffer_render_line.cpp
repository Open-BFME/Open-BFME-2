// cl: /EHsc /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
#define Matrix4x4 Matrix4
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
 *                     $Archive:: /Commando/Code/ww3d2/part_buf.cpp       $* 
 *                                                                         * 
 *                      $Author:: Jani_p                                  $* 
 *                                                                         * 
 *                     $Modtime:: 9/07/01 12:57p                          $* 
 *                                                                         * 
 *                    $Revision:: 20                                      $* 
 *                                                                         * 
 *-------------------------------------------------------------------------* 
 * Functions:                                                              * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#include "../../../../../reference/shims/bfmesegline/rendobj.h" // independently verified indexed-factor prefix and 0xC4 base size
#include "part_buf.h"
#include "part_emt.h"
#include "ww3d.h"
#include "rinfo.h"
#include "scene.h"
#include "camera.h"
#include "predlod.h"
#include "pot.h"
#include "bound.h"
#include "simplevec.h"
#include "sphere.h"
#include "wwprofile.h"
#include <limits.h>
#include "vp.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "vector3.h"

// Donor predicate is inlined here so this TU retains the original call graph.
inline int ParticleBufferClass::Is_Freeze_Random(void) const
{
 if (LineRenderer != NULL) return LineRenderer->Is_Freeze_Random();
 return false;
}
// Full retail body: RVA 0x1AE4D0 through RET 4 at 0x5AEC28 (1883 bytes).
// /EHsc preserves the five-state static-vector initialization unwind map.
void ParticleBufferClass::Render_Line(RenderInfoClass & rinfo)
{

	LineRenderer->Set_Freeze_Random(Is_Freeze_Random());

	// Look up the array to use
	int pingpong = 0;
	if (PingPongPosition) {
		pingpong = WW3D::Get_Frame_Count() & 0x1;
	}

	// Unroll the circular buffer while skipping LOD'd particles
	static SimpleDynVecClass<Vector3> tmp_points;
	static SimpleDynVecClass<Vector4> tmp_diffuse;
	static SimpleDynVecClass<unsigned char> tmp_id;

	Vector3 * positions = Position[pingpong]->Get_Array();
	Vector4 * diffuse = 0;
	Vector4 default_diffuse(0, 0, 0, 0);
	unsigned char *ids = GroupID->Get_Array();
	Combine_Color_And_Alpha();
	if (Diffuse) {		
		diffuse = Diffuse->Get_Array();
	} else {
		default_diffuse.Set(ColorKeyFrameValues[0].X, ColorKeyFrameValues[0].Y, ColorKeyFrameValues[0].Z,
								  AlphaKeyFrameValues[0]);
	}

	unsigned int sub1_end;		// End of subrange 1.
	unsigned int sub2_start;	// Start of subrange 2.
	unsigned int i;				// Loop index.

	if ((Start < End) || ((Start == End) && NonNewNum ==0)) {
		sub1_end = End;
		sub2_start = End;
	} else {
		sub1_end = MaxNum;
		sub2_start = 0;
	}

	tmp_points.Delete_All(false);
	tmp_diffuse.Delete_All(false);
	tmp_id.Delete_All(false);

	Vector4 *last_color = &default_diffuse;
	unsigned char last_id = 0;

	for (i = Start; i < sub1_end; i++) {
		if (PermutationArray[i & 0xF] >= DecimationThreshold) {
			tmp_points.Add(positions[i]);
			last_color = diffuse ? &diffuse[i] : &default_diffuse;
			tmp_diffuse.Add(*last_color);
			last_id = ids[i];
			tmp_id.Add(last_id);
		}
	}
	
	for (i = sub2_start; i < End; i++) {
		if (PermutationArray[i & 0xF] >= DecimationThreshold) {
			tmp_points.Add(positions[i]);
			last_color = diffuse ? &diffuse[i] : &default_diffuse;
			tmp_diffuse.Add(*last_color);
			last_id = ids[i];
			tmp_id.Add(last_id);
		}
	}

	// add in the emitter's position too for the source	
	if (Emitter && !Emitter->Is_Stopped() && (last_id == CurrentGroupID)) {
		tmp_points.Add(Emitter->Get_Position());
		// it has the color of the last point
		tmp_diffuse.Add(*last_color);
		tmp_id.Add(last_id);
	}	

	// If we got any points, render them
	if (tmp_points.Count() > 0) {
		SphereClass bounding_sphere;
		Get_Obj_Space_Bounding_Sphere(bounding_sphere);

		// Draw line segments only if they are in the same group
		int count = tmp_points.Count();
		int start = 0;
		int end = 0;		

		while (end < count) {
			// detect contiguous runs of IDs
			while ( (end < count) && (tmp_id[start] == tmp_id[end])) {
				end++;
			}

			// render from start, excluding end
			if (end - start > 1) {
				LineRenderer->Render(rinfo,
											Transform,
											end - start,
											&(tmp_points[start]),
											bounding_sphere,
											&(tmp_diffuse[start]));
			}
			start = end;
		}
	}
}

