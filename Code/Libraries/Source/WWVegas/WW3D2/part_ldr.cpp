// cl: /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the optimization
// state of the first function that needs it; retail links one copy, the /O1 body at
// 0x00001423. This unemitted anchor makes this unit's copy that body. auto_inline(off)
// keeps the iterator out of line: without it the /O2 Copy_Emitter_Property_Struct
// <Vector3> inlines it and loses retail's call to ??_H.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma auto_inline(off)
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#pragma auto_inline(on)
// Select the BFME2 legacy kernel32 import declarations before reference headers.

// BFME 2 has no W3D memory pools (see Code/Libraries/Source/WWVegas/WWLib/always.h).
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#include <sweep/winbase_shim.h>

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
// Particle system loader adapted from Generals Zero Hour for BFME2.
// Keyframe writers explicitly canonicalize their final bool result to match
// the retail compiler's test/setne sequence; the donor write order is preserved.
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
// Retail frees these polymorphic objects through the virtual destructor with
// flag 0 plus the global operator delete -- what ::delete emits.
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) {	\
		::delete pointer; \
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
// _ParticleEmitterLoader: defined in particle_emitter_read_props.cpp.

//	This array is declared in "W3D_File.H"
const char *EMITTER_TYPE_NAMES[EMITTER_TYPEID_COUNT] = 
{
	"Default"
};


///////////////////////////////////////////////////////////////////////////////////
//
//	ParticleEmitterDefClass
//
// ?ParticleEmitterDefClass::ParticleEmitterDefClass present-unmatched
ParticleEmitterDefClass::ParticleEmitterDefClass (void)
	:	m_pName (NULL),
		m_Version (0L),
		m_pUserString (NULL),	  
		m_iUserType (EMITTER_TYPEID_DEFAULT),
		m_InitialOrientationRandom (0),
		m_pCreationVolume (NULL),
		m_pVelocityRandomizer (NULL)
{
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_InfoV2, 0, sizeof (m_InfoV2));	
	::memset (&m_ExtraInfo, 0, sizeof (m_ExtraInfo));

	::memset (&m_ColorKeyframes, 0, sizeof (m_ColorKeyframes));
	::memset (&m_OpacityKeyframes, 0, sizeof (m_OpacityKeyframes));
	::memset (&m_SizeKeyframes, 0, sizeof (m_SizeKeyframes));
	::memset (&m_RotationKeyframes, 0, sizeof (m_RotationKeyframes));
	::memset (&m_FrameKeyframes, 0, sizeof (m_FrameKeyframes));
	::memset (&m_BlurTimeKeyframes, 0, sizeof (m_BlurTimeKeyframes));
	::memset (&m_LineProperties, 0, sizeof (m_LineProperties));
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	ParticleEmitterDefClass
//
// ?ParticleEmitterDefClass::ParticleEmitterDefClass present-unmatched
ParticleEmitterDefClass::ParticleEmitterDefClass (const ParticleEmitterDefClass &src)
	:	m_pName (NULL),
		m_Version (0L),
		m_pUserString (NULL),	  
		m_iUserType (EMITTER_TYPEID_DEFAULT),
		m_InitialOrientationRandom (src.m_InitialOrientationRandom),
		m_pCreationVolume (NULL),
		m_pVelocityRandomizer (NULL)
{
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_InfoV2, 0, sizeof (m_InfoV2));	
	::memset (&m_ExtraInfo, 0, sizeof (m_ExtraInfo));	

	::memset (&m_ColorKeyframes, 0, sizeof (m_ColorKeyframes));
	::memset (&m_OpacityKeyframes, 0, sizeof (m_OpacityKeyframes));
	::memset (&m_SizeKeyframes, 0, sizeof (m_SizeKeyframes));
	::memset (&m_RotationKeyframes, 0, sizeof (m_RotationKeyframes));
	::memset (&m_FrameKeyframes, 0, sizeof (m_FrameKeyframes));
	::memset (&m_BlurTimeKeyframes, 0, sizeof (m_BlurTimeKeyframes));
	::memset (&m_LineProperties, 0, sizeof (m_LineProperties));

	(*this) = src;
	return ;
}


// ~ParticleEmitterDefClass is owned by
// particle_emitter_definition_destructor.cpp; declared in part_ldr.h.


///////////////////////////////////////////////////////////////////////////////////
//
//	ParticleEmitterDefClass
//
const ParticleEmitterDefClass &
ParticleEmitterDefClass::operator= (const ParticleEmitterDefClass &src)
{
	//
	//	Copy the user structures
	//
	Set_Name (src.Get_Name ());
	Set_User_String (src.Get_User_String ());
	Set_User_Type (src.Get_User_Type ());
	m_Version = src.m_Version;

	//
	//	Copy the information structures
	//
	::memcpy (&m_Info, &src.m_Info, sizeof (m_Info));
	::memcpy (&m_InfoV2, &src.m_InfoV2, sizeof (m_InfoV2));
	::memcpy (&m_ExtraInfo, &src.m_ExtraInfo, sizeof (m_ExtraInfo));
	::memcpy (&m_LineProperties, &src.m_LineProperties, sizeof(m_LineProperties));

	//
	//	Copy the keyframes
	//
	Free_Props ();
	::Copy_Emitter_Property_Struct (m_ColorKeyframes, src.m_ColorKeyframes);
	::Copy_Emitter_Property_Struct (m_OpacityKeyframes, src.m_OpacityKeyframes);
	::Copy_Emitter_Property_Struct (m_SizeKeyframes, src.m_SizeKeyframes);
	::Copy_Emitter_Property_Struct (m_RotationKeyframes, src.m_RotationKeyframes);
	::Copy_Emitter_Property_Struct (m_FrameKeyframes, src.m_FrameKeyframes);
	::Copy_Emitter_Property_Struct (m_BlurTimeKeyframes, src.m_BlurTimeKeyframes);
	m_InitialOrientationRandom = src.m_InitialOrientationRandom;

	//
	//	Create the randomizers
	//
	SAFE_DELETE (m_pCreationVolume);
	SAFE_DELETE (m_pVelocityRandomizer);
	m_pCreationVolume			= Create_Randomizer (m_InfoV2.CreationVolume);
	m_pVelocityRandomizer	= Create_Randomizer (m_InfoV2.VelRandom);
	return (*this);
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Free_Props
//
void
ParticleEmitterDefClass::Free_Props (void)
{
	m_ColorKeyframes.NumKeyFrames = 0;
	m_OpacityKeyframes.NumKeyFrames = 0;
	m_SizeKeyframes.NumKeyFrames = 0;
	m_RotationKeyframes.NumKeyFrames = 0;
	m_FrameKeyframes.NumKeyFrames = 0;
	m_BlurTimeKeyframes.NumKeyFrames = 0;

	SAFE_DELETE_ARRAY (m_ColorKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_ColorKeyframes.Values);
	SAFE_DELETE_ARRAY (m_OpacityKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_OpacityKeyframes.Values);
	SAFE_DELETE_ARRAY (m_SizeKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_SizeKeyframes.Values);
	SAFE_DELETE_ARRAY (m_RotationKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_RotationKeyframes.Values);
	SAFE_DELETE_ARRAY (m_FrameKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_FrameKeyframes.Values);
	SAFE_DELETE_ARRAY (m_BlurTimeKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_BlurTimeKeyframes.Values);

	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Velocity_Random
//
void							
ParticleEmitterDefClass::Set_Velocity_Random (Vector3Randomizer *randomizer)
{
	SAFE_DELETE (m_pVelocityRandomizer);
	m_pVelocityRandomizer = randomizer;

	//
	//	Ensure our persistent structure is up-to-date so it will save correctly
	//
	if (m_pVelocityRandomizer != NULL) {
		Initialize_Randomizer_Struct (*m_pVelocityRandomizer, m_InfoV2.VelRandom);
	}

	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Creation_Volume
//
void							
ParticleEmitterDefClass::Set_Creation_Volume (Vector3Randomizer *randomizer)
{
	SAFE_DELETE (m_pCreationVolume);
	m_pCreationVolume = randomizer;

	//
	//	Ensure our persistent structure is up-to-date so it will save correctly
	//
	if (m_pCreationVolume != NULL) {
		Initialize_Randomizer_Struct (*m_pCreationVolume, m_InfoV2.CreationVolume);		
	}

	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Texture_Filename
//
void							
ParticleEmitterDefClass::Set_Texture_Filename (const char *pname)	
{ 
	::lstrcpy (m_Info.TextureFilename, pname); 
	Normalize_Filename (); 
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Normalize_Filename
//
void
ParticleEmitterDefClass::Normalize_Filename (void)
{	
	TCHAR path[MAX_PATH];
	::lstrcpy (path, m_Info.TextureFilename);

	// Find the last occurance of the directory deliminator
	LPCTSTR filename = ::strrchr (path, '\\');
	if (filename != NULL) {
		
		// Increment past the directory deliminator
		filename ++;

		// Now copy the filename protion of the path to the structure
		::lstrcpy (m_Info.TextureFilename, filename);
	}

	return ;
}




///////////////////////////////////////////////////////////////////////////////////
//
//	Initialize_To_Ver2
//
void
ParticleEmitterDefClass::Initialize_To_Ver2 (void)
{
	::memset (&m_Info, 0, sizeof (m_Info));
	::memset (&m_InfoV2, 0, sizeof (m_InfoV2));
	::memset (&m_ExtraInfo, 0, sizeof (m_ExtraInfo));
	
	//
	//	Set the version 2 values using defaults from version 1
	//
	m_InfoV2.BurstSize = 1;
	m_InfoV2.OutwardVel = 0;
	m_InfoV2.VelInherit = 0;
	W3dUtilityClass::Convert_Shader (ShaderClass::_PresetAdditiveSpriteShader, &m_InfoV2.Shader);	
	
	m_InfoV2.CreationVolume.ClassID = Vector3Randomizer::CLASSID_SOLIDBOX;
	m_InfoV2.CreationVolume.Value1 = 0;
	m_InfoV2.CreationVolume.Value2 = 0;
	m_InfoV2.CreationVolume.Value3 = 0;

	m_InfoV2.VelRandom.ClassID = Vector3Randomizer::CLASSID_SOLIDBOX;
	m_InfoV2.VelRandom.Value1 = 0;
	m_InfoV2.VelRandom.Value2 = 0;
	m_InfoV2.VelRandom.Value3 = 0;
	
	Free_Props ();
	return ;
}


// Convert_To_Ver2 is owned by particle_emitter_convert_version.cpp;
// declared in part_ldr.h.


///////////////////////////////////////////////////////////////////////////////////
//
//	Read_Header
//
extern "C" char * __cdecl strdup(const char *);







///////////////////////////////////////////////////////////////////////////////////
//
//	Create_Randomizer
//
Vector3Randomizer *
ParticleEmitterDefClass::Create_Randomizer (W3dVolumeRandomizerStruct &info)
{
	Vector3Randomizer *randomizer = NULL;
	switch (info.ClassID)
	{
		case Vector3Randomizer::CLASSID_SOLIDBOX:
			randomizer = W3DNEW Vector3SolidBoxRandomizer (Vector3 (info.Value1, info.Value2, info.Value3));
			break;

		case Vector3Randomizer::CLASSID_SOLIDSPHERE:
			randomizer = W3DNEW Vector3SolidSphereRandomizer (info.Value1);
			break;

		case Vector3Randomizer::CLASSID_HOLLOWSPHERE:
			randomizer = W3DNEW Vector3HollowSphereRandomizer (info.Value1);
			break;

		case Vector3Randomizer::CLASSID_SOLIDCYLINDER:
			randomizer = W3DNEW Vector3SolidCylinderRandomizer (info.Value1, info.Value2);
			break;		
	}

	return randomizer;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Initialize_Randomizer_Struct
//
void
ParticleEmitterDefClass::Initialize_Randomizer_Struct
(
	const Vector3Randomizer &		randomizer,
	W3dVolumeRandomizerStruct &	info
)
{
	info.ClassID = randomizer.Class_ID ();
	switch (randomizer.Class_ID ())
	{
		case Vector3Randomizer::CLASSID_SOLIDBOX:
		{
			Vector3 extents = ((Vector3SolidBoxRandomizer &)randomizer).Get_Extents ();
			info.Value1 = extents.X;
			info.Value2 = extents.Y;
			info.Value3 = extents.Z;
		}
		break;

		case Vector3Randomizer::CLASSID_SOLIDSPHERE:
			info.Value1 = ((Vector3SolidSphereRandomizer &)randomizer).Get_Radius ();
			break;

		case Vector3Randomizer::CLASSID_HOLLOWSPHERE:
			info.Value1 = ((Vector3HollowSphereRandomizer &)randomizer).Get_Radius ();
			break;

		case Vector3Randomizer::CLASSID_SOLIDCYLINDER:
			info.Value1 = ((Vector3SolidCylinderRandomizer &)randomizer).Get_Height ();
			info.Value2 = ((Vector3SolidCylinderRandomizer &)randomizer).Get_Radius ();			
			break;		
	}

	return ;
}






//////////////////////////////////////////////////////////////////////////////////
//
//	Read_Color_Keyframe
//
bool
ParticleEmitterDefClass::Read_Color_Keyframe
(
	ChunkLoadClass &	chunk_load,
	float *				key_time,
	Vector3 *			value
)
{
	bool retval = false;

	//
	//	Read the color key frame from the chunk
	//
	W3dEmitterColorKeyframeStruct key_frame = { 0 };
	if (chunk_load.Read (&key_frame, sizeof (key_frame)) == sizeof (key_frame)) {
		
		// Pass the key time to the caller
		if (key_time != NULL) {
			(*key_time) = key_frame.Time;
		}

		// Pass the oclor back to the caller
		if (value != NULL) {
			(*value) = RGBA_TO_VECTOR3 (key_frame.Color);
		}

		// Success!
		retval = true;
	}

	return retval;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Read_Opacity_Keyframe
//
bool
ParticleEmitterDefClass::Read_Opacity_Keyframe
(
	ChunkLoadClass &	chunk_load,
	float *				key_time,
	float *				value
)
{
	bool retval = false;

	//
	//	Read the key frame from the chunk
	//
	W3dEmitterOpacityKeyframeStruct key_frame = { 0 };
	if (chunk_load.Read (&key_frame, sizeof (key_frame)) == sizeof (key_frame)) {
		
		// Pass the key time to the caller
		if (key_time != NULL) {
			(*key_time) = key_frame.Time;
		}

		// Pass the value back to the caller
		if (value != NULL) {
			(*value) = key_frame.Opacity;
		}

		// Success!
		retval = true;
	}

	return retval;
}


//////////////////////////////////////////////////////////////////////////////////
//
//	Read_Size_Keyframe
//
bool
ParticleEmitterDefClass::Read_Size_Keyframe
(
	ChunkLoadClass &	chunk_load,
	float *				key_time,
	float *				value
)
{
	bool retval = false;

	//
	//	Read the key frame from the chunk
	//
	W3dEmitterSizeKeyframeStruct key_frame = { 0 };
	if (chunk_load.Read (&key_frame, sizeof (key_frame)) == sizeof (key_frame)) {
		
		// Pass the key time to the caller
		if (key_time != NULL) {
			(*key_time) = key_frame.Time;
		}

		// Pass the value back to the caller
		if (value != NULL) {
			(*value) = key_frame.Size;
		}

		// Success!
		retval = true;
	}

	return retval;
}



















///////////////////////////////////////////////////////////////////////////////////
//
//	Save_Props
//
bool
ParticleEmitterDefClass::Save_Props (ChunkSaveClass &chunk_save)
{
	// BFME returns a byte here, not WW3DErrorType.
	bool ret_val = false;

	// Begin a chunk that identifies the generic emitter settings
	if (chunk_save.Begin_Chunk (W3D_CHUNK_EMITTER_PROPS) == TRUE) {
		
		//
		//	Fill in the property struct
		//
		W3dEmitterPropertyStruct info = { 0 };
		info.ColorKeyframes		= m_ColorKeyframes.NumKeyFrames + 1;
		info.OpacityKeyframes	= m_OpacityKeyframes.NumKeyFrames + 1;
		info.SizeKeyframes		= m_SizeKeyframes.NumKeyFrames + 1;
		info.OpacityRandom		= m_OpacityKeyframes.Rand;
		info.SizeRandom			= m_SizeKeyframes.Rand;
		VECTOR3_TO_RGBA (m_ColorKeyframes.Rand, info.ColorRandom);		

		//
		// Write the property structure out to the chunk
		//
		if (chunk_save.Write (&info, sizeof (info)) == sizeof (info)) {

			//
			//	Save the keyframes
			//
			if ((Save_Color_Keyframes (chunk_save) == TRUE) &&
				 (Save_Opacity_Keyframes (chunk_save) == TRUE) &&
				 (Save_Size_Keyframes (chunk_save) == TRUE)) {

				// Success!
				ret_val = true;
			}
		}

		// End the settings chunk
		chunk_save.End_Chunk ();
	}

	// Return the success status
	return ret_val;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Save_Color_Keyframes
//
bool
// ?ParticleEmitterDefClass::Save_Color_Keyframes present-unmatched
ParticleEmitterDefClass::Save_Color_Keyframes (ChunkSaveClass &chunk_save)
{
	// Assume error
	bool ret_val = false;

	W3dEmitterColorKeyframeStruct info = { 0 };
	info.Time = 0;
	VECTOR3_TO_RGBA (m_ColorKeyframes.Start, info.Color);

	//
	// Write the starting color keyframe to the chunk
	//
	if (chunk_save.Write (&info, sizeof (info)) == sizeof (info)) {
		
		//
		// Write each of the remaining color keyframes to the chunk
		//
		int count = m_ColorKeyframes.NumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index ++) {			
			info.Time = m_ColorKeyframes.KeyTimes[index];
			VECTOR3_TO_RGBA (m_ColorKeyframes.Values[index], info.Color);
			success = (chunk_save.Write (&info, sizeof (info)) == sizeof (info));
		}

		ret_val = (success != false);
	}

	// Return the success status
	return ret_val;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Save_Opacity_Keyframes
//
bool
// ?ParticleEmitterDefClass::Save_Opacity_Keyframes present-unmatched
ParticleEmitterDefClass::Save_Opacity_Keyframes (ChunkSaveClass &chunk_save)
{
	// Assume error
	bool ret_val = false;

	W3dEmitterOpacityKeyframeStruct info = { 0 };
	info.Time = 0;
	info.Opacity = m_OpacityKeyframes.Start;

	//
	// Write the starting keyframe to the chunk
	//
	if (chunk_save.Write (&info, sizeof (info)) == sizeof (info)) {
		
		//
		// Write each of the remaining keyframes to the chunk
		//
		int count = m_OpacityKeyframes.NumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index ++) {			
			info.Time = m_OpacityKeyframes.KeyTimes[index];
			info.Opacity = m_OpacityKeyframes.Values[index];
			success = (chunk_save.Write (&info, sizeof (info)) == sizeof (info));
		}

		ret_val = (success != false);
	}

	// Return the success status
	return ret_val;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Save_Size_Keyframes
//
bool
// ?ParticleEmitterDefClass::Save_Size_Keyframes present-unmatched
ParticleEmitterDefClass::Save_Size_Keyframes (ChunkSaveClass &chunk_save)
{
	// Assume error
	bool ret_val = false;

	W3dEmitterSizeKeyframeStruct info = { 0 };
	info.Time = 0;
	info.Size = m_SizeKeyframes.Start;

	//
	// Write the starting keyframe to the chunk
	//
	if (chunk_save.Write (&info, sizeof (info)) == sizeof (info)) {
		
		//
		// Write each of the remaining keyframes to the chunk
		//
		int count = m_SizeKeyframes.NumKeyFrames;
		bool success = true;
		for (int index = 0; (index < count) && success; index ++) {			
			info.Time = m_SizeKeyframes.KeyTimes[index];
			info.Size = m_SizeKeyframes.Values[index];
			success = (chunk_save.Write (&info, sizeof (info)) == sizeof (info));
		}

		ret_val = (success != false);
	}

	// Return the success status
	return ret_val;
}






bool
ParticleEmitterDefClass::Save_Extra_Info (ChunkSaveClass & chunk_save)
{
	// Assume error
	bool ret_val = false;

	// Begin a chunk that identifies the extra info
	if (chunk_save.Begin_Chunk (W3D_CHUNK_EMITTER_EXTRA_INFO) == TRUE) {

		W3dEmitterExtraInfoStruct data;

		memset(&data, 0, sizeof(data));
		data.FutureStartTime = Get_Future_Start_Time();
		bool success = (chunk_save.Write (&data, sizeof (data)) == sizeof (data));		
		ret_val = success;
		
		chunk_save.End_Chunk ();
	}

	return ret_val;
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Color_Keyframes
//
void
ParticleEmitterDefClass::Set_Color_Keyframes (ParticlePropertyStruct<Vector3> &keyframes)
{
	SAFE_DELETE_ARRAY (m_ColorKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_ColorKeyframes.Values);

	::Copy_Emitter_Property_Struct (m_ColorKeyframes, keyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Opacity_Keyframes
//
void
ParticleEmitterDefClass::Set_Opacity_Keyframes (ParticlePropertyStruct<float> &keyframes)
{
	SAFE_DELETE_ARRAY (m_OpacityKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_OpacityKeyframes.Values);

	::Copy_Emitter_Property_Struct (m_OpacityKeyframes, keyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Size_Keyframes
//
void
ParticleEmitterDefClass::Set_Size_Keyframes (ParticlePropertyStruct<float> &keyframes)
{
	SAFE_DELETE_ARRAY (m_SizeKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_SizeKeyframes.Values);

	::Copy_Emitter_Property_Struct (m_SizeKeyframes, keyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Rotation_Keyframes
//
void 
ParticleEmitterDefClass::Set_Rotation_Keyframes (ParticlePropertyStruct<float> &keyframes, float orient_rnd)
{
	SAFE_DELETE_ARRAY (m_RotationKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_RotationKeyframes.Values);

	::Copy_Emitter_Property_Struct (m_RotationKeyframes, keyframes);
	m_InitialOrientationRandom = orient_rnd;
	return ;
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Frame_Keyframes
//
void 
ParticleEmitterDefClass::Set_Frame_Keyframes (ParticlePropertyStruct<float> &keyframes)
{
	SAFE_DELETE_ARRAY (m_FrameKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_FrameKeyframes.Values);

	::Copy_Emitter_Property_Struct (m_FrameKeyframes, keyframes);
	return ;
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Set_Blur_Time_Keyframes
//
void
ParticleEmitterDefClass::Set_Blur_Time_Keyframes (ParticlePropertyStruct<float> &keyframes)
{
	SAFE_DELETE_ARRAY (m_BlurTimeKeyframes.KeyTimes);
	SAFE_DELETE_ARRAY (m_BlurTimeKeyframes.Values);

	::Copy_Emitter_Property_Struct (m_BlurTimeKeyframes, keyframes);
	return ;
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Get_Color_Keyframes
//
void
// ?ParticleEmitterDefClass::Get_Color_Keyframes present-unmatched
ParticleEmitterDefClass::Get_Color_Keyframes (ParticlePropertyStruct<Vector3> &keyframes) const
{
	::Copy_Emitter_Property_Struct (keyframes, m_ColorKeyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Get_Opacity_Keyframes
//
void
// ?ParticleEmitterDefClass::Get_Opacity_Keyframes present-unmatched
ParticleEmitterDefClass::Get_Opacity_Keyframes (ParticlePropertyStruct<float> &keyframes) const
{
	::Copy_Emitter_Property_Struct (keyframes, m_OpacityKeyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Get_Size_Keyframes
//
void
// ?ParticleEmitterDefClass::Get_Size_Keyframes present-unmatched
ParticleEmitterDefClass::Get_Size_Keyframes (ParticlePropertyStruct<float> &keyframes) const
{
	::Copy_Emitter_Property_Struct (keyframes, m_SizeKeyframes);
	return ;
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Get_Rotation_Keyframes
//
void
// ?ParticleEmitterDefClass::Get_Rotation_Keyframes present-unmatched
ParticleEmitterDefClass::Get_Rotation_Keyframes (ParticlePropertyStruct<float> &keyframes) const
{
	::Copy_Emitter_Property_Struct (keyframes, m_RotationKeyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Get_Frame_Keyframes
//
void 
// ?ParticleEmitterDefClass::Get_Frame_Keyframes present-unmatched
ParticleEmitterDefClass::Get_Frame_Keyframes (ParticlePropertyStruct<float> &keyframes) const
{
	::Copy_Emitter_Property_Struct (keyframes, m_FrameKeyframes);
	return ;
}

///////////////////////////////////////////////////////////////////////////////////
//
//	Get_Blur_Time_Keyframes
//
void
// ?ParticleEmitterDefClass::Get_Blur_Time_Keyframes present-unmatched
ParticleEmitterDefClass::Get_Blur_Time_Keyframes (ParticlePropertyStruct<float> &blurtimeframes) const
{
	::Copy_Emitter_Property_Struct (blurtimeframes, m_BlurTimeKeyframes);
	return ;
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Create
//
RenderObjClass *
// ?ParticleEmitterPrototypeClass::Create present-unmatched
ParticleEmitterPrototypeClass::Create (void)
{
	return ParticleEmitterClass::Create_From_Definition (*m_pDefinition);
}


///////////////////////////////////////////////////////////////////////////////////
//
//	Load
//
PrototypeClass *
// ?ParticleEmitterLoaderClass::Load_W3D present-unmatched
ParticleEmitterLoaderClass::Load_W3D (ChunkLoadClass &chunk_load)
{
	// Assume failure
	ParticleEmitterPrototypeClass *pprototype = NULL;

	// Create a definition object
	ParticleEmitterDefClass *pdefinition = W3DNEW ParticleEmitterDefClass;
	if (pdefinition != NULL) {
		
		// Ask the definition object to load the emitter data
		if (!pdefinition->Load_W3D (chunk_load)) {
			
			// Error!  Free the definition
			delete pdefinition;
			pdefinition = NULL;
		} else {

			// Success!  Create a prototype from the definition
			pprototype = W3DNEW ParticleEmitterPrototypeClass (pdefinition);
		}
	}

    // Return a pointer to the prototype
	 return pprototype;
}

// Load_W3D, Save_W3D and their Read_ and Save_ helpers are rowed in their own particle_emitter_*.cpp and
// ParticleEmitterDefClass*Bool.cpp units: retail's return bool, as part_ldr.h declares.
// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva7F4CC0Child@@QAE@XZ=??0PrototypeClass@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0SnapshotDupReplica@@QAE@XZ=??0PrototypeClass@@QAE@XZ")
#pragma comment(linker, "/alternatename:?bfmeInitTUA@BfmeSubTUA@@QAEXXZ=??0PrototypeClass@@QAE@XZ")
