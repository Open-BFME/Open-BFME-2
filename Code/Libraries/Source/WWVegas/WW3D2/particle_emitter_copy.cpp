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


// Direct game allocator-backed duplication at AC4C70; imported _strdup has a different ABI binding.
extern "C" char * __cdecl strdup(const char *);
// Full486-byte copy constructor; RET4 at5A1713. Base-object unwind action independently verified.
ParticleEmitterClass::ParticleEmitterClass(const ParticleEmitterClass & src) :
	RenderObjClass(src),
	EmitRate(src.EmitRate),
	BurstSize(src.BurstSize),
	OneTimeBurstSize(src.OneTimeBurstSize),
	OneTimeBurst(src.OneTimeBurst),
	PosRand(src.PosRand ? src.PosRand->Clone() : NULL),
	BaseVel(src.BaseVel),
	VelRand(src.VelRand ? src.VelRand->Clone() : NULL),
	OutwardVel(src.OutwardVel),
	VelInheritFactor(src.VelInheritFactor),
	EmitRemain(src.EmitRemain),
	PrevQ(src.PrevQ),
	PrevOrig(src.PrevOrig),
	Active(true),	// default to on
	FirstTime(true),
	BufferSceneNeeded(true),
	ParticlesLeft(src.ParticlesLeft),
	MaxParticles(src.MaxParticles),
	IsComplete(false),
	NameString(::strdup (src.NameString)),
	UserString(::strdup (src.UserString)),
	RemoveOnComplete(src.RemoveOnComplete),
	IsInScene(false),
	GroupID(0),
	Buffer(NULL),
	IsInvisible(src.IsInvisible)
{
	Buffer = (ParticleBufferClass *) src.Buffer->Clone();
	Buffer->Set_Emitter(this);
	SET_REF_OWNER( Buffer );
}


