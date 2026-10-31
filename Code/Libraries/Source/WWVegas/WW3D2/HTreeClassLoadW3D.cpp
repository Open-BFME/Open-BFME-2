// cl: /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_htreetu /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/archivefile_directory_dtor /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/shims/zh_outofline /Ireference/shims/updatemodule_ctor
// stlport
//
// ?Load_W3D@HTreeClass@@QAEHAAVChunkLoadClass@@@Z, retail 0x00166800..0x00166973
// (371B), thiscall ret 4.
//
// Donor: Open-BFME-1 game/Libraries/Source/WWVegas/WW3D2/HTreeClassLoadW3D.cpp
// (Zero Hour's htree.cpp HTreeClass::Load_W3D shape): read the
// W3D_CHUNK_HIERARCHY_HEADER (0x101) chunk, bump the pivot count for pre-3.0
// files, copy the name, allocate the pivots, then read every
// W3D_CHUNK_PIVOTS (0x102) chunk, freeing the tree when one fails. BFME 2
// differences read from retail: the tree is emptied through the out-of-line
// Free 0x00166510 (BFME 1 inlined it), and the pivots are BFME 2's 0x58-byte
// PivotClass (rowed ctor 0x00197830, built by the vector constructor iterator
// 0x00001423 over operator new[] 0x0002FDE0, no cookie). Callees:
// ChunkLoadClass Open_Chunk / Cur_Chunk_ID / Read / Close_Chunk
// (0x00614F50 / 0x00615020 / 0x006151A0 / 0x00614FC0) and the rowed
// read_pivots 0x001614F0.

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links one
// copy, the /O1 body at 0x00001423. This unemitted anchor (as in
// HTreeClassInitDefault.cpp) makes this unit's copy that same body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include <windows.h>
#include "htree.h"
#include "chunkio.h"
#include "w3d_file.h"
#include <string.h>

#pragma intrinsic(memcpy)

int HTreeClass::Load_W3D(ChunkLoadClass &cload)
{
	Free();

	if (!cload.Open_Chunk())
		return LOAD_ERROR;

	if (cload.Cur_Chunk_ID() != 0x101)
		return LOAD_ERROR;

	W3dHierarchyStruct header;
	if (cload.Read(&header, sizeof(header)) != sizeof(header))
		return LOAD_ERROR;

	cload.Close_Chunk();

	bool pre30 = false;
	if (header.Version < 0x30000)
	{
		header.NumPivots++;
		pre30 = true;
	}

	memcpy(Name, header.Name, sizeof(Name));
	NumPivots = header.NumPivots;
	if (NumPivots > 0)
		Pivot = new PivotClass[NumPivots];

	while (cload.Open_Chunk())
	{
		if (cload.Cur_Chunk_ID() == 0x102)
		{
			if (!read_pivots(cload, pre30))
			{
				Free();
				return LOAD_ERROR;
			}
		}
		cload.Close_Chunk();
	}

	return OK;
}
