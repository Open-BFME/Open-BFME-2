// cl: /Ireference/shims/bfmeparticlequat /G7 /Ireference/shims/bfme2renderobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
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

#include "rendobj.h"
#include "quat.h"
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


extern Vector3 InheritedWorldSpaceEmitterVel;
void ParticleEmitterClass::Initialize_Particle(NewParticleStruct * newpart,
   unsigned int timestamp, const Quaternion & quat, const Vector3 & orig)
{
   // Set time stamp.
	newpart->TimeStamp = timestamp;

   // Set starting (random) local position.
	Vector3 rand_pos;
	if (PosRand) {
		PosRand->Get_Vector(rand_pos);
	} else {
		rand_pos.Set(0.0, 0.0, 0.0);
	}

	// Transform position to worldspace, using the transform at moment of
   // particle creation.
	newpart->Position = quat.Rotate_Vector(rand_pos) + orig;

	// Set (random) local velocity.
	Vector3 rand_vel;
	if (VelRand) {
		VelRand->Get_Vector(rand_vel);
	} else {
		rand_vel.Set(0.0, 0.0, 0.0);
	}

	// Add outwards velocity to emitterspace velocity
	if (OutwardVel) {
		// Find vector pointing outwards (from origin to creation position)
		Vector3 outwards;
		float pos_l2 = rand_pos.Length2();
		if (pos_l2) {
			outwards = rand_pos * (OutwardVel * WWMath::Inv_Sqrt(pos_l2));
		} else {
			outwards.X = OutwardVel;
			outwards.Y = 0.0f;
			outwards.Z = 0.0f;
		}

		rand_vel += outwards;
	}

	// Add base velocity to emitterspace velocity
	rand_vel += BaseVel;

	// Rotate velocity to worldspace and add emitter's inherited velocity.
	newpart->Velocity = InheritedWorldSpaceEmitterVel + quat.Rotate_Vector(rand_vel);

	// GroupID
	newpart->GroupID = GroupID;	
}
