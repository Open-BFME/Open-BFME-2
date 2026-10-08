// cl: /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/WW3D/pluglib
// HLodDefClass::read_header (0x0019ECE0, 232B).
//
// Reached by compiling the BFME 1 source rather than by searching for BFME 1's
// retail bytes: lotrbfme.exe's own copy of this body is NOT byte-identical, so
// bfme1_sweep can never place it -- Open-BFME-1 carries it marked
// "present-unmatched" for that reason. Compiled here at the sweep's default
// /O2 /GR- /EHsc- it is byte-exact against game.dat, unique in .text, and
// Ghidra independently calls 0x0019ECE0 a 232-byte function.
#include "winbase_shim.h"
#include "hlod.h"
#include "chunkio.h"
#include <string.h>

// Make our vector-deleting-dtor copy identical to hlod.cpp's kept copy: that
// TU defines ~SubObjectArrayClass in-TU as { Reset(); }, so its ??_E inlines
// the dtor to a direct Reset call, while this TU calling the out-of-line dtor
// emits a differing ??_E. Defining the dtor inline here lets our ??_E inline
// the same way; the inline ??1 is a COMDAT the link discards for hlod.cpp's
// regular copy.
// ??1SubObjectArrayClass@HLodDefClass@@QAE@XZ present-unmatched
// ??1SubObjectArrayClass@HLodDefClass@@QAE@XZ is a row of hlod.cpp; this unit only declares it.

bool HLodDefClass::read_header(ChunkLoadClass & cload)
{
	/*
	**	Open the first chunk, it should be the LOD header
	*/
	if (!cload.Open_Chunk()) return false;

	if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_HEADER) {
		// ERROR: Expected HLOD Header!
		return false;
	}

	W3dHLodHeaderStruct header;
	if (cload.Read(&header,sizeof(header)) != sizeof(header)) {
		return false;
	}
	cload.Close_Chunk();

	// Copy the name into our internal variable
	if (Name != NULL) {
		free(Name);
	}
	Name = ::_strdup(header.Name);
	HierarchyTreeName = ::strdup(header.HierarchyName);
	LodCount = header.LodCount;
	Lod = W3DNEWARRAY SubObjectArrayClass[LodCount];
	return true;
}
