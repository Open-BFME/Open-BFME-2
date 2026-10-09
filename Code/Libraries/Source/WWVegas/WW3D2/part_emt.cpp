// cl: /DBFME_RENDEROBJ_SIZE_LOD /G7 /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// Retail Release_Ref at 0x005D1A7D uses dec-dword under /G7.
// Parse its refcount inlines with size optimization, preserving other headers.
#include "wwstring.h"
#pragma optimize("t", off)
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
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
#include "texture.h"
#include "part_ldr.h"


// Global variable which is only used to communicate the worldspace emitter
// velocity from ParticleEmitterClass::Create_New_Particles() to
// ParticleEmitterClass::Initialize_Particle(), for velocity inheritance.
Vector3 InheritedWorldSpaceEmitterVel;

// This debug setting disables particles from being generated
bool ParticleEmitterClass::DebugDisable = false;

// This is used to set the global behavior of emitters...
// Should they be removed from the scene when they complete their
// emissions, or should they stay in the scene.  (For editing purposes)
// (gth) 09/17/2000 - particle emitters now have a local RemoveOnComplete flag
// which is initialized to the state of DefaultRemoveOnComplete.
bool ParticleEmitterClass::DefaultRemoveOnComplete = true;


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
	NameString(::_strdup ("ParticleEmitter")),
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
	NameString(::_strdup (src.NameString)),
	UserString(::_strdup (src.UserString)),
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


// ?ParticleEmitterClass::operator= present-unmatched
ParticleEmitterClass & ParticleEmitterClass::operator = (const ParticleEmitterClass & that)
{
	RenderObjClass::operator = (that);

	if (this != &that) {
		assert(0);	// TODO: if you hit this assert, please implement me !!!;-)
	}

	return * this;
}


ParticleEmitterClass::~ParticleEmitterClass(void)
{
	Buffer->Emitter_Is_Dead();
	Buffer->Release_Ref();

	if (PosRand != NULL) {
		delete PosRand;
		PosRand = NULL;
	}

	if (VelRand != NULL) {
		delete VelRand;
		VelRand = NULL;
	}

	if (NameString != NULL) {
		::free (NameString);
		NameString = NULL;
	}

	if (UserString != NULL) {
		::free (UserString);
		UserString = NULL;
	}

	return ;
}


ParticleEmitterClass *
// ?ParticleEmitterClass::Create_From_Definition present-unmatched
ParticleEmitterClass::Create_From_Definition (const ParticleEmitterDefClass &definition)
{
	// Assume failure
	ParticleEmitterClass *pemitter = NULL;

	// Attempt to load the texture for this emitter
	const char *ptexture_filename = definition.Get_Texture_Filename ();
	TextureClass *ptexture = NULL;
	if (ptexture_filename && ptexture_filename[0]) {
		ptexture = WW3DAssetManager::Get_Instance()->Get_Texture
		(
			ptexture_filename,
			MIP_LEVELS_ALL,
			WW3D_FORMAT_UNKNOWN
		);
//			false);	// no compression for particle textures!
	}
	
	ShaderClass shader;
	definition.Get_Shader (shader);
	if (WW3DAssetManager::Get_Instance()->Get_Activate_Fog_On_Load()) {
		shader.Enable_Fog ("ParticleEmitterClass");
	}
	/*if (ptexture) {
		// If texture has an alpha channel do alpha blending instead of additive
		// (which is the default for point groups):
		srTextureIFace::Dimensions dimensions;
		ptexture->getDimensions(dimensions);
		if (dimensions.pixelFormat.aBits > 0) {
			shader = ShaderClass::_PresetAlphaSpriteShader;
		}
	}*/

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

	// release our reference to particle texture.
	if (ptexture) {
		REF_PTR_RELEASE(ptexture);
		ptexture = 0;
	}

	// Return a pointer to the new emitter
	return pemitter;
}

RenderObjClass * ParticleEmitterClass::Clone(void) const
{
	return W3DNEW ParticleEmitterClass(*this);
}

// ?ParticleEmitterClass::Restart present-unmatched
void ParticleEmitterClass::Restart(void)
{
	// calling Start will cause all internal counters to reset
	Start();
}

// Target: emitter table 0x00BD69FC slot 25 points at this 64-byte body;
// its destructor/Clone/Get_Name and slot 26 Notify_Removed are already matched.
// The donor supplies this callback name and the Active/FirstTime/IsInScene labels.
// Native byte accesses at +0x110/+0x111/+0x129 and both ret4 paths reproduce it.
void ParticleEmitterClass::Notify_Added(SceneClass * scene)
{
	RenderObjClass::Notify_Added(scene);
	scene->Register(this,SceneClass::ON_FRAME_UPDATE);
	if (FirstTime == false) {
		Active = true;
	}
	IsInScene = true;
}

// ?ParticleEmitterClass::Notify_Removed present-unmatched
void ParticleEmitterClass::Notify_Removed(SceneClass * scene)
{
	scene->Unregister(this,SceneClass::ON_FRAME_UPDATE);
	RenderObjClass::Notify_Removed(scene);
	Active = false;
	IsInScene = false;

	//Buffer->Emitter_Is_Dead();
}

// Put particle buffer in scene if this is the first time (clunky code
// - hopefully can be rewritten more cleanly in future)...
// ?ParticleEmitterClass::On_Frame_Update present-unmatched
void ParticleEmitterClass::On_Frame_Update(void)
{
	WWPROFILE("ParticleEmitterClass::On_Frame_Update");
	if (Active && !IsComplete) {
		if (FirstTime) {

			// The particle buffer doesn't have a valid Scene yet - the emitter
			// finds out what scene it belongs to (goes up the container tree
			// until it finds a non-NULL Scene), and then adds the particle
			// buffer to it.
			if ( BufferSceneNeeded ) {
			
				if (Is_In_Scene()) {
					Buffer->Add(Scene);
					BufferSceneNeeded = false;
				} else {
					return;
				}

			}
			BufferSceneNeeded = false;

			// Initialize previous transform:
			PrevQ = Build_Quaternion(Get_Transform());
			PrevOrig = Get_Transform().Get_Translation();

			FirstTime = false;
		}
	}

	if (Is_Complete()) {
		if (Is_In_Scene() && Is_Remove_On_Complete_Enabled()) {
			Scene->Register(this,SceneClass::RELEASE);
		}
	}
}

// ?ParticleEmitterClass::Reset present-unmatched
void ParticleEmitterClass::Reset(void)
{
	// Note:  This flag needs to be set first thing, otherwise
	// getting the transform will result in an 'update_x' call
	// which in turn results in a 'Set_Animation_Hidden' call, which
	// in turn will cause the Update_Visibilty function to call
	// Start().  This won't cause a stack overflow like in Start
	// but it would do some extra work.
	Active = true;

	// Initialize previous transform:
	PrevQ = Build_Quaternion(Get_Transform());
	PrevOrig = Get_Transform().Get_Translation();

	// Reset the number of particles to emit
	ParticlesLeft = MaxParticles;
	EmitRemain = 0;	
	IsComplete = false;
}

// ?ParticleEmitterClass::Start present-unmatched
void ParticleEmitterClass::Start(void)
{
	// Note:  This flag needs to be set first thing, otherwise
	// getting the transform will result in an 'update_x' call
	// which in turn results in a 'Set_Animation_Hidden' call, which
	// in turn will cause the Update_Visibilty function to call
	// this method.  And then... Stack Overflow!  ;)
	Active = true;

	// Initialize previous transform:
	PrevQ = Build_Quaternion(Get_Transform());
	PrevOrig = Get_Transform().Get_Translation();

	// Reset the number of particles to emit (if necessary)
	if (IsComplete == true) {
		ParticlesLeft = MaxParticles;
		IsComplete = false;
	}

	// This is to keep track of particles so that
	// the line segments can start and stop properly
	GroupID++;
	Buffer->Set_Current_GroupID(GroupID);
}


// ?ParticleEmitterClass::Stop present-unmatched
void ParticleEmitterClass::Stop(void)
{
	Active = false;	
}


// ParticleEmitterClass::Is_Stopped: defined in part_emt_is_stopped.cpp (its row's unit).


// ?ParticleEmitterClass::Set_Position_Randomizer present-unmatched
void ParticleEmitterClass::Set_Position_Randomizer(Vector3Randomizer *rand)
{
	if (PosRand) {
		delete PosRand;
		PosRand =NULL;
	}
	PosRand = rand;
}


// ?ParticleEmitterClass::Set_Velocity_Randomizer present-unmatched
void ParticleEmitterClass::Set_Velocity_Randomizer(Vector3Randomizer *rand)
{
	if (VelRand) {
		delete VelRand;
		VelRand =NULL;
	}
	VelRand = rand;
	if (VelRand) {
		VelRand->Scale(0.001f);	// Convert from seconds to ms
	}
}


// ?ParticleEmitterClass::Get_Creation_Volume present-unmatched
inline Vector3Randomizer *ParticleEmitterClass::Get_Creation_Volume (void) const
{
	Vector3Randomizer *randomizer = NULL;
	if (PosRand != NULL) {
		randomizer = PosRand->Clone ();
		//randomizer->Scale (1000.0F);
	}
	return randomizer;
}


inline Vector3Randomizer *ParticleEmitterClass::Get_Velocity_Random (void) const
{
	Vector3Randomizer *randomizer = NULL;
	if (VelRand != NULL) {
		randomizer = VelRand->Clone ();
		randomizer->Scale (1000.0F);
	}
	return randomizer;
}

void ParticleEmitterClass::Set_Base_Velocity(const Vector3& base_vel)
{
	BaseVel = base_vel * 0.001f;	// Convert from seconds to ms
}


// ?ParticleEmitterClass::Set_Outwards_Velocity present-unmatched
void ParticleEmitterClass::Set_Outwards_Velocity(float out_vel)
{
	OutwardVel = out_vel * 0.001f;	// Convert from seconds to ms
}


// ?ParticleEmitterClass::Set_Velocity_Inheritance_Factor present-unmatched
void ParticleEmitterClass::Set_Velocity_Inheritance_Factor(float inh_factor)
{
	VelInheritFactor = inh_factor;
}


// Emit particles (put in particle buffer). This is called by the particle
// buffer On_Frame_Update() function to avoid order dependence.
// Owned by particle_emitter_emit.cpp.


// Collision sphere is a point - emitter emits also when not visible, so this
// is only important to avoid affecting the collision spheres of composite
// objects into which the emitter is inserted.
// ?ParticleEmitterClass::Update_Cached_Bounding_Volumes present-unmatched
void ParticleEmitterClass::Update_Cached_Bounding_Volumes(void) const
{ 
	CachedBoundingSphere.Init(Get_Position(),0.0); 
	CachedBoundingBox.Center = Get_Position();
	CachedBoundingBox.Extent.Set(0,0,0);
	Validate_Cached_Bounding_Volumes();
}


// Note that creation location and velocity are in local coordinates, so new
// particles need to be transformed into worldspace. It is important to get
// the correct transform at the exact time of particle creation (for frame-
// rate independence), so the current emitter transform is calculated by
// time-based interpolation between the transforms at the beginning and end
// of the current frame. This interpolation is performed via quaternion-
// slerping the orientation and lerping the origin.
// ?ParticleEmitterClass::Create_New_Particles present-unmatched
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
	// InheritedWorldSpaceEmitterVel is a global variable which is only used
	// to pass this into the following Initialize_Particle() calls without
	// having to set it as an argument for each call.
	if (VelInheritFactor) {
		InheritedWorldSpaceEmitterVel = (curr_orig - PrevOrig) * (VelInheritFactor / fl_frametime);
	} else {
		InheritedWorldSpaceEmitterVel.Set(0.0, 0.0, 0.0);
	}
	
   for (; EmitRemain > EmitRate;) {
		
		// Calculate the new remainder.
		EmitRemain -= EmitRate;

      // Interpolate the start and end transforms to find the transform at
      // the moment of particle creation.
      alpha += d_alpha;
      quat = Cached_Slerp(PrevQ, curr_quat, alpha, &slerp_info);
      Vector3::Lerp(PrevOrig, curr_orig, alpha, &orig);

		// Initialize BurstSize new particles with the given age and emitter
		// transform (expressed as a quaternion and origin vector), and add it
		// to the particle buffer's new particle vector.
		unsigned int age = WW3D::Get_Sync_Time() - EmitRemain;
		unsigned int burst_size = BurstSize;
		if (OneTimeBurst) {
			burst_size = OneTimeBurstSize;
			OneTimeBurst = false;
		}

		if ( ParticlesLeft > 0 ) {			// if we are counting,
			if (burst_size > (unsigned int)ParticlesLeft) {
				burst_size = (unsigned int)ParticlesLeft;
				ParticlesLeft = 0;
			} else {
				ParticlesLeft -= burst_size;
			}
			if ( ParticlesLeft <= 0 ) {	// count and if done
				IsComplete = true;			// stop
			}
		}

		for (unsigned int i = 0; i < burst_size; i++) {
			Initialize_Particle(Buffer->Add_Uninitialized_New_Particle(), age, quat, orig);
		}

		if (IsComplete) break;
	}
}


// Initialize one new particle at the given NewParticleStruct address, with
// the given age and emitter transform (expressed as a quaternion and origin
// vector). (must check if address is NULL).
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


// Build_Definition: BFME2 retail 0x001A2B00, owned by
// particle_emitter_build_definition.cpp with the native texture/string ABI.


WW3DErrorType
// ?ParticleEmitterClass::Save present-unmatched
ParticleEmitterClass::Save (ChunkSaveClass &chunk_save) const
{
	// Assume error
	WW3DErrorType ret_val = WW3D_ERROR_SAVE_FAILED;

	// Build a definition from this emitter instance, and save it
	// to the chunk.
	ParticleEmitterDefClass *pdefinition = Build_Definition ();
	if (pdefinition != NULL) {
		ret_val = pdefinition->Save_W3D (chunk_save);
	}

	// Return the WW3DErrorType return code
	return ret_val;
}


// ParticleEmitterClass::Set_Name: defined in ParticleEmitterSetName.cpp (its row's unit).


// ParticleEmitterClass::Update_On_Visibilty: defined in particle_emitter_update_visibility.cpp (its row's unit).


void
ParticleEmitterClass::Add_Dependencies_To_List
(
	DynamicVectorClass<StringClass> &file_list,
	bool textures_only
)
{
	//
	// Get the texture the emitter is using and add it to our list
	//
	TextureClass *texture = Get_Texture ();
	if (texture != NULL) {
		file_list.Add (texture->Get_Full_Path ());
		REF_PTR_RELEASE(texture);
	}

	// Allow the base class to process this call (extremely important)
	RenderObjClass::Add_Dependencies_To_List (file_list, textures_only);
	return ;
}
