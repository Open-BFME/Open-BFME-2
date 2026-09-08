// cl: /G7 /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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


// Direct game string allocation helper; imported CRT _strdup is a different binding.
extern "C" char * __cdecl strdup(const char *);
// Full881-byte emitter initialization at1A1070; RET74 at5A13DE.
// Both base-object and unfinished buffer-allocation unwind actions match retail.
ParticleEmitterClass::ParticleEmitterClass(float emit_rate, unsigned int burst_size,
			Vector3Randomizer *pos_rnd, Vector3 base_vel, Vector3Randomizer *vel_rnd, float out_vel,
			float vel_inherit_factor, 
			ParticlePropertyStruct<Vector3> &color,
			ParticlePropertyStruct<float> &opacity, 
			ParticlePropertyStruct<float> &size,
			ParticlePropertyStruct<float> &rotation, float orient_rnd,
			ParticlePropertyStruct<float> &frames,
			ParticlePropertyStruct<float> &blur_times,
			Vector3 accel, float max_age, float future_start, TextureClass *tex, ShaderClass shader, int max_particles,
			int max_buffer_size, bool pingpong,int render_mode,int frame_mode,
			const W3dEmitterLinePropertiesStruct * line_props
) :
	RenderObjClass(),
	EmitRate(emit_rate > 0.0f ? (unsigned int)(1000.0f / emit_rate) : 1000U),
	BurstSize(burst_size != 0	? burst_size : 1),
	OneTimeBurstSize(1),
	OneTimeBurst(false),
	PosRand(pos_rnd),
	BaseVel(base_vel * 0.001f),
	VelRand(vel_rnd),
	OutwardVel(out_vel * 0.001f),
	VelInheritFactor(vel_inherit_factor),
	EmitRemain(0U),
	PrevQ(true),
	PrevOrig(0.0, 0.0, 0.0),
	Active(false),
	FirstTime(true),
	BufferSceneNeeded(true),
	ParticlesLeft(max_particles),
	MaxParticles(max_particles),
	IsComplete(false),
	NameString(::strdup ("ParticleEmitter")),
	UserString(NULL),
	RemoveOnComplete(DefaultRemoveOnComplete),
	IsInScene(false),
	GroupID(0),
	Buffer(NULL),
	IsInvisible(false)
{
	max_age		= max_age	> 	0.0f ? max_age : 1.0f;
	VelRand->Scale(0.001f);

	// The maximum number of particles is determined by the emission rate, burst size and lifetime.
	// However, it is capped both by the particle cap and by the maximum buffer size, if these are
	// active.
	int max_num = BurstSize * emit_rate * (max_age + 1);
	if (max_particles > 0) max_num = MIN(max_num, max_particles);
	if (max_buffer_size > 0) max_num = MIN(max_num, max_buffer_size);
	max_num = MAX(max_num, 2);	// max_num of 1 causes problems

	Buffer = W3DNEW ParticleBufferClass(this, max_num, color, opacity, size, rotation, orient_rnd,
		frames, blur_times, accel/1000000.0f,max_age, future_start, tex, shader, pingpong, render_mode, frame_mode,
		line_props);
	SET_REF_OWNER( Buffer );
}


