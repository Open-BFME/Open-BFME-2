// cl: /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

// Select the BFME2 legacy kernel32 import declarations before reference headers.
#include <sweep/winbase_shim.h>
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#define MAX_PATH 260
#define LPCTSTR const char *
// Particle system loader, adapted from the Generals Zero Hour reference.
#include "part_ldr.h"
#include "part_emt.h"
#include "w3derr.h"
#include "chunkio.h"
#include "win.h"
#include "assetmgr.h"
#include "texture.h"

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(pointer) \
	if (pointer) { \
		delete [] pointer; \
		pointer = 0; \
	}
#endif

bool
ParticleEmitterDefClass::Read_Rotation_Keyframes (ChunkLoadClass &chunk_load)
{
	bool ret_val = true;

	W3dEmitterRotationHeaderStruct header;
	if (chunk_load.Read(&header,sizeof(header)) != sizeof(header)) {
		ret_val = false;
	}
	m_RotationKeyframes.NumKeyFrames = header.KeyframeCount;
	m_RotationKeyframes.Rand = header.Random;
	m_InitialOrientationRandom = header.OrientationRandom;

	W3dEmitterRotationKeyframeStruct key;
	if (chunk_load.Read(&key,sizeof(key)) == sizeof(key)) {
		m_RotationKeyframes.Start = key.Rotation;
	}

	if (m_RotationKeyframes.NumKeyFrames > 0) {
		m_RotationKeyframes.KeyTimes = W3DNEWARRAY float[m_RotationKeyframes.NumKeyFrames];
		m_RotationKeyframes.Values = W3DNEWARRAY float[m_RotationKeyframes.NumKeyFrames];
	}

	for (unsigned int i=0; (i<header.KeyframeCount) && (ret_val == true); i++) {
		W3dEmitterRotationKeyframeStruct key;
		if (chunk_load.Read(&key,sizeof(key)) == sizeof(key)) {
			m_RotationKeyframes.KeyTimes[i] = key.Time;
			m_RotationKeyframes.Values[i] = key.Rotation;
		} else {
			m_RotationKeyframes.KeyTimes[i] = 0.0f;
			m_RotationKeyframes.Values[i] = 0.0f;
			ret_val = false;
		}
	}
	return ret_val;
}
