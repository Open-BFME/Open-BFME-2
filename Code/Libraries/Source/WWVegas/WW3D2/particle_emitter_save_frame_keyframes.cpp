// cl: /Ireference/shims/bfmeparticlesave /EHsc /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sweep/winbase_shim.h>
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
#include "part_ldr.h"
#include "part_emt.h"
#include "w3derr.h"
#include "chunkio.h"
#include "win.h"
#include "assetmgr.h"
#include "texture.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) { \
		delete pointer; \
		pointer = 0; \
	} \
}
#endif


// Adapted donor serializer using BFME2 bool result.
bool
ParticleEmitterDefClass::Save_Frame_Keyframes (ChunkSaveClass & chunk_save)
{
	// Assume error
	bool ret_val = false;
	
	// Begin a chunk that identifies the rotation keyframes
	if (chunk_save.Begin_Chunk (W3D_CHUNK_EMITTER_FRAME_KEYFRAMES) == TRUE) {

		// Write the header
		W3dEmitterFrameHeaderStruct header;
		header.KeyframeCount = m_FrameKeyframes.NumKeyFrames;
		header.Random = m_FrameKeyframes.Rand;
		chunk_save.Write (&header, sizeof (W3dEmitterFrameHeaderStruct));
		
		// Write the keyframes
		bool success = true;
		W3dEmitterFrameKeyframeStruct key;

		// Write the start keyframe
		key.Time = 0;
		key.Frame = m_FrameKeyframes.Start;
		chunk_save.Write (&key, sizeof (key));

		// Write the remaining keyframes
		for (unsigned int index = 0; (index < header.KeyframeCount) && success; index ++) {			
			key.Time = m_FrameKeyframes.KeyTimes[index];
			key.Frame = m_FrameKeyframes.Values[index];
			success = (chunk_save.Write (&key, sizeof (key)) == sizeof (key));
		}

		ret_val = (success != false);

		// End the chunk
		chunk_save.End_Chunk ();
	}

	// Return the WW3DErrorType return code
	return ret_val;
}
