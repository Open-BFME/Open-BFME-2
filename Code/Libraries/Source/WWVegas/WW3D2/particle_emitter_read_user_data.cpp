// cl: /Ireference/shims/bfmeparticleload /EHsc /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

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

// Retail uses STLport's direct narrow allocator entry point (class 3 game
// allocation), rather than the imported CRT malloc binding.
namespace _STL {
template <class T> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

#ifndef SAFE_DELETE
#define SAFE_DELETE(pointer) \
{ \
	if (pointer) { \
		delete pointer; \
		pointer = 0; \
	} \
}
#endif

// Particle system loader, adapted from the Open-BFME-1 donor for BFME2's bool loader ABI; direct BFME2 allocator calls are retained.
bool
ParticleEmitterDefClass::Read_User_Data (ChunkLoadClass &chunk_load)
{
	bool ret_val = false;

	if (chunk_load.Open_Chunk () &&
	    (chunk_load.Cur_Chunk_ID () == W3D_CHUNK_EMITTER_USER_DATA)) {

		W3dEmitterUserInfoStruct user_info = { 0 };
		if (chunk_load.Read (&user_info, sizeof (user_info)) == sizeof (user_info)) {
			ret_val = true;
			m_iUserType = user_info.Type;
			if (user_info.SizeofStringParam > 0) {
				m_pUserString = _STL::allocator<char>::allocate (sizeof (char) * (user_info.SizeofStringParam+1), 0);
				m_pUserString[0] = 0;
				if (chunk_load.Read (m_pUserString, user_info.SizeofStringParam) != user_info.SizeofStringParam) {
					ret_val = false;
				}
			}
		}
		chunk_load.Close_Chunk ();
	}
	return ret_val;
}
