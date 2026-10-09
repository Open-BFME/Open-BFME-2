// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva0017FDA7_LoadTree@Rva0017FB41_Prototype@@QAEXXZ
// retail 0x0017FDA7..0x0017FEA4 (254 bytes) thiscall RET 0.
//
// Slot 2 of the HTree prototype vtable 0x00BD4F10 (absolute reference
// 0x007D4F18), the twin of the animation prototype's
// Rva0014CD63_Prototype::Rva0014D078_LoadAnim (Rva0014D078LoadAnim.cpp).
// Unless the +0x14 HTree is already loaded, it opens the prototype name at
// +0x18 past its two-character prefix plus ".w3d" (0x00BC6860) through
// GetGameFilePart with the +0x1C/+0x20 ints and, when the first chunk is
// 0x100 (W3D_CHUNK_HIERARCHY), builds a 0x34-byte HTreeClass (rowed
// constructor 0x00166270) at +0x14 and loads it (Load_W3D 0x00166800); a
// nonzero result deletes it again (rowed ~HTreeClass 0x001667E0). The file
// is closed through its slot 2 either way.

typedef unsigned int uint32;
typedef unsigned char uint8;

class StringClass
{
public:
	StringClass(const char *string, bool hint_temporary);
	~StringClass() { Free_String(); }
	const StringClass &operator+=(const char *string);
	operator const char *() const { return m_Buffer; }

private:
	void Free_String();
	char *m_Buffer;
};

class BFMEChunkInput
{
public:
	virtual void f0();
	virtual void f1();
	virtual void Close();
};

class File : public BFMEChunkInput
{
};

class FileClass;

File *__cdecl GetGameFilePart(const char *filename, int a, int b);

struct ChunkHeader
{
	ChunkHeader() : ChunkType(0), ChunkSize(0) {}
	uint32 ChunkType;
	uint32 ChunkSize;
};

struct MicroChunkHeader
{
	MicroChunkHeader() {}
	uint8 ChunkType;
	uint8 ChunkSize;
};

class ChunkLoadClass
{
public:
	ChunkLoadClass(BFMEChunkInput *input);
	bool Open_Chunk();
	unsigned long Cur_Chunk_ID();

private:
	FileClass *File;
	BFMEChunkInput *Input;
	int StackIndex;
	uint32 PositionStack[256];
	ChunkHeader HeaderStack[256];
	bool InMicroChunk;
	int MicroChunkPosition;
	MicroChunkHeader MCHeader;
};

class HTreeClass
{
public:
	HTreeClass();					// 0x00166270
	~HTreeClass();					// 0x001667E0
	int Load_W3D(ChunkLoadClass &cload);		// 0x00166800

private:
	char m_body[0x34];
};

class Rva0017FB41_Prototype
{
public:
	void Rva0017FDA7_LoadTree();

private:
	void *m_vtable;
	char m_pad04[0x10];
	HTreeClass *m_tree;	// +0x14
	StringClass m_name;	// +0x18
	int m_arg1C;		// +0x1C
	int m_arg20;		// +0x20
};

void Rva0017FB41_Prototype::Rva0017FDA7_LoadTree()
{
	if (m_tree != 0)
		return;

	StringClass filename((const char *)m_name + 2, false);
	filename += ".w3d";
	File *file = GetGameFilePart(filename, m_arg1C, m_arg20);
	if (file == 0)
		return;

	ChunkLoadClass cload(file);
	if (cload.Open_Chunk() && cload.Cur_Chunk_ID() == 0x100)
	{
		m_tree = new HTreeClass;
		if (m_tree->Load_W3D(cload) != 0)
		{
			delete m_tree;
			m_tree = 0;
		}
	}
	file->Close();
}
