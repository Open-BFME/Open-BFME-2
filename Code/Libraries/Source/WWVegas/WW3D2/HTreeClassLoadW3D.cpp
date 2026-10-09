// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
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

typedef unsigned long uint32;

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links one
// copy, the /O1 body at 0x00001423. This unemitted anchor (as in
// HTreeClassInitDefault.cpp) makes this unit's copy that same body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

class ChunkLoadClass
{
public:
	bool Open_Chunk();
	bool Close_Chunk();
	uint32 Cur_Chunk_ID();
	uint32 Read(void *buffer, uint32 bytes);
};

struct W3dVectorStruct
{
	float x, y, z;
};

struct W3dHierarchyStruct
{
	uint32 Version;
	char Name[16];
	uint32 NumPivots;
	W3dVectorStruct Center;
};

// BFME 2's pivot is 0x58 bytes (HTreeClassInitDefault.cpp) with no destructor,
// so new[] carries no cookie.
class PivotClass
{
public:
	PivotClass();

private:
	unsigned char m_data[0x58];
};

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

class HTreeClass
{
public:
	enum { OK, LOAD_ERROR };

	int Load_W3D(ChunkLoadClass &cload);
	void Free();

private:
	bool read_pivots(ChunkLoadClass &cload, bool pre30);

	char Name[16];
	int NumPivots;
	PivotClass *Pivot;
	float ScaleFactor;
};

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);
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
