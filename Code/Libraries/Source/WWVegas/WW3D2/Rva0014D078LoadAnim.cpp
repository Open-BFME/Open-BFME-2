// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva0014D078_LoadAnim@Rva0014CD63_Prototype@@QAEXXZ @ 0x0014D078 (310
// bytes). Slot 2 of the animation prototype vtable 0x00BD37EC (slot 6 is
// the rowed Rva0014CDCB_ReleaseTree, slot 13 the 'MINA' tag). Target
// evidence: the prototype name at +0x18 is split at its first '.' (strchr
// import), the remainder plus ".w3d" (0x00BC6860) is opened through
// GetGameFilePart with the +0x1C/+0x20 ints, and the first chunk decides
// the class: 0x200 builds a 0x54-byte HRawAnimClass, 0x280 a 0x5C-byte
// HCompressedAnimClass, each stored at +0x14 before its Load_W3D. A
// nonzero load result releases the anim through its ref count (slot 0 on
// the last reference) and nulls the member; the file is closed through
// its slot 2 either way. The chunk and anim class names follow the BFME1
// and ZH W3D loaders (W3D_CHUNK_ANIMATION / W3D_CHUNK_COMPRESSED_ANIMATION).

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *s, int c);

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

class HAnimClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--m_NumRefs == 0)
			Delete_This();
	}

private:
	int m_NumRefs;
};

class HRawAnimClass : public HAnimClass
{
public:
	HRawAnimClass();
	int Load_W3D(ChunkLoadClass &cload);

private:
	char m_body[0x54 - 0x08];
};

class HCompressedAnimClass : public HAnimClass
{
public:
	HCompressedAnimClass();
	int Load_W3D(ChunkLoadClass &cload);

private:
	char m_body[0x5C - 0x08];
};

class Rva0014CD63_Prototype
{
public:
	void Rva0014D078_LoadAnim();

private:
	void *m_vtable;
	char m_pad04[0x10];
	HAnimClass *m_anim;	// +0x14
	StringClass m_name;	// +0x18
	int m_arg1C;		// +0x1C
	int m_arg20;		// +0x20
};

void Rva0014CD63_Prototype::Rva0014D078_LoadAnim()
{
	const char *anim_name = strchr(m_name, '.');
	if (anim_name == 0)
		return;

	StringClass filename(anim_name + 1, false);
	filename += ".w3d";
	File *file = GetGameFilePart(filename, m_arg1C, m_arg20);
	if (file == 0)
		return;

	ChunkLoadClass cload(file);
	if (cload.Open_Chunk()) {
		switch (cload.Cur_Chunk_ID()) {
		case 0x200: {
			HRawAnimClass *anim = new HRawAnimClass;
			m_anim = anim;
			if (anim->Load_W3D(cload) != 0) {
				m_anim->Release_Ref();
				m_anim = 0;
			}
			break;
		}
		case 0x280: {
			HCompressedAnimClass *anim = new HCompressedAnimClass;
			m_anim = anim;
			if (anim->Load_W3D(cload) != 0) {
				m_anim->Release_Ref();
				m_anim = 0;
			}
			break;
		}
		}
	}
close:
	file->Close();
}
