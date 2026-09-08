// cl: /G7 /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression
#include "rendobj.h"
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

void ParticleEmitterClass::Create_New_Particles(const Quaternion & curr_quat, const Vector3 & curr_orig)
{
   Quaternion quat;
   Vector3 orig;

   // The emit remainder from the previous interval (the time remaining in
	// the previous interval when the last particle was emitted) is added to
	// the size of the current frame to yield the time currently available
	// for emitting particles.
	unsigned int frametime = WW3D::Get_Frame_Time();
	// Since the particles are written into a wraparound buffer, we can take the time modulo a time
	// constant which represents the time it takes to fill up the entire buffer with new particles.
	// We will do this so we don't run into performance problems with very large frame times.
	if (frametime > 100 * EmitRate) {	// If the loop will run over 100 times
		unsigned int buf_size = Buffer->Get_Buffer_Size();
		unsigned int gcd = Greatest_Common_Divisor(buf_size, BurstSize);
		unsigned int bursts = buf_size / gcd;
		unsigned int cycle_time = EmitRate * bursts;
		if (cycle_time > 1) {
			frametime = frametime % cycle_time;
		} else {
			frametime = 1;
		}
	}

	EmitRemain += frametime;

	// The interpolation factor (0: start of interval: 1: end of interval).
   // Possibly negative at this point, but after the delta is added to it, it
   // will be positive.
	float fl_frametime = (float)frametime;
   float alpha = 1 - ((float)EmitRemain / fl_frametime);
   float d_alpha = (float)EmitRate / fl_frametime;

   // Setup the slerp between the two quaternions.
   SlerpInfoStruct slerp_info;
   Slerp_Setup(PrevQ, curr_quat, &slerp_info);

   // Find the velocity of the emitter (for velocity inheritance).
   if (VelInheritFactor) {
      InheritedWorldSpaceEmitterVel = (curr_orig - PrevOrig) * (VelInheritFactor / fl_frametime);
   } else {
      InheritedWorldSpaceEmitterVel.Set(0.0, 0.0, 0.0);
   }

   for (; EmitRemain > EmitRate;) {
      EmitRemain -= EmitRate;
      alpha += d_alpha;
      quat = Cached_Slerp(PrevQ, curr_quat, alpha, &slerp_info);
      Vector3::Lerp(PrevOrig, curr_orig, alpha, &orig);

      unsigned int age = WW3D::Get_Sync_Time() - EmitRemain;
      unsigned int burst_size = BurstSize;
      if (OneTimeBurst) {
         burst_size = OneTimeBurstSize;
         OneTimeBurst = false;
      }

      if ( ParticlesLeft > 0 ) {
         if (burst_size > (unsigned int)ParticlesLeft) {
            burst_size = (unsigned int)ParticlesLeft;
            ParticlesLeft = 0;
         } else {
            ParticlesLeft -= burst_size;
         }
         if ( ParticlesLeft <= 0 ) {
            IsComplete = true;
         }
      }

      for (unsigned int i = 0; i < burst_size; i++) {
         Initialize_Particle(Buffer->Add_Uninitialized_New_Particle(), age, quat, orig);
      }

      if (IsComplete) break;
   }
}
